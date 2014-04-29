#!/bin/bash
################################################################################
#
#  This is a script for deleting of distribution
#  It comes handy in case of incorrect or incomplete distribution published.
#
################################################################################

function print_usage() {
  echo "$0 <version of distribution>"
}

if [ ! $# -eq 1 ]; then print_usage; exit 1; fi

VERSION=$1

MODULEFILE=/packages/local/modulefiles/divine-"$VERSION"
echo "Trying to delete modulefile $MODULEFILE:"

if [ -e "$MODULEFILE" ]; then
	if rm -f "$MODULEFILE"; then
		echo "$MODULEFILE deleted"
	else
		echo "Deletion of $MODULEFILE failed - ignoring"
	fi
else
	echo "$MODULEFILE not found - ignoring"
fi

PACKAGEFILE=/packages/local/run/divine-"$VERSION"
echo "Trying to delete directory of module $PACKAGEFILE:"

if [ -e "$PACKAGEFILE" ]; then
	if rm -rf "$PACKAGEFILE"; then
		echo "$PACKAGEFILE deleted"
	else
		echo "Deletion of $PACKAGEFILE failed - ignoring"
	fi
else
	echo "$PACKAGEFILE not found - ignoring"
fi

RELEASESDIRECTORY=/www/htdocs/divine/releases
TARBALLPATH="$RELEASESDIRECTORY/divine-$VERSION.tar.gz"
echo "Trying to delete a tarball $TARBALLPATH"
if [ -e "$TARBALLPATH" ]; then
	if rm -f "$TARBALLPATH"; then
		echo "$TARBALLPATH deleted"
	else
		echo "Deletion of $TARBALLPATH failed - ignoring"
	fi
else
	echo "$TARBALLPATH not found - ignoring"
fi

RELDOCPATH="$RELEASESDIRECTORY/divine-$VERSION"
echo "Trying to delete a documentaion for a release divine-$VERSION"
if [ -e "$RELDOCPATH" ]; then
	if rm -rf "$RELDOCPATH"; then
		echo "$RELDOCPATH deleted"
	else
		echo "Deletion of $RELDOCPATH failed - ignoring"
	fi
else
	echo "$RELDOCPATH not found - ignoring"
fi

echo "Trying to delete a version from $RELEASESDIRECTORY/order"
cat "$RELEASESDIRECTORY/order" | grep -v "^$VERSION\$" >"$RELEASESDIRECTORY/order.tmp" && mv "$RELEASESDIRECTORY/order.tmp" "$RELEASESDIRECTORY/order";

