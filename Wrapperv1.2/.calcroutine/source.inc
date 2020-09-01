	structure /source/
		union 
		  map
			character*12 name
		  end map
		  map
			real*4 nn(3)
		  end map
		end union

		union
		  map
			real*8 ra0
			real*8 dec0
			real*8 ep0
			real*8 rad
			real*8 decd
			real*8 epd
			real*8 raoff
			real*8 dra
			real*8 decoff
			real*8 ddec
			real*8 te0
			real*8 azoff
			real*8 daz
			real*8 eloff
			real*8 del
			real*8 th0
			real*8 time
		end map

		map
			real*8 aa(17)
		end map
	   end union
	end structure

	structure/final/
		union
		    map
			real*8  lctr
			real*8  ldayr
			real*8  lcts
			real*8  ldays
			real*8  az
			real*8  el
			real*8  deltaz
			real*8  deltel
		    end map
		
		    map
			real*8  res(8)
		    end map
		end union
	end structure
