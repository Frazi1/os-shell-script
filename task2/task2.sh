cat log.txt |
  awk '{print $4, $9}'|
  cut -c 2-|
  sed 's/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g' |
  sed 's/\//-/g' |
  grep " 4" |
  uniq -c1 |
  sort -nrk 1 |
  head -10
