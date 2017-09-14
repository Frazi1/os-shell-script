#!/usr/bin/awk -f
BEGIN{
	dates[""]=0
	err_cnt=0
}
{
	date=$1
	err_code=$2
	if( err_code > 399 && err_code < 500 ){
		dates[date]++
		err_cnt++
		print date, dates[date], dates[date]/err_cnt*100
	}
}
END{}
