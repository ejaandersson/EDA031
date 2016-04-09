#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>

#include "connection.h"

using namespace std;

struct IllegalCommandException {};

class MessageHandler {
public:
	explicit MessageHandler(Connection &conn);

	unsigned char readByte() throw (ConnectionClosedException);
	string readStr() throw (IllegalCommandException, ConnectionClosedException);
	size_t readNbr() throw (IllegalCommandException, ConnectionClosedException);
	unsigned int readUInt() throw (ConnectionClosedException);
	
	void printByte(const unsigned char &b) throw (ConnectionClosedException);
	void printStr(const string &s) throw (ConnectionClosedException);
	void printNbr(const int &num) throw (ConnectionClosedException);
	void printInt(const int &i) throw (ConnectionClosedException);
	
	private:
	Connection &con;
};


#endif