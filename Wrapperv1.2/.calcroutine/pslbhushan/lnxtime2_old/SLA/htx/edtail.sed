#+
#  Name:
#     edtail.sed

#  Purpose:
#     Tidy up hypertext lines after link-editing.

#  Type of Module:
#     Commented part-script for the UNIX "sed" utility

#  Description:
#     This file contains "sed" commands that constitute the final part of an
#     editing script used to link-edit lines of hypertext by substituting
#     references to external labels with appropriate URLs. It should be
#     supplied to the "sed" utility in conjunction with (a) the "edhead.sed"
#     script that initially prepares lines of hypertext for link-editing and
#     (b) the set of "sed" substitution ("s") commands that insert the new
#     URLs.
#
#     The first purpose of this script is to insert relative file path prefixes
#     into any cross-reference URLs that require them (indicated by a missing
#     file path prefix in the document name after link-editing).
#
#     Its second purpose is to remove embedded newlines from the text,
#     splitting it into multiple output lines (each with the appropriate
#     "filename:" prefix) so as to restore the line breaks present in the
#     original input text.

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
#     -  This script is not valid on its own as a "sed" script as it starts
#     with unbalanced brackets. It must be preceded by the "edhead.sed" script
#     that opens the brackets and accepts the input text via "sed".
#     -  This script contains comments. To convert it into a legal "sed" script
#     these should be removed.
#     -  The combined length of this script and of the "edtail.sed" script
#     must be shorter (and preferably much shorter) than the limits on 
#     total length of a "sed" script required by the "multised" script.

#  Implementation Deficiencies:
#     The regular expressions used to match HTML constructs may be more general
#     than necessary (i.e. may allow for possibilities that HTML browsers do
#     not themselves recognise).

#  Copyright:
#     Copyright (C) 1995 The Central Laboratory of the Research Councils

#  Authors:
#     RFWS: R.F. Warren-Smith (Starlink, RAL)
#     {enter_new_authors_here}

#  History:
#     18-APR-1995 (RFWS):
#        Original version.
#     {enter_changes_here}

#  Bugs:
#     {note_any_bugs_here}
#-

#  Test if the current line has been link-edited (i.e. whether substitutions
#  have been made since it was processed by the "edhead.sed" script). If not,
#  branch to the "same" label to skip the insertion of relative path prefixes.
            t filenm
            b same
            :filenm

#  Substitute relative path prefixes.
#  ---------------------------------
#  Start constructing the relative path prefix required by making a duplicate
#  copy of the filename prefix (i.e. the name of the file containing the
#  current line) at the start of the line. Separate this copy from the rest
#  of the line's contents with a newline character.
            s%^\([^:]*\)\(:.*\)%\1/\
\1\2%

#  So that we can distinguish this first newline from any others, mark all
#  newlines present by appending "#" to them and identify the first one by
#  changing its "#" to a " ".
            s%\(\n\)%\1#%g
            s%\(\n\)#%\1 %

#  Also mark all "/" characters present by appending "#" to them. This allows
#  them to be distinguished from the new "/" characters that will now be
#  introduced.
            s%/%/#%g

#  Loop to replace all file name fields occurring before the first newline
#  (i.e. in the duplicate file name we added above) with "../". This constructs
#  the relative path prefix required to go from the ".html" file containing the
#  current line up to the directory containing the document in which the line
#  appears (which will also be the directory containing the referenced
#  document). Quit looping when no more substitutions occur (i.e. when all
#  occurrences of "/#" in the file name have been processed).
            :field
               s%^[^/][^/]*/#\(.*\)\(\n \)%\1../\2%
            t field

#  Remove the "#" flag from any remaining "/" characters.
            s%/#%/%g

#  Move the relative path prefix we have just constructed to the end of the
#  line. This is done so that it can be more easily matched and substituted
#  into the URLs where it is needed. Change the " " that follows the separating
#  newline into a "#" in the process.
            s%^\(.*\)\(\n\) \(.*\)$%\3\2#\1%

#  Remove all the distinguishing "#" flags from embedded newlines.
            s%\(\n\)#%\1%g

#  Match complete lines that contain anchor expressions (with "HREF"
#  parameters) whose URLs specify cross-references to documents but without a
#  file path prefix. Substitute in a copy of the prefix we have just
#  constructed and stored at the end of the line. Loop to repeat this process
#  (in case the line contains several such anchors) until no more substitutions
#  occur.
            :prefix
               s%^\(.*<\n*[ 	]*[aA][ 	]\n*[^>]*[hH][rR][eE][fF]\n*[ 	]*=\n*[ 	]*"\)\([^ 	"/]*\.htx/[^ 	"]*#xref_[^  "]*"[^>]*>.*\)\(\n\(.*\)\)%\1\4\2\3%
            t prefix

#  Once the relative path prefix has been pasted in where necessary, delete
#  the original copy by removing everything from the last newline onwards.
            s%^\(.*\)\n.*%\1%

#  Arrive at this point when all necessary relative path prefixes have been
#  added, or directly if no link-edits were performed on the current line.
            :same

#  These brackets mark the end of the line selection performed by the
#  "edhead.sed" script. Subsequently, we see all the input text lines, not
#  just those containing cross-reference anchor expressions.
         }
      }

#  Split up lines for output.
#  -------------------------
#  Clear the "sed" substitution flag with a dummy test.
      t mark
      : mark

#  Mark all newlines embedded in the text by appending a "#" to them. Test to
#  see if a substitution occurred. If not, then there are no newlines present.
#  In this case, simply print out the line and delete the pattern space (which
#  starts a new cycle to read the next input line).
      s%\(\n\)%\1#%g
      t newline
      p
      d

#  If embedded newlines are present, distinguish the first one by changing its
#  following "#" to a " ".
      :newline
          s%\(\n\)#%\1 %

#  Copy the file name prefix (including the colon) from the start of the line
#  to a point just after the first embedded newline and following " " (i.e. to
#  where the next output line will start).
          s%^\(\([^:]*:\).*\n \)%\1\2%

#  Print out the contents of the pattern space up to the first newline and then
#  remove the characters that were printed together with the newline and
#  following " ".
          P
          s%.*\n %%

#  If a substitution occurred (i.e. embedded newlines were found above), then
#  branch back to see if there are any more. If none were found above, then the
#  entire contents of the pattern space will have been printed out, so ignore
#  anything that remains.
      t newline

#  End of script.
