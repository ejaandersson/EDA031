#ifndef NEWSGROUPNONEXISTANTEXCEPTION_H
#define NEWSGROUPNONEXISTANTEXCEPTION_H

#include <string>

struct NewsGroupNonexistantException {
	std::string message = "The news group does not exist.";
};

#endif
