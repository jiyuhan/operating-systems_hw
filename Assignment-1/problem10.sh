#!/bin/bash
tar xzf zip_directory.tar.gz
mkdir -p ./zip_directory/JPG/
for filename in ./zip_directory/*.jpg; do
    mv $filename ./zip_directory/JPG/
done
mkdir -p ./zip_directory/TXT/
for filename in ./zip_directory/*.txt; do
    mv $filename ./zip_directory/TXT/
done
tar -zcvf zip_directory_zipped.tar.gz zip_directory
rm -r zip_directory
