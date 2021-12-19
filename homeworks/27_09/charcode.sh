#!/usr/bin/bash


for (( i=33; i<=255; i++))
  do
    printf "$i - "
    printf "\x$(printf %x $i)"
    printf '\n'
  done
