.data
    # массив для вызова cat log.txt
    cmd_cat: .string "/bin/cat"
    arg_cat: .string "log.txt"
    args_cat: .long cmd_cat, arg_cat, 0
    env_cat: .long 0

    # массив для вызова awk
    cmd_awk: .string "/usr/bin/awk"
    arg_awk: .string "{split($4, newdd, \":\"); if (newdd[1]==\"[18/Oct/2006\") {split($11,output_array,\" \"); if(output_array[1]!=\"\\\"-\\\"\"){ sum[output_array[1]] += 1 }}} END { PROCINFO[\"sorted_in\"]=\"@val_num_desc\"; pos = 1; for(i in sum){ if (pos <= 10) {total=total+sum[i]} pos++;};pos = 1; for(i in sum){if (pos <= 10){printf(\"%d. %s - %d - %f%%\\n\",  pos, i, sum[i], sum[i]/total*100);pos++;}}}"
   args_awk: .long cmd_awk, arg_awk, 0
    env_awk: .long 0
	
    # массив файловых дескрипторов для pipe
    fds: .int 0, 0   

.text
.globl _start
_start:
        # вызов pipe(fds)
        pushl $fds
        call pipe

        # вызов fork()
        call fork

        # переход к коду дочернего процесса для cat,
        # если fork вернул 0
        cmpl $0, %eax
        je child_cat

        # вызов fork() в родительском процессе
        call fork
        # переход к коду дочернего процесса для awk,
        # если fork вернул 0
        cmpl $0, %eax
        je child_awk

        # close(fd[0]) в родительском процессе
        movl $fds, %eax
        pushl 0(%eax)
        call close

        # close(fd[1]) в родительском процессе
        movl $fds, %eax
        pushl 4(%eax)
        call close

        # вызов wait(NULL) - для cat
        pushl $0
        call wait

        # еще один вызов wait(NULL) - для awk
        pushl $0
        call wait

finish:
        # вызов exit(0)
        movl $1, %eax
        movl $0, %ebx
        int $0x80

# код дочернего процесса для cat
child_cat:
        # вызов dup2(fds[1],1)
        pushl $1
        movl $fds, %eax
        pushl 4(%eax)
        call dup2

        # вызов close(fds[0]), close(fds[1])
        movl $fds, %eax
        pushl 0(%eax)
        call close
        movl $fds, %eax
        pushl 4(%eax)
        call close

        # вызов execve(cmd_cat, args_cat, env_cat)
		pushl $env_cat
        pushl $args_cat
        pushl $cmd_cat
        call execve

        call finish

# код дочернего процесса для awk
child_awk:
        # вызов dup2(fds[0],0)
        pushl $0
        movl $fds, %eax
        pushl (%eax)
        call dup2

        # вызов close(fds[0]), close(fds[1])
        movl $fds, %eax
        pushl 0(%eax)
        call close
        movl $fds, %eax
        pushl 4(%eax)
        call close

        # вызов execve(cmd_awk, args_awk, env_awk)
		pushl $env_awk
        pushl $args_awk
        pushl $cmd_awk
        call execve

        call finish
