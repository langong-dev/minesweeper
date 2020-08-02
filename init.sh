#!/usr/bin/bash


echo " Preparing for user '$USER'"

path="$HOME/.local/share/minesweeper/"

echo 0 > "$path/level"
echo $USER > "$path/user"
echo "" > "$path/log"

echo " OKay!"
