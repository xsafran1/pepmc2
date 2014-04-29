#!/bin/bash
################################################################################
#
#  This is a script for linking of module divine to the module of divine with
#  given version. It can be without
#  modification successfuly ran only on out laboratory server anna.
#
################################################################################

function print_usage() {
  echo "$0 <version of distribution>"
}

if [ $# -eq 1 ]; then
	VERSION="$1";
else
	echo "Bad number of parameters" 1>&2
	print_usage
	exit 1
fi

echo "Creating a link:"
echo "/packages/local/modulefiles/divine"
echo "   -->  "
echo "/packages/local/modulefiles/divine-$VERSION"
if ! ln -sf /packages/local/modulefiles/divine-"$VERSION" /packages/local/modulefiles/divine; then
	echo "Problem during creation of link!" 1>&2
	exit 2
fi

