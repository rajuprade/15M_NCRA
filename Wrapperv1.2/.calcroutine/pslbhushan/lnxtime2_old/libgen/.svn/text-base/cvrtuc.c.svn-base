 void cvrtuc(s)
 char s[];
 
 /*  cvrtuc converts its input string to upper case.  The input string
     must be terminated by '\0'.  cvrtuc should work in any C environment.
---
%% Convert string to upper case.
:: Parser String
 
LANGUAGE: C
ENVIRONMENT:  Any standard C
 
Testing:
85jun14.  Echoed typed in strings mixing UC/lc and numbers -
     seems to work.
 
++$       Audit trail:
  85jun14     1.0   B. Clark     Original submission
--$
-*/ 
#define version 1.0
 
   { long i;
     i=0;
     while (s[i] != '\0')
       { if(('a'<=s[i])&&(s[i]<='z')) s[i]+='A'-'a';
         i++;}  }
