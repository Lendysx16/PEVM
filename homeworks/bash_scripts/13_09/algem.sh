#!/bin/bash

filename="$(date "+%Y-%m-%d").log"

touch "${filename}"
text=""
while read -r text
do
  echo "$text" >> "${filename}"
done
