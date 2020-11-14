#!/usr/bin/bash

fail(){
  echo " >> Error: Install failed!"
  exit 1
}


echo " >> Installing Terminal MineSweeper..."

echo "    -> Downloading source..."
#mkdir -p "/usr/share/minesweeper"
cd /usr/share
git clone https://github.com/langong-dev/tminesweeper.git

echo "    -> Putting files..."
cd tminesweeper
g++ main.cpp -o /usr/bin/tminesweeper


echo " >> Checking..."

echo "    -> Checking /usr/bin/tminesweeper"

if [ ! -f "/usr/bin/tminesweeper" ]; then
  fail
fi

echo "    -> Checking /usr/share/tminesweeper/init.sh"

if [ ! -f "init.sh" ]; then
  fail
fi

echo "    -> Checking /usr/share/tminesweeper/uninstall.sh"

if [ ! -f "uninstall.sh" ]; then
  fail
fi

echo " >> Installed Terminal MineSweeper."
echo "    -> Use 'tminesweeper' to start game"
echo "    -> Use 'tminesweeper init' to setup user"


