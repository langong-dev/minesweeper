#!/usr/bin/bash

echo " >> Uninstall MineSweeper"

cd /usr/share
rm -rf minesweeper

cd /usr/bin
rm -f MineSweeper

echo " >> Uninstalled MineSweeper"

