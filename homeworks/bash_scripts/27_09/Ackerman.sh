#!/usr/bin bash

function ackerman {
  local tmp1; local tmp2; local tmp3; local acctmp;
  if [[ $1 == 0 ]]
  then
    echo $(($2 + 1))
  fi
  if [[ ($1 -gt 0) && ($2 == 0) ]]
  then
    tmp1=$(( $1 - 1 ))
    result=$(ackerman $tmp1 1)
    echo ${result}
  fi
  if [[ ($1 -gt 0) && ($2 -gt 0) ]]
  then
    tmp2=$(( $1 - 1 ))
    tmp3=$(( $2 - 1 ))
    acctmp=$(ackerman $1 $tmp3)
    result=$(ackerman $tmp2 $acctmp)
    echo ${result}
  fi
}

result=$(ackerman $1 $2)
echo ${result}
