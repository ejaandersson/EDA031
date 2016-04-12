#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>

#include "connection.h"

using namespace std;

struct IllegalCommandException {};

class MessageHandler {
public:
	explicit MessageHandler(net::Connection &conn);
	
	void newConnection(const Connection& conn);
	
	void sendCode(int code) throw(ConnectionClosedException);
	void sendByte(int code);
	
	void sendInt(int value) throw(ConnectionClosedException);
	void sendIntParam(int i) throw(ConnectionClosedException);
	void sendStrParam(const string& str) throw(ConnectionClosedException);
	
	int getCode() throw(ConnectionClosedException);
	int getByte();
	
	int getInt() throw(ConnectionClosedException);
	int getIntParam() throw(ConnectionClosedException, IllegalCommandException);
	string getStrParam() throw(ConnectionClosedException, IllegalCommandException);
	
	private:
	Connection &con;
};


#endif
