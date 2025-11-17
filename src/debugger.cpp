#include <stdlib.h>
#include <sys/wait.h>
#include "debugger.h"

void Debugger::run() {
	int wait_status;
	waitpid(m_pid, &wait_status, 0);

	while (true) {
		char c = getchar();
		putchar(c);
	}
}
