#include "stdio.h"
/*++********************************************************************/
int srclist(string, list, strsize)	/* search list for string */
char *string;	/* search for this string in list ('\0' or ' ' terminated) */
char *list;	/* list to be searched ('\0' terminated) */
int strsize;	/* number of characters in each list element */
/***********************************************************************/
/*
%% search list for minimum match of string

Minimum match means that matching is done to the end of the string to 
be matched only.  Any further characters in the list element are ignored.  
For example, "EX" minimum matches with "EXIT", "EXACT", and "EXPLAIN" 
(making this minimum match ambiguous).  Matching "EX" with "EX" is an 
exact match.

'list' is a character array composed of string elements to be matched, 
each 'strsize' long.  Strings should be right justified within each 
element (leading blanks are ignored).  Leading and trailing blanks in 
'string' are ignored.

If a single minimum match or an exact match is found the matching 
element displacement is returned (0 to number of elements in list - 1).  
If no match or multiple matches are found -1 is returned.
---
LANGUAGE: C
ENVIRONMENT: VLBA Operator Interface Package
:: string match
++$ AUDIT TRAIL
1.0  87mar30  R. Heald  Extracted from SCRFUNC
1.1  87jul07  R. Heald  Blank also terminates string
1.2  88sep10  R. Heald  Don's overwrite string, Improve doc
--$
-*/
{
    register char *strhead, *eleptr, *strptr, *listptr;
    register int match, matches = 0;

    /* 'strhead' always points to first non-blank character in string */
    strhead = string;
    while(*strhead == ' ')strhead++;

    /* search through list an element at a time, always search entire 
    list for exact match (even though have multiple min matches) */
    for(eleptr = list; *eleptr; eleptr += strsize) {

	/* listptr points to first non-blank list element character */
	listptr = eleptr;
	while(*listptr == ' ')listptr++;

	/* compare strings until terminator 
	    or non-matching characters are found */
	strptr = strhead;	/* pointer to 1st non-blank in string */
	while(*strptr != '\0' && *strptr != ' ' && *strptr == *listptr) {
	    strptr++;
	    listptr++;
	}

	/* check for minimum match (has end of string been reached?) */
	if(*strptr == ' ' || *strptr == '\0') {

	    /* save matching element displacement and bump match count */
	    match = (eleptr - list) / strsize;
	    matches++;

	    /* check for exact match (has end of list element been reached?) */
	    if(listptr - eleptr == strsize) {
		matches = 1;
			break;
	    }
	}
    }

    /* if just one match then return matching element displacement */
    if(matches == 1)return(match);
    return(-1);			/* bad return */
}
