#!/usr/bin/awk -f
BEGIN{
	dates_errs[""]=0
	err_cnt=0
}
{
	date=$1
	err_code=$2
	if(err_code > 399 && err_code < 500){
		dates_errs[date]++
		err_cnt++
	}
}
END{
	for(date in dates_errs) {
	#	print date " - " dates_errs[date] " - " dates_errs[date]/err_cnt*100 "%"
		printf "%s - %d - %.1f%%\n", date, dates_errs[date], dates_errs[date]/err_cnt*100
	}
}
