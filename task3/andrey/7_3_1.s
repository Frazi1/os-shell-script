.data
    # массив для вызова cat log.txt
    cmd_cat: .string "/bin/cat"
    arg_cat: .string "log.txt"
    args_cat: .long cmd_cat, arg_cat, 0
    env_cat: .long 0

    # массив для вызова awk -F
    cmd_wc: .string "/usr/bin/awk"
    arg_wc: .string "{split($0, pr, \"\\\"\"); split(pr[1], sec, \"\[\"); split(sec[2], th, \"\:\"); split(pr[3], res, \"\"); if(res[2]==\"4\"){sum[th[1]]+=1}} END {for(i in sum){print i, sum[i]}}"
    args_wc: .long cmd_wc, arg_wc, 0
    env_wc: .long 0
	
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
        # переход к коду дочернего процесса для wc,
        # если fork вернул 0
        cmpl $0, %eax
        je child_wc

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

        # еще один вызов wait(NULL) - для wc
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

# код дочернего процесса для wc
child_wc:
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

        # вызов execve(cmd_wc, args_wc, env_wc)
		pushl $env_wc
        pushl $args_wc
        pushl $cmd_wc
        call execve

        call finish
