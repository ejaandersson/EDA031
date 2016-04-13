#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "illegalcommandexception.h"

using namespace std;

class MessageHandler {
public:
	explicit MessageHandler(Connection &conn);
	
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
