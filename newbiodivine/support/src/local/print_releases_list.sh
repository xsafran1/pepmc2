#!/bin/bash
################################################################################
#
#  This is a script for creating XML file for xweb source of DiVinE web
#  It can be without
#  modification successfully ran only on out laboratory server anna.
#
################################################################################

PLACE_ON_ANNA=/www/htdocs/divine/releases
WWW_PLACE_ON_ANNA=../releases

echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
echo "<html>"
echo "  <head>"
echo "    <title>DiVinE Library Download</title>"
echo "  </head>"
echo "  <body>"
echo "    <h1 align=\"center\">DiVinE Library - Download</h1>"


echo "<h2>License</h2>"

echo "DiVinE Library is available for non-commercial use under the GNU General Public License.<br/>"
echo "<br/>"


echo "<font face=\"courier\">"
echo "DiVinE Library is a software product to support cluster-based formal verification.<br/>"
echo "Copyright (C) 2005  DiVinE Development Team<br/>"
echo "<br/>"
echo "This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version."
echo "<br/>"
echo "<br/>"
echo "This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details."
echo "<br/>"
echo "<br/>"
echo "You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA."
echo "</font>"
echo "<br/>"
echo "<br/>"


LATEST=`cat "$PLACE_ON_ANNA"/order|head -n 1`
echo "<h2> Latest release </h2>"

echo "The latest version of DiVinE Library is version $LATEST. It can be downloaded in a single tar.gz archive 
<a href=\"$WWW_PLACE_ON_ANNA/divine-$LATEST.tar.gz\">divine-$LATEST.tar.gz</a>.<br/>"
echo "Documentation to the latest DiVinE Library interface is available in the form of a "
echo "<a href=\"$WWW_PLACE_ON_ANNA/divine-$LATEST/refs/library/html/index.html\">reference manual</a>. Further documentation can be found <a href=\"$WWW_PLACE_ON_ANNA/divine-$LATEST/\">here</a>."
echo "<br/>"

echo "<h2>Install instructions</h2>"

echo "Perform the following steps in order to install DiVinE Library. Note that for successful installation the GCC compatible compiler and MPI version 1.2 library must be properly installed and available on your system."


echo "<ul>"
echo "<li> Download the latest release "
echo "<a href=\"$WWW_PLACE_ON_ANNA/divine-$LATEST.tar.gz\">here</a></li>"
echo "<li> Use tar and gunzip to extract files from downloaded archive.<br/>"
echo "<font face=\"courier\">tar xvzf divine-x.y.z.tar.gz</font></li>"
echo "<li> Enter the DiVinE Library installation directory.<br/><font face=\"courier\">cd divine-x.y.z </font></li>"
echo "<li> List and configure install options. <br/>"
echo "<font face=\"courier\">./configure --help<br/>./configure [name your options]</font></li>"
echo "<li> Compile DiVinE Library. <br/><font face=\"courier\"> make </font></li>"
echo "<li> Install DiVinE Library. <br/><font face=\"courier\"> make install </font></li>"
echo "</ul>"






RELEASES_AUX=`cat "$PLACE_ON_ANNA"/order`
RELEASES=`echo $RELEASES_AUX`
FIRST=yes
SECOND=no
for RELEASE in $RELEASES; do
  if [ $FIRST = yes ]; then
    SECOND=yes;
    FIRST=no;
    continue;
  fi    
  if [ $SECOND = yes ]; then
    SECOND=no;
    echo "<h2>Old releases</h2>"
    echo "Below we list old public releases of DiVinE Library with appropriate link to corresponding version of Library interface documentation."
  fi
  TARGZNAME="divine-$RELEASE.tar.gz"
  DOCDIRNAME="divine-$RELEASE"
    echo "<br/>"
    echo "<a href=\"$WWW_PLACE_ON_ANNA/$TARGZNAME\">DiVinE $RELEASE</a>, "
    echo "       <a href=\"$WWW_PLACE_ON_ANNA/$DOCDIRNAME/\">reference manual $RELEASE</a>"
done

echo "  </body>"
echo "</html>"




