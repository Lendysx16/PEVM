#!/bin/bash

if [[ $# -gt 0 ]]
then
  word="${1}"
  reversed_word=$(echo "${word}"|rev)
  if [[ "${word}" == "${reversed_word}" ]]
  then
    echo "Word is palindrome"
  else
    echo "Word is not palindrome"
  fi
else
  echo "No arguments added"
fi
