#! /bin/sh
############################################################################

module=conf-macros
moduledir=`echo $0 | sed 's,[^/]*$,,g'`
cvs2cl=/home/sigma/larsa/code/misc/src/cvs2cl/cvs2cl.pl
headerfile=/tmp/$module.header

############################################################################
cat > $headerfile <<ENDOFHEADER
ChangeLog
=========

This is the ChangeLog file for SIM's $module module.  This file is
automatically generated every night.  Entries are in reversed chronological
order.

See http://www.red-bean.com/~kfogel/cvs2cl.shtml for information about the
cvs2cl script used to generate this file.

============================================================================

ENDOFHEADER
############################################################################

cd $moduledir

cvs update -dP

cvs log | $cvs2cl --stdin --header $headerfile --separate-header --prune \
  --ignore 'ChangeLog$' \
  --ignore '(Makefile\.in|configure|aclocal\.m4|config\.sub|config\.guess)$' \
  --ignore '(ltconfig|ltmain\.sh|missing|mkinstalldirs|stamp-h.*|install-sh)$' \
  --ignore 'config\.h\.in$' 

rm -f ChangeLog.bak $headerfile

cvs commit -m "Automatic ChangeLog generation" ChangeLog

