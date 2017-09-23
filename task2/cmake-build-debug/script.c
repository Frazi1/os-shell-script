#include <unistd.h>

void createPipe(void (*pf)(void), void (*chf)(void));
void cntError();
void removeQuotes();
void sort();
void getTop();
void secondThirdPipe();
void firstSecondPipe();
void firstPipe();

int main(void)
{
	firstPipe();
	return 0;
}

void cntError()
{
	execlp("./cnt-error.awk", "./cnt-error.awk", "log.txt", (char*)NULL);
}

void removeQuotes()
{
	execlp("/bin/sed", "/bin/sed", "s/\"//g", (char*) NULL);
}

void sort()
{
	execlp("/bin/sort", "/bin/sort", "-nrk", "2", (char*) NULL);
}

void getTop()
{
	execlp("/bin/head", "/bin/head", "-n", "10", (char*) NULL);
}


void secondThirdPipe()
{
	createPipe(sort, getTop);
}

void firstSecondPipe()
{
	createPipe(removeQuotes, secondThirdPipe);
}

void firstPipe()
{
	createPipe(cntError, firstSecondPipe);
}

void createPipe(void (*pf)(void), void (*chf)(void))
{
	int fd[2];
	pipe(fd);
	if (fork())
	{
		//parent
		close(fd[0]);
		if (fd[1] != 1)
		{
			dup2(fd[1], 1);
		}
		pf();
	}
	else
	{
		//child
		close(fd[1]);
		if (fd[0] != 0)
		{
			dup2(fd[0], 0);
		}
		chf();
	}
}





	
