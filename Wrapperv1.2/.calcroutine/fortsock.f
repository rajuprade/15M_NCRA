      subroutine init_sock(iptr,istat)

      include "online.inc"
      integer iptr,istat,itoken,length,flag,idata,mindx
      character*12 name_c
      character*(*) mbuff,name

      integer my_index,my_type,indx,length,loclen,indx,istat
      integer sockid,ierr,i,j,k,lptr
      integer getpid,comp_str,casecomp_str
      integer tcpport,leng,itry,nbytes,lnblnk
      integer MAX_SOCK_MESG/5000/,NO_DATA/-35/
      integer line/0/,ibuff,get_process_table,null_term
      byte bbuff,bbuffi(4)
      equivalence(ibuff,bbuffi)
      character*12 name_c,host_c,name_p,host_p,my_name
      character*1200 buff

      pointer (lptr,config)
      record /PROCESS_TABLE/ config
c				get my name
      lptr=get_process_table()
      if(lptr.eq.0) then
         write(0,*)"init_ipc: shared memory not initiated"
         iptr=-1
         return
      endif
      if(lptr.eq.-1) then
         write(0,*)"init_ipc: shared memory failure"
         iptr=-1
         return
      endif
      call get_myname(my_name)
c				get my index      
      call get_index(my_name,my_index)
      if(my_index.lt.0) then
         write(0,*)my_name," not in configuration... exit"
	 iptr=-1
	 return
      endif
      iptr=my_index
      j=iptr
      do i=0,1
          config.process(j).tcp_local_err(i)=0
          config.process(j).tcp_remote_err(i)=0
C          config.process(j).status(i)=0
      enddo
      config.process(j).pid=getpid()
      istat=0
      my_type=0
      if(comp_str(my_name,"unixhub").gt.0)my_type=1
      return



C
C
C	sock_start 	open a socket on a specified tcp port,
C			wait for a connection to be made by
C			specified process on specified machine,
C			ensure the specified process knows the 
C			right password, and return the socket id
C			process id of connecting task and status
C
C	Parameters (* means returned values)
C	
C	name_c		name of connecting process
C	itoken		passwd number that connecting
C			process must give
C	istat		status of call
C			=0    	Success
C			=-1801	uanble to open socket
C			=-1802	packet from connector !=80 bytes
C			=-1803	connector name does not match
C			=-1804	connector hostid does not match
C			=-1805	connector token does not match
C			=-1806  unable to get connectors pid
C
C
      entry sock_start(name_c,itoken,istat)
      
      tcpport=config.process(my_index).tcpport
      write(0,*)" sock_start: my_name=",my_name,tcpport

c				open required socket
      i=0
      sockid=-1
      do while ( sockid.lt.0)
         call so_serv(tcpport,sockid)
	 write(0,*)my_name," sock_start: after so_serv ",tcpport,sockid
	 i=i+1

         if(sockid .lt. 0) then
            write(0,*)my_name,':sockid=',sockid,' while connecting ',
     1           name_c,' on port=',tcpport,':attempt=',i
            if(i.eq.5) then
               istat=-1801
               return
            endif
            call sleep(1)
         endif
      enddo


c				get 1 line from connecting party

      call so_recv(sockid,buff,80,0,i)

      if(i.ne. 80) then
         write(0,*)my_name,'strange pkt len:',i, buff,
     1       'connecting to ',name_c
         istat=-1802
         return
      endif

c				check if right connection

      read(buff,*)name_p,i,host_p,j

      write(0,*)name_p,i,host_p,j

c				check if name ok
      if(comp_str(name_p,name_c).eq.0) then
         write(0,*)my_name,':strange name connecting from ',name_c
         write(0,*)' req task name=',name_c,' ret name=',name_p 
         call sleep(1)
         istat=-1803
         return
      endif

c				chaeck if right host

      host_c=config.hostname

      if(comp_str(host_c,host_p).eq.0) then
         write(0,*)my_name,'strange job connecting from ',name_c
         write(0,*)' req host name=',host_c,' ret host=',host_p 
         call sleep(1)
         istat=-1804
         return
      endif
c				check if password number correct

      if(itoken.ne.j) then
         write(0,*)my_name,':incorrect passwd token by ',name_c,j
         call sleep(1)
         istat=-1805
         return
      endif

c				send connector name,owd pid and hostname 

      write(buff,'(120x)')
      i=config.process(my_index).pid
      write(buff,*)my_name(:lnblnk(my_name)),' ',i,' ',host_c
      ierr=0
      call so_send(sockid,buff,80,0,i)

      if(i.ne. 80) then
         istat=-1806
         return
      endif

c				fill info and return

      istat=0
      config.process(my_index).sock_id(my_type)=sockid
      config.process(my_index).status(my_type)=1
      if(my_index.eq.0)config.process(1).status(my_type)=1
      write(0,*)my_name,':successfully connected to ',name_c,
     1    ' on socket ',sockid
      return


C
C
C	sock_resp	respond to a socket opend with sock_start
C			whose tcp port and hostname are specified
C			callers name and password token have to 
C			be specified. routine tries connecting 
C			to the socket istat times before returning
C
C			Returns socket id, process id of parent of
C			socket and status
C
C	Parameters ( * return values)
C	
C	tcpport	tcp port of socket
C	sock_id *	id of connected socket
C	host_p		hostname of opener of the socket
C	pid_p *		process id of opener of socket
C	name_c		name of the responder to the socket
C	itoken		password number to be given to the opener 
C	istat *		no of time to try hard connection
C			Also return status 
C			0	success
C			-1811	unable to hard connect
C			-1812	unable to send 80byte packet
C			-1813	error detected by opener
C			-1814	host id of opener does not match
C			
C
C
      entry sock_resp(name_c,itoken,istat)


c				get index of socket opener     

      j=-1
      do i=0,config.max_process-1
         if(comp_str(config.process(i).name,name_c).gt.0) then
	    j=i   
         endif
      enddo
      if(j.lt.0) then
          write(0,*)my_name,name_c," not found in shared mem"
	  istat=-1
	  return
      endif
      indx=j

c				try for a hard connection istat times
      tcpport=config.process(indx).tcpport
      itry=istat
      buff=config.hostname
      i=null_term(buff)
      sockid=-1
      j=0
      do while (sockid.lt.0.and.j.lt.itry)
         call so_alloc(buff,tcpport,sockid)
         j=j+1
         if(sockid.lt.0.and.j.lt.itry) then
c            write(0,*)  my_name,'cant connect to ',tcpport,sockid,j
c            write(0,*) 'retrying after 3 sec'
c            call sleep(3)
         endif
      end do

      if(sockid.lt.0) then
         istat=-1811
         return
      endif

c				send my name,hostname,pid and password token

      leng=80
      write(0,*)name_c,buff,tcpport,sockid
      host_c=config.hostname
      i=config.process(my_index).pid
      write(buff,*)my_name,' ',i,' ',host_c,' ',itoken
      write(0,*)"sock_resp:",buff
      call so_send(sockid,buff,leng,0,i)
      if(i .ne. 80) then
         istat=-1812
         return
      endif


c				receive response packet

      i=0
      do while (i.ne.80)
      leng=80
      call so_recv(sockid,buff,leng,0,i)
      if(i .ne. 80) then
	 write(0,*)my_name,' got strange length from ',name_c,i
	 write(0,*)'packet=',buff(1:i)
	 istat=-1812
	 return
      endif
      enddo
      write(0,*)my_name,name_c,buff(1:80)
      read(buff,*)name_p,j,host_p

c				confirm connector is as expected

      if(comp_str(name_p,name_c).eq.0) then
         write(0,*)my_name,' ',name_c,'strange job connecting ',name_p
         istat=-1814
         return
      endif

c				confirm connector host is as expected

      if(comp_str(host_p,config.hostname).eq.0) then
         write(0,*)my_name,'strange host connecting ',name_p
         write(0,*)my_name,host_p,config.hostname
         istat=-1814
c         return
      endif

c				fill tables and return

      istat=0


      if(indx.lt.config.max_process) then
          config.process(indx).sock_id(my_type)=sockid
	  config.process(indx).status(my_type)=1
          if(indx.eq.0) then
	           config.process(1).status(my_type)=1
          endif
      endif

      write(0,*)my_name,' successfully connected to ',name_c,
     1    'socket ',sockid

      return
      
C
C
C       read a message from a socket without blocking
C       messages are expected to be in the form of a 4 byte length
C       followed by length bytes. The first 4 byte ( length) are read
C       in a unblocked mode. If 4 bytes are not present, routine
C       returns with status=NO_DATA(-35). If length bytes are present and
C       less than MAX_SOCK_LEN  routine reads length bytes in a
C       blocked mode
C
C       PARAMETERS  (* implies return values)
C
C       sockid  (if < 100) pointer to process in configuration table
C               (if > 100) sockid-100 is the actual socket number
C       buff    buffer in main prog into which to put mesg
C       leng    length of mesg
C       flag    type of read (0 normal,MSG_OUB,MSG_PEEK(man recv))
C                               note: MSG_OUB does not work in this routine
C       istat   status of read
C               0       success
C               -1821   unexpected length
C               -1822   mesg length does not match length field
C               -1823   got less than 4 bytes for length


      entry rd_soc_unbloc(iptr,mbuff,length,flag,istat)
c                               read length (4 bytes) in unblocked mode

c
c---   if iptr > 100, assume that it is a raw socket number=iptr-100
c---   avoid using ipr in this routine for compatibility with old fortsock.f
c

      if(iptr.lt.100) then
        indx=iptr
        sockid=config.process(indx).sock_id(my_type)
      else
        indx=-1
        sockid=iptr-100
      endif
      nbytes=4
      call so_block(sockid,1,istat)
      call so_recv(sockid,leng,nbytes,flag,istat)
      if(istat.ne.NO_DATA) then
 
c                               some bytes are available
 
         if(istat.lt.0) then
            if(indx.ge.0) then
c              config.process(indx).rec_err=
c     1              config.process(indx).rec_err+1
c             if(mod(config.process(indx).rec_err,20).eq.0)

              write(0,*)my_name,' istat=',istat,
     1         ' reading from ',config.process(indx).name
             else
               write(0,*)my_name,' istat=',istat,
     1         'reading from raw socket no:',sockid
             endif
             return
         endif
         if(istat.eq.4) then

c                               looks like a length

            if (leng.le.0.or.leng.gt.MAX_SOCK_MESG) then

c                               improper length

               loclen=leng
               if(indx.ge.0) then
                if (leng .eq. 0) then
                   write(0,*)my_name,':rd_soc_unbloc:socket open'
                   istat=-1821
                   leng=0
                   return
                else
                   write(0,*)my_name,':unexpected length= ',leng,
     1         ' istat ',istat,' from ',config.process(indx).name
                endif
               else
                if (leng .eq. 0) then
                 write(0,*)my_name,':raw socket no: ',sockid,
     1             'open'
                 istat=-1821
                 leng=0
                 return
                else
                   write(0,*)my_name,':unexpected length= ',leng,
     1             'from raw socket no:',sockid
                endif
               endif
               call flush_sock(sockid)
               istat=-1821
               leng=0
               return
            endif

c                               valid length, read messg in blocked mode

            call so_block(sockid,0,istat)
            loclen=leng
            call so_read(sockid,mbuff,leng)

            istat=loclen
            if(loclen.ne.leng) then
               write(0,*)my_name,' expecting ',loclen,' got ',
     1           leng,' from ',config.process(indx).name
               call flush_sock(sockid)
               istat=-1822
               return
            endif
            istat=0
            length=leng
         else

c                               length mesg no equal to 4 bytes

           if(istat.ne.0) then
            write(0,*)my_name,' got ',istat,' bytes as length',
     1           ' from ',config.process(indx).name
            call flush_sock(sockid)
            istat=-1823
           else
            if(my_type.eq.1) then 
              write(0,*)my_name,'rd_soc_unb: socket to ',
     1              config.process(indx).name,' open',istat
            else
              write(0,*)my_name,' rd_soc_unb:socket to ',
     1              ' unixhub  open',istat
              config.process(indx).tcp_remote_err(my_type)=-1
            endif
           endif
         endif
      endif
      return


      entry rd_soc_oub(iptr,idata,istat)
      indx=iptr
      sockid=config.process(indx).sock_id(my_type)
      ibuff=0
      do i=1,50
	 call so_recv(sockid,bbuff,1,1,istat)
	 if(istat.gt.0) go to 20
	 call sleep(1)
      enddo
20    if(istat.lt.0) then
	 write(0,*)'rd_soc_oub: failed , istat=',istat
      else
	 bbuffi(4)=bbuff
	 istat=0
	 idata=ibuff
      endif
      return

C
C
C	routine to send a mesg on a socket
C	mesg is in the form of a 4byte length word followed 
C	by length bytes of message
C
C	PARAMETERS
C	
C	sockid	id of socket on which to send
C	buff	array containing message
C	len	number of bytes in the message
C	flag	=0 for normal socket,MSG_OUB for out of bound Xmit
C	istat	return status
C		0	success
C		-1831	could not send 4 bytes of length
C		-1832	could not send body of message
C		-1833	will not send 0 byte messg 
C               -1834   will not send packet since socket seems open
C	

      entry snd_sock_pkt(iptr,mbuff,length,flag,istat)


      indx=iptr
      if(config.process(indx).tcp_local_err(my_type).lt.0) then
         write(0,*)my_name,' not sending packet to ',
     1	        config.process(indx).name, ' sock open'
         istat=-1834
         return
      endif

      leng=length
      sockid=config.process(indx).sock_id(my_type)
c      write(0,*)my_name,' snd_sock_pkt',iptr,my_type,sockid
c			check of mesg length is > 0

      if(leng .le. 0) then
	 istat=-1833
	 write(0,*)my_name,' wont send 0 byte mesg to',
     1	        config.process(indx).name
	 return
      endif
c			send 4 bytes of length

      call so_send(sockid,leng,4,flag,istat)
      if (istat.ne.4) then
	 write(0,*)my_name,' snd_sock_pkt: cant send 4 byte ',
     1	'on sock=',sockid,' istat=',istat	
	 istat=-1831
         config.process(indx).tcp_local_err(my_type)=-1
	 return
      endif

c			send len bytes of the message

      call so_send(sockid,mbuff,leng,flag,istat)
      if (istat.ne.leng) then
         istat=-1832
         config.process(indx).tcp_local_err(my_type)=-1
	 write(0,*)my_name,' cant send ',leng,'byte to',
     1		config.process(indx).name
         return
      endif
      istat=0
      return 

C
C
C	routine to close a socket and clear all tables
C
C	PARAMETERS
C	sockid	id of socket
C


      entry close_socket(iptr)

      if(iptr.le.config.max_process) then
        indx=iptr
        sockid=config.process(indx).sock_id(my_type)
        call so_close(sockid)
        write(0,*)my_name,':closing socket to ',
     1		config.process(indx).name
        config.process(indx).sock_id(my_type)=0
	config.process(indx).status(my_type)=0
c	 config.process(inxd).myname=''
c	 config.process(inxd).hostname=''
c	 config.process(inxd).my_pid=0
c	 config.process(inxd).connstat(sockid).name=''
c	 config.process(inxd).connstat(sockid).pid=0
c	 config.process(inxd).connstat(sockid).host=''
c	 config.process(inxd).connstat(sockid).tcpport=0
c	 config.process(inxd).connstat(sockid).snd_err=0
c	 config.process(inxd).connstat(sockid).rec_err=0
      endif
      return

C
C
C	routine to print out status of a socket
C
C	PARAMETERS
C	sockid	id of socket whose status is reqd
C		-1 implies all sockets
C


      entry fs_error(iptr,istat)
      indx=iptr
      if(iptr.ge.100) indx=iptr-100
      write(0,*)"fs_error :",my_name,istat
      return


      entry get_index(name,mindx)
      
      j=-1
      do i=0,config.max_process-1
          if(casecomp_str(name,config.process(i).name).gt.0)then
            j=i   
          endif
      enddo
      if(j.lt.0) then
           write(0,*)"get_index:",name," process not in shrd mem"
           mindx=-1
           return
       endif
 
       mindx=j
       return

      entry get_id(name,mindx)
      
      j=-1
      do i=0,config.max_process-1
          if(casecomp_str(name,config.process(i).name).gt.0)then
            j=i   
          endif
      enddo
      if(j.lt.0) then
           write(0,*)"get_index:",name," not in shared mem"
           mindx=-1
           return
       endif
 
       mindx=config.process(j).online_id
       return

      entry get_subno(iptr,mindx)
      mindx=-1
      j=config.process(iptr).online_id
      if((j.ge.50).and.(j.le.55))mindx=j-50
      if((j.ge.65).and.(j.le.70))mindx=j-65
      return


       end

C
C
C	routine reads the online configuration file and returns
C	a filled config structure along with callers name and 
C	id (iptr ) in the config table
C	the configuration file is expected to be defined by the
C	environmental variable ONCONFIG. A default exists which
C	may not be relaible
C
C	PARAMETERS
C
C	config	name of config structure in main array to return vals
C	my_name	name of caller : name returned if blank
C	myid	pointer to int in main pgm to have callers index in config
C	ierr	error status
C		0 	success
C		-1	error opening configuratio file
C		-2	error reading configuration file
C		-3	eof while reading configuration file
C		-4	calling routine not found in config file
C		-5	host name of caller does not match entry
C			in config file
C

      subroutine rd_config(config,istat)
c     read configuration
      include "online.inc"
      character*120 buff,configfile
      character*12 name_p
      character*4 rights
      record /PROCESS_TABLE/ config
      integer istat,comp_str
      integer i,j,line,index,lnblnk,hostnm,tcpport,onlnid
      integer null_term


      line=-1
      do i=0,255
        config.rev_map(i)=char(-1)
      enddo
      write(buff,'(120x)')
      call getenv("ONCONFIG",buff)
      if(lnblnk(buff).ne.0) then
        configfile=buff
      else
        configfile="onconfig.def"
      endif
      i=null_term(configfile)
      write(*,*)" reading online config from  "  ,
     1     configfile
      open(unit=9, file=configfile, status='old',err=9000)
      config.configfile=configfile
      read(9,'(a)',err=9005,end=9010)buff
      config.version=buff

      config.max_process=maxprocess
      do while (line.le.config.max_process-1)
	 read(9,'(a)',err=9005,end=9010)buff
	 if(index(buff,'*').ne.1) then
	    if(line.eq.-1) then
	       read(buff,*,err=9005)config.max_process,
     1              config.max_auto_process
	       line=line+1
	    else
	       write(name_p,'(12x)')
	       read(buff,*,err=9005)name_p,tcpport,onlnid,rights 
	       i=null_term(name_p)
	       config.process(line).name=name_p
	       config.process(line).tcpport=tcpport
	       config.process(line).online_id=onlnid
	       i=null_term(rights)
	       config.rev_map(onlnid)=line
	       config.process(line).rights=rights
	       config.process(line).pid=0
	       config.process(line).sock_id(0)=0
	       config.process(line).sock_id(1)=0
	       config.process(line).status(0)=0
	       config.process(line).status(1)=0
	       config.process(line).tcp_local_err(0)=0
	       config.process(line).tcp_local_err(1)=0
	       config.process(line).tcp_remote_err(0)=0
	       config.process(line).tcp_remote_err(1)=0
	       line=line+1
	    endif
	 endif
      enddo
      close(unit=9)
      i=hostnm(config.hostname)
      write(0,*)'hostname=',config.hostname
      j=-1
      do i=0,config.max_process-1
        if(comp_str(config.process(i).name,'scctask').gt.0) j=i  
      enddo
      do i=0,255
        if(config.rev_map(i).eq.-1)config.rev_map(i)=char(j)
      enddo

      return
 9000 continue      
      write(*,*)" error opening configuration file ",config.configfile
      write(*,*)" does ONCONFIG need to be set ?"
      istat=-1
      close(unit=9)
      return
 9005 continue      
      write(*,*)" error reading configuration file ",config.configfile
      istat=-2
      close(unit=9)
      return
 9010 continue      
      write(*,*)" eof reading configuration file ",config.configfile
      istat=-3
      close(unit=9)
      return
      end

      subroutine get_myname(name)
      character*(*) name
      character*120 buff
      integer i,j,rindex,lnblnk

      write(buff,'(120x)')
      call getarg(0,buff)
      i=rindex(buff,'/')+1
      j=lnblnk(buff)+1
      buff(j:j)=char(0)
      name=buff(i:j)

      return
      end
      

      integer function null_term(str)
      character*(*) str
      integer i,j,lnblnk,index
      j=index(str,char(0))
      if(j.eq.0) then
         i=lnblnk(str)+1
	 str(i:i)=char(0)
	 null_term=i
      else
	 null_term=j
      endif
      end

      integer function comp_str(str1,str2)
      character*(*) str1,str2
      integer i,j
      integer index,lnblnk
      i=index(str2,char(0))
      j=lnblnk(str2)
      if(i.gt.0) then
        comp_str=index(str1,str2(:i-1))
	return
      else
        comp_str=index(str1,str2(:j))
	return
      endif
      end

      integer function casecomp_str(str1,str2)
      character*(*) str1,str2
      character*(80) lstr1,lstr2
      integer i,j,k,l,n
      integer index,lnblnk
      i=index(str2,char(0))
      j=lnblnk(str2)
      k=lnblnk(str1)
      write(lstr1,'(80x)')
      write(lstr2,'(80x)')
      do l=1,k
	n=ichar(str1(l:l))
        if(n.ge.65.and.n.le.90)then
	  lstr1(l:l)=char(n+32)
        else
	  lstr1(l:l)=str1(l:l)
	endif
      enddo
      do l=1,j
	n=ichar(str2(l:l))
        if(n.ge.65.and.n.le.90)then
	  lstr2(l:l)=char(n+32)
	else
	  lstr2(l:l)=str2(l:l)
	endif
      enddo

      if(i.gt.0) then
        casecomp_str=index(lstr1,lstr2(:i-1))
	return
      else
        casecomp_str=index(lstr1,lstr2(:j))
	return
      endif
      end
C
C
C       routine flushes all bytes in a socket buffer in case of
C       errors in synchronisation.
C
C       PARAMETERS
C
C       sockid  id of socket to flush
C

      subroutine flush_sock(sockid)
      integer sockid,i,istat
      character*1100 buff


c      sockid=iptr
      call so_block(sockid,1,istat)

c       keep reading bytes from buffer till it is empty

      i=1
      do while(i.gt.0)
         call so_recv(sockid,buff,1000,0,i)
c         write(0,*)'so_flush ', "flushed ",i
c        write(0,*)buff(1:30)
      enddo
      return
      end


