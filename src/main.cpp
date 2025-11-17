#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>

#include "debugger.h"

using namespace std;

int main(int argc, char* argv[]) {
	// TODO: Allow program name to be specified when running
	if (argc < 2) {
		cerr << "Please provide a program name";
		return -1;
	}

	int pid = fork();

	if (pid == 0) {
		// Tracee process
		ptrace(PTRACE_TRACEME, nullptr, nullptr);
		execl(argv[1], argv[1], nullptr);
	} else {
		// Tracer process
		Debugger dbg {argv[1], pid};		
		dbg.run();
	}

	return 0;
}	
