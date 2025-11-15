#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char* argv[]) {
	int wait_status;

	if (argc < 2) {
		cerr << "Please provide a program name";
		return -1;
	}

	int pid = fork();

	if (pid == 0) {
		puts("Child!");
		ptrace(PTRACE_TRACEME, nullptr, nullptr);
		execl(argv[1], argv[1], nullptr);
	} else {
		puts("Parent!");
		waitpid(pid, &wait_status, 0);
		char c = getchar();
		putchar(c);
	}

	return 0;
}	
