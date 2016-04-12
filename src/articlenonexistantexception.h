#ifndef ARTICLENONEXISTANTEXCEPTION_H
#define ARTICLENONEXISTANTEXCEPTION_H

#include <string>

struct ArticleNonexistantException {
	std::string message = "The article does not exist.";
};

#endif
