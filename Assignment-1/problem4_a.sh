#!/bin/bash

counter=0
for filename in ./XML_FILES/*.xml; do
    if grep -q -m 1 "<name>car</name>" $filename; then
        counter=$((counter+1))
    fi
done

echo "$counter"
