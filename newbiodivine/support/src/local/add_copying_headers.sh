#!/bin/bash
################################################################################
#
#  This is a script for publishing a distribution. It can be without
#  modification successfuly ran only on out laboratory server anna.
#
################################################################################

function print_usage() {
  echo "$0 [-h]"
  echo "-h ... prints this help"
}

function finish() {
  if [ ! -z $TEMP_DIRECTORY ]; then
    echo "Deleting $TEMP_DIRECTORY"
    rm -rf "$TEMP_DIRECTORY"
  fi
  exit $1
}

TEMP_DIRECTORY=

if [ $# -gt 1 ]; then print_usage; finish 1; fi
if [ $# -eq 1 ]; then
  if [ $1 = '-h']; then print_usage; finish 0;
  else print_usage; finish 1; fi
fi

COPYING_HEADER_FILES=`find . -type f -name COPYING_HEADER`
COPYING_HEADER_FILE=
for FILE in $COPYING_HEADER_FILES; do COPYING_HEADER_FILE=$FILE; done
if [ -z "$COPYING_HEADER_FILE" ]; then
  echo "COPYING_HEADER not found" 1>&2
  finish 5
fi


if TEMP_DIRECTORY=`mktemp -d /tmp/add_copying_headers.XXXXXXXXXX`; then
  for FILE in `find . -type f -and '(' -name '*.cc' -or -name '*.hh' -or -name '*.h' -or -name '*.c' ')'`; do
    FILE_DIRNAME=`dirname $FILE`
    install -d "$TEMP_DIRECTORY/$FILE_DIRNAME"
    cat "$COPYING_HEADER_FILE" "$FILE" > "$TEMP_DIRECTORY/$FILE"
    mv "$TEMP_DIRECTORY/$FILE" "$FILE"
  done
  echo "Removing temporary directory..."
  rm -r "$TEMP_DIRECTORY"
else
  echo "Problems during run of mktemp" 1>&2
  finish 4
fi
