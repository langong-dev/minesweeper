#!/usr/bin/bash


echo " Preparing for user '$USER'"

ipath="$HOME/.local/share/minesweeper/"

mkdir -p $ipath

echo 0 > "$ipath/level"
echo $USER > "$ipath/user"
echo "" > "$ipath/log"

echo " OKay!"
