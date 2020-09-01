#+
#  Name:
#     edhead.sed

#  Purpose:
#     Select and concatenate lines of hypertext that require link-editing.

#  Type of Module:
#     Commented part-script for the UNIX "sed" utility

#  Description:
#     This file contains "sed" commands that constitute the first part of an
#     editing script used to link-edit lines of hypertext by substituting
#     references to external labels with appropriate URLs. It should be
#     supplied to the "sed" utility in conjunction with (a) the set of "sed"
#     substitution ("s") commands that insert the new URLs and (b) the
#     "edtail.sed" script that subsequently reverses the modifications made by
#     this script.
#
#     The first purpose of this script is to concatenate any broken input lines
#     so that complete HTML anchor expressions of the form:
#
#        <A ... HREF="xxx" ... >
#
#     are presented to the subsequent URL substitution commands.
#
#     Its second purpose is to select (address) only those input lines which
#     contain URLs which may require modification. This is done to improve
#     efficiency, so that URL substitution is not attempted on the (often many)
#     irrelevant lines in the input.

#  Invocation:
#     cat input_text | sed -n -f edhead.sed -e subs1 -e subs2 ... -f edtail.sed

#  Parameters:
#     input_text
#        The input lines supplied to "sed" should contain the original lines of
#        hypertext (HTML), each prefixed with the name of the file from which
#        it originates and a colon (i.e. "filename:text"). Lines from different
#        files can be concatenated, but not interleaved. The file name must be
#        given relative to the hypertext document directory, as it will be used
#        to generate the appropriate relative URL. For example, a line from the
#        file "doc.htx/subdir/node.html" should appear as:
#
#           subdir/node.html:text
#
#     subs1, subs2, ...
#        The "sed" substitution commands that perform the link-editing.

#  Notes:
#     -  This script is not valid on its own as a "sed" script as it ends with
#     unbalanced brackets. It must be followed by the "edtail.sed" script that
#     closes the brackets and generates the required output from "sed". This
#     output is in the same form as the input, with original line breaks
#     restored.
#     -  This script contains comments. To convert it into a legal "sed" script
#     these should be removed.
#     -  The combined length of this script and of the "edtail.sed" script
#     must be shorter (and preferably much shorter) than the limits on 
#     total length of a "sed" script required by the "multised" script.

#  Implementation Deficiencies:
#     -  Trailing white space on some input lines may be deleted by this
#     script.
#     -  The regular expressions used to match HTML constructs may be more
#     general than necessary (i.e. may allow for possibilities that HTML
#     browsers do not themselves recognise).

#  Copyright:
#     Copyright (C) 1995 The Central Laboratory of the Research Councils

#  Authors:
#     RFWS: R.F. Warren-Smith (Starlink, RAL)
#     {enter_new_authors_here}

#  History:
#     23-FEB-1995 (RFWS):
#        Original version.
#     27-FEB-1995 (RFWS):
#        Modified line addressing for greater efficiency.
#     {enter_further_changes_here}

#  Bugs:
#     {note_any_bugs_here}
#-

#  Select lines ending in "<" or "<A" or similar, with any amount of white
#  space (including newlines) following. These lines must be completed as they
#  may contain the start of an anchor expression. Join them with the following
#  line.
      :concat
      /<\n\{0,1\}[ 	]*[aA]\{0,1\}\n\{0,1\}[ 	]*$/{
         N

#  Delete the "filename:" that follows the newline introduced by the line
#  concatenation.
         s%\(.*\n\)[^:]*:\(.*\)$%\1\2%

#  Delete any spaces or tabs immediately in front of a newline. This
#  corresponds to deleting white space at the ends of input lines. This is
#  necessary because some implementations of "sed" do not seem able to match
#  white space with arbitrary occurrences of newlines in it. This approach
#  ensures that newlines always appear at the front of white space, making
#  them easier to match.
         s%[ 	][ 	]*\(\n\)%\1%

#  Branch back to see if the line needs further concatenation.
         b concat
      }

#  Similarly, select and concatenate lines ending in "<A xxx" (where "xxx"
#  doesn't contain a ">" character), since these also contain incomplete
#  anchor expressions.
      /<\n\{0,1\}[ 	]*[aA]\n\{0,1\}[ 	][^>]*$/{
         N
         s%\(.*\n\)[^:]*:\(.*\)$%\1\2%
         s%[ 	][ 	]*\(\n\)%\1%
         b concat
      }

#  Now address those lines containing the magic "xref_" string which appears
#  in all URLs associated with cross references. This improves efficiency by
#  greatly reducing the number of lines that must be considered subsequently.
      /xref_/{

#  Further select only those lines containing the "HREF" string which appears
#  in cross references to other documents (this eliminates lines containing
#  only labels - i.e. the targets that cross references point at).
         /[hH][rR][eE][fF]/{

#  Make sure that any HTML anchor starting "<a\n" gets a space inserted before
#  the newline. This is done simply to make matching these patterns easier
#  from here on.
            s%\(<\n*[ 	]*[aA]\)\(\n[^>]*>\)%\1 \2%g

#  Clear the "sed" substitution flag with a dummy test so that we can tell
#  which lines get modified by link-edit commands between here and the
#  invocation of the "edtail.sed" script.
            t clear
            :clear

#  End of script.
