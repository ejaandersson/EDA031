#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>
#include <memory>
#include "protocol.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "illegalcommandexception.h"


class MessageHandler {
public:
	explicit MessageHandler(std::shared_ptr<Connection>);
  
	
	//void newConnection(const Connection& conn);
	
	void sendCode(int code) throw(ConnectionClosedException);
	void sendByte(int code) throw(ConnectionClosedException);
	
	void sendInt(int value) throw(ConnectionClosedException);
	void sendIntParam(int i) throw(ConnectionClosedException);
	void sendStrParam(const std::string& str) throw(ConnectionClosedException);
	
	int getCode() throw(ConnectionClosedException);
	int getByte();
	
	int getInt() throw(ConnectionClosedException);
	int getIntParam() throw(ConnectionClosedException, IllegalCommandException);
	std::string getStrParam() throw(ConnectionClosedException, IllegalCommandException);
	
	private:
	std::shared_ptr<Connection> conn;
};


#endif
