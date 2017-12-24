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
	# 	print date " - " dates_errs[date] " - " dates_errs[date]/err_cnt*100 "%"
		printf "%s - %d - %.1f%%\n", date, dates_errs[date], dates_errs[date]/err_cnt*100
	}
}


{
	split($4, newdd, \":\");
	if (newdd[1]==\"[18/Oct/2006\"){
		split($11,output_array,\" \");
		if(output_array[1]!=\"\\\"-\\\"\")
			{ sum[output_array[1]] += 1 }}} 
   	END {
   	 PROCINFO[\"sorted_in\"]=\"@val_num_desc\";
   	  pos = 1; for(i in sum)
   	  { if (pos <= 10) 
   	  {total=total+sum[i]}
   	   pos++;
   	};
   	pos = 1;
   	 for(i in sum)
   	 {
   	 	if (pos <= 10){
   	 		printf(\"%d. %s - %d - %f%%\\n\",  pos, i, sum[i], sum[i]/total*100);pos++;}
   	 	}
   	 }