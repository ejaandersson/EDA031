#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <string>

#include "connection.h"

using namespace std;

struct IllegalCommandException {};

class MessageHandler {
public:
<<<<<<< HEAD
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
=======
	explicit MessageHandler(Connection &conn);

	unsigned char readByte() throw (ConnectionClosedException);
	string readStr() throw (IllegalCommandException, ConnectionClosedException);
	size_t readNbr() throw (IllegalCommandException, ConnectionClosedException);
	unsigned int readUInt() throw (ConnectionClosedException);
	
	void printByte(const unsigned char &b) throw (ConnectionClosedException);
	void printStr(const string &s) throw (ConnectionClosedException);
	void printNbr(const int &num) throw (ConnectionClosedException);
	void printInt(const int &i) throw (ConnectionClosedException);
>>>>>>> master
	
	private:
	Connection &con;
};


#endif
