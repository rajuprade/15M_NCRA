#! /bin/bash

if [ $# -eq 0 ]
then
 echo "usage old-dir new-dir"
 exit 1
fi
dirold=$1
dirnew=$2

for var in `ls $dirold`
do
   oldfile=${dirold}/$var

   if [ -f ${dirnew}/$var ]
   then
    newfile=${dirnew}/$var
    i=`diff $oldfile $newfile | wc -l`
    if [ $i -gt 0 ]
    then 
         vimdiff $oldfile $newfile
         echo "Copy $oldfile to $newfile"
         read ans < /dev/tty
         if [ $ans == "y" ]
         then
            cp -i $oldfile $newfile
         fi
    fi
#  else
#      echo $oldfile $dirnew/$var
#      cp -i $oldfile $dirnew/$var
   fi
done
           
