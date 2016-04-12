#include <string>

#ifndef ILLEGAL_COMMAND_EXCEPTION_H
#define ILLEGAL_COMMAND_EXCEPTION_H

struct IllegalCommandException {
	std::string message;
	std::string error;
	int protMessage;
	int codeNumber;
	IllegalCommandException(std::string m, int prot, int code) : message(m), protMessage(prot), codeNumber(code) {}
	
	IllegalCommandException(std::string m, std::string em) : message(m), error(em) {}
};
#endif