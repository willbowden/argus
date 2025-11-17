#include <stdlib.h>
#include <string>

class Debugger {
public:
	Debugger(std::string program_name, pid_t pid) 
		: m_program_name {std::move(program_name)}, m_pid {pid} {}

	void run();

private:
	std::string m_program_name;
	pid_t m_pid;
};
