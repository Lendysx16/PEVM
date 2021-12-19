#!/bin/bash

x=100
str=''
while [[ $str != '269696' ]]; do
    sqr=$((x*x))
    str="${sqr}"
    str=$(echo ${str}|rev)
    str=${str::6}
    str=$(echo ${str}|rev)
    x=$((x+2))
done
echo $((x-2))
