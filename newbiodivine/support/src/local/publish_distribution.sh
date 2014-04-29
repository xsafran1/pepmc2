#!/bin/bash
################################################################################
#
#  This is a script for publishing a distribution. It can be without
#  modification successfuly ran only on out laboratory server anna.
#
################################################################################

function print_usage() {
  echo "$0 [-x] <version of distribution>"
  echo "-x ... creates link from module divine to the new module"
}

function finish() {
  if [ ! -z $VERSION ]; then
    echo "Premature finish of program -> cleaning"
    delete_distribution.sh "$VERSION"
  fi
  if [ ! -z $TEMP_DIRECTORY ]; then
    echo "Deleting $TEMP_DIRECTORY"
    rm -rf "$TEMP_DIRECTORY"
  fi
  exit $1
}

#initialization of variables controling deleting after premature finish
VERSION=
TEMP_DIRECTORY=

if [ $# -eq 0 ]; then print_usage; finish 1; fi
if [ $# -gt 2 ]; then print_usage; finish 1; fi
if [ $# -eq 1 ]; then VERSION="$1"; CURRENT=yes; fi
if [ $# -eq 2 ]; then
  if [ $1 = '-x' ]; then VERSION="$2"; CURRENT=no;
  else print_usage; finish 1; fi
fi


MODULEFILE=/packages/local/modulefiles/divine-"$VERSION"
PACKAGEFILE=/packages/local/run/divine-"$VERSION"

#Writing of modulefile to the local packages directory
if [ -e "$MODULEFILE" ]; then
  echo "Modulefile $MODULEFILE exists!" 1>&2
  finish 2;
else
  echo "Creating modulefile $MODULEFILE..."
  echo "#%Module1.0" > "$MODULEFILE"
  echo "#!" >> "$MODULEFILE"
  echo "#! Title: DiVinE" >> "$MODULEFILE"
  echo "#! Version: $VERSION" >> "$MODULEFILE"
  echo "#! Description: DiVinE - installed library and tools" >> "$MODULEFILE"
  echo "#!" >> "$MODULEFILE"
  echo "" >> "$MODULEFILE"
  echo "proc ModulesHelp {} {" >> "$MODULEFILE"
  echo "global ModulesCurrentModulefile" >> "$MODULEFILE"
  echo "puts stdout \"cat /packages/local/helpfiles/\\" >> "$MODULEFILE"
  echo "\`basename $ModulesCurrentModulefile\`\"" >> "$MODULEFILE"
  echo "}" >> "$MODULEFILE"
  echo "" >> "$MODULEFILE"
  echo "prereq mpich" >> "$MODULEFILE"
  echo "" >> "$MODULEFILE"
  echo "append-path PATH $PACKAGEFILE/bin" >> "$MODULEFILE"
  echo "append-path LD_LIBRARY_PATH $PACKAGEFILE/lib" >> "$MODULEFILE"
  echo "append-path LIBRARY_PATH $PACKAGEFILE/lib" >> "$MODULEFILE"
  echo "append-path CPLUS_INCLUDE_PATH $PACKAGEFILE/include/divine" >> "$MODULEFILE"
fi

if [ -e "$PACKAGEFILE" ]; then
  echo "Package directory $PACKAGEFILE exists!" 1>&2
  finish 3;
else
  echo "Creating module directory $PACKAGEFILE..."
  mkdir "$PACKAGEFILE"
fi

if TEMP_DIRECTORY=`mktemp -d /tmp/publish_distribution.XXXXXXXXXX`; then
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
  
  if ! ./configure; then
    echo "Configuration was not successful" 1>&2
    finish 6
  fi
  
  echo "Adding licence headers to source codes"
  if ! sh ./support/src/local/add_copying_headers.sh; then
    echo "Adding licence headers was not successful" 1>&2
    finish 22
  fi
  
  echo "Making distribution (tarball)"
  if ! make dist; then
    echo "Problems during a build of distribution (tarball)" 1>&2
    finish 7
  fi
  DISTRFILE="divine-$VERSION.tar.gz"
  if [ ! -e "$DISTRFILE" ]; then
    echo "Ditribution file $DISTRFILE not found." 1>&2
    finish 8
  fi
  
  echo "Unpacking a distribution file $DISTRFILE"
  tar --gunzip -xf "$DISTRFILE"
  echo "Entering distribution directory"
  cd "divine-$VERSION"
  
  echo "Going to configure a distribution:"
  if ! ./configure --prefix=$PACKAGEFILE; then
    echo "Configuration was not successful" 1>&2
    finish 9
  fi
  
  echo "Configuration completed, calling make..."
  if ! make; then
    echo "make was not successful" 1>&2
    finish 10
  fi
  
  echo "Make completed, calling make install..."
  if ! make install; then
    echo "make install was not successful" 1>&2
    finish 11
  fi
  
  cd ..
  
  RELEASESDIRECTORY=/www/htdocs/divine/releases/
  echo "Copying $DISTRFILE to $RELEASESDIRECTORY" 
  if ! cp "$DISTRFILE" "$RELEASESDIRECTORY"; then
    echo "Copying of file failed" 1>&2
    finish 12
  fi
  
  echo "Writing a version to $RELEASESDIRECTORY/order..."
  if echo "$VERSION" > "$TEMP_DIRECTORY/order" && \
     cat "$RELEASESDIRECTORY/order" >> "$TEMP_DIRECTORY/order" && \
     mv "$TEMP_DIRECTORY/order" "$RELEASESDIRECTORY/order"; then
    echo "Success in writing $RELEASESDIRECTORY/order"
  else
    echo "Writing og $RELEASESDIRECTORY/order failed" 1>&2
  fi
  
  echo "Copying installed documentation to $RELEASESDIRECTORY"
  if ! cp -r "$PACKAGEFILE/share/doc/divine" "$RELEASESDIRECTORY/divine-$VERSION"; then
    echo "Problems during copying of documentation" 1>&2
    finish 13
  fi
  
  echo "Installation to directory $PACKAGEFILE completed"
  
  echo "Removing temporary directory..."
  cd
  rm -r "$TEMP_DIRECTORY"
  
  if [ "$CURRENT" = yes ]; then  #if flag -x is set
	  echo "Linking module divine to module divine-$VERSION"
	  link_module_divine.sh "$VERSION"
  fi
	  
  echo "Publishing of release divine-"$VERSION" finished"
else
  echo "Problems during run of mktemp" 1>&2
  finish 4
fi

