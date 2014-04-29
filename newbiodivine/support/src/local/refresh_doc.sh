#!/bin/bash
################################################################################
#
#  This is a script for publishing a documentation for current
#  version. It can be without
#  modification successfuly ran only on out laboratory server anna.
#
################################################################################

PLACE_ON_ANNA=/www/htdocs/divine/current_doc

function print_usage() {
  echo "$0 <flags for export from CVS>"
}

function finish() {
  if [ ! -z $TEMP_DIRECTORY ]; then
	  echo "Deleting $TEMP_DIRECTORY"
	  rm -rf "$TEMP_DIRECTORY"
  fi
  exit $1
}

#initialization of variables controling deleting after premature finish
TEMP_DIRECTORY=

if [ $# -ne 0 ]; then print_usage; finish 1; fi

if ! TEMP_DIRECTORY=`mktemp -d /tmp/publish_distribution.XXXXXXXXXX`; then
	echo "Creation of temporary directory unsuccessful"
	exit 25
fi

cd "$TEMP_DIRECTORY"
echo "Exporting current version of CVS"
export CVSROOT="$USER@anna.fi.muni.cz:/mnt/sda1/CVSroot"
export CVS_RSH=ssh
if ! cvs export -D tomorrow divine; then
  echo "Export not successful" 1>&2
  finish 5
fi
echo "Export complete"
cd divine

VERSION="current-`date +\"%k:%M_%d.%m.%Y\"`"

echo "Writing a chosen version to configuration.ac file (using vi):"
if ! vi -es +"%s/\(AC_INIT([^,]*,\)[^,]*\(,.*\)/\1 $VERSION\2/ | write | quit" configure.ac; then
        echo "Problem during run of vi" 1>&2
        finish 21
fi

echo "Running ./autogen"
if ! ./autogen; then
        echo "./autogen failed" 1>&2
        finish 20
fi
echo "Autogen successfuly completed"

if ! ./configure --datadir="$PLACE_ON_ANNA"; then
  echo "Configuration was not successful" 1>&2
  finish 6
fi

echo "Entering divine/doc in export"
cd doc
echo "Making documentation"
if ! make; then
        echo "Problems during a build of documentation"
        finish 7
fi

echo "Documentation made."
echo "Cleaning old documentation "
if ! rm -rf "$PLACE_ON_ANNA"; then
        echo "Cleaning of old documentation in $PLACE_ON_ANNA failed"
        finish 8
fi

echo "Running make install in divine/doc"
if ! make install; then
        echo "make install in divine/doc failed"
        finish 9
fi

if ! chmod -R g+w "$PLACE_ON_ANNA"; then
	echo "Warning: change of rights of $PLACE_ON_ANNA failed!"
fi
	

echo "+----------------------------------------------------------------------+"
echo "| Make & install of documentation for current version in CVS completed |"
echo "+----------------------------------------------------------------------+"
  
