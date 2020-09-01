      /<[Hh][Ee][Aa][Dd]>/ {
         s%.*<[Hh][Ee][Aa][Dd]>%%
         :next
         \?</[Hh][Ee][Aa][Dd]>? !{
            N
            P
            s%.*\n%%
            b next
         }
         s%</[Hh][Ee][Aa][Dd]>.*%%
         p
         q
      }
