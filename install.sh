#!/usr/bin/bash

fail(){
  echo " >> Error: Install failed!"
  exit 1
}


echo " >> Installing MineSweeper..."

echo "    -> Downloading sorces..."
mkdir -p "/usr/share/minesweeper"
cd /usr/share
git clone https://github.com/langong-dev/minesweeper.git

echo "    -> Putting files..."
cd minesweeper
g++ main.cpp -o /usr/bin/MineSweeper


echo " >> Checking..."

echo "    -> Checking /usr/bin/MineSweeper"

if [ ! -f "/usr/bin/MineSweeper" ]; then
  fail
fi

echo "    -> Checking /usr/share/minesweeper/init.sh"

if [ ! -f "init.sh" ]; then
  fail
fi

echo "    -> Checking /usr/share/minesweeper/uninstall.sh"

if [ ! -f "uninstall.sh" ]; then
  fail
fi

echo " >> Installed MineSweeper."

