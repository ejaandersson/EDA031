#ifndef NEWSGROUPALREADYEXISTS_H
#define NEWSGROUPALREADYEXISTS_H

#include <string>

struct NewsGroupAlreadyExistsException {
	std::string message = "The news group already exist.";
};

#endif
