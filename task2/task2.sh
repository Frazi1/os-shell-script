#!/usr/bin/env bash
cat log.txt |
  awk '{print $4, $9}'|
  cut -c 2-|
  grep "[[:space:]]4" |
  sed 's/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g' |
  sed 's/\//-/g' |
  uniq -c1 |
  sort -nrk 1 |
  head -10
