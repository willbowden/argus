#include <stdlib.h>
#include <sys/wait.h>
#include <string>
#include <sys/ptrace.h>

#include "debugger.h"
#include "utils.h"
#include "../include/linenoise.hpp"

void Debugger::run() {
	int wait_status;
	waitpid(m_pid, &wait_status, 0);
	
	linenoise::linenoiseState ln("\033[0;32margus>\033[0m ");

	// Enable the multi-line mode
    ln.EnableMultiLine();

    // Set max length of the history
    ln.SetHistoryMaxLen(4);

	while (true) {
		std::string line;
	    auto quit = ln.Readline(line);

    	if (quit) {
        	break;
	    }

		handle_command(line);
		ln.AddHistory(line.c_str());
		}
}

void Debugger::handle_command(const std::string& line) {
	std::vector<std::string> args = split(line, ' ');
	if (args.size() == 0) { return; }

	std::string command = args[0];

	if (is_prefix(command, "cont")) {
		continue_execution();
	} else {
		std::cerr << "Unknown command" << std::endl;
	}
}

void Debugger::continue_execution() {
	ptrace(PTRACE_CONT, m_pid, nullptr, nullptr);
	
	int wait_status;
	waitpid(m_pid, &wait_status, 0);
	std::cout << "Continued" << std::endl;
}
