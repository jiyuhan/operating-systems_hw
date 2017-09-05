#!/bin/bash
tar xzf zip_directory.tar.gz
for filename in ./zip_directory/*.*; do
    if grep -e "*.jpg" $filename; then
        echo "$filename"
    elif grep -e "*.txt" $filename; then
        echo "$filename"
    fi
done
