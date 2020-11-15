#!/usr/bin/bash

fail(){
  echo " >> Error: Install failed!"
  exit 1
}

type=$1

echo " >> Installing Terminal MineSweeper..."

if [ "$type" == "--install-to-here" ]
then
  echo " :: Install to here..."
  tbin="./tminesweeper"
  tdir="."
  tusr="tminesweeper-bin"
  drun="./tminesweeper-bin/tminesweeper"
else
  echo " :: Install to computer"
  tbin="/usr/bin/tminesweeper"
  tdir="/usr/share"
  tusr="tminesweeper"
  drun="tminesweeper"
fi


echo "    -> Downloading source..."
#mkdir -p "/usr/share/minesweeper"
cd $tdir
git clone https://github.com/langong-dev/tminesweeper.git $tusr

echo "    -> Putting files..."
cd $tusr

echo "const char initsh[100]=\"bash $tdir/$tusr/init.sh\";" > df.hpp
echo "const char uninstallsh[100]=\"bash $tdir/$tusr/uninstall.sh\";" >> df.hpp

g++ main.cpp -o $tbin

echo " >> Checking..."

echo "    -> Checking $tbin"

if [ ! -f "$tbin" ]; then
  fail
fi

echo "    -> Checking $tdir/$tusr/init.sh"

if [ ! -f "init.sh" ]; then
  fail
fi

echo "    -> Checking $tdir/$tusr/uninstall.sh"

if [ ! -f "uninstall.sh" ]; then
  fail
fi

echo " >> Installed Terminal MineSweeper."
echo "    -> Use '$drun' to start game"
echo "    -> Use '$drun init' to setup user"
echo "    -> Use '$drun uninstall' to uninstall game"


