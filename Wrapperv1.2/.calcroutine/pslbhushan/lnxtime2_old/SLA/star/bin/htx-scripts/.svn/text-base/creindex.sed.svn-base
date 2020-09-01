      :concat
      /<[ 	]*[aA]\{0,1\}[ 	]*$/{
         N
         s%\n[^:]*:% %
         b concat
      }
      /<[ 	]*[aA][ 	][^>]*$/{
         N
         s%\n[^:]*:% %
         b concat
      }
      /xref_/{
         t dolab
         :dolab
         s%^\([^/ 	]*/\([^: 	]*\):.*<[ 	]*[aA][ 	][^>]*\)[nN][aA][mM][eE][ 	]*=[ 	]*"\{0,1\}xref_\([^ 	">]*\)[  "]\{0,1\}\([^>]*>.*\)$%< \2 \3\
\1\4%
         t label
         b dolink
         :label
         P
         b rescan
         :dolink
         s%^\([^/ 	]*/\([^: 	]*\):.*<[ 	]*[aA][ 	][^>]*\)[hH][rR][eE][fF][ 	]*=[ 	]*"[^ 	"]*/\([^ 	/"]*\)\.htx/[^  "]*[#?]xref_\([^  "]*\)"\([^>]*>.*\)$%> \2 \3 \4\
\1\5%
         t link
         b rescan
         :link
         P
         :rescan
         D
      }
