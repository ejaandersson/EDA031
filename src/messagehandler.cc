#include <iostream>
#include <string>
#include "messagehandler.h"


using namespace std;


/**
 Create a message handler through a connection.
 @param conn is the connection message handler handles messages through (Bättre kommentar går inte hitta)
*/

MessageHandler::MessageHandler(shared_ptr<Connection> conn) : conn(conn) {}

/**
Change connection.
@param conn is the new Connection object

*/

/**
Sends a code corresponding to a constant from the Protocol class.
@param code is the code to send.
@throws ConnectionClosedException if the server is dead.
*/
void MessageHandler::sendCode(int code) throw(ConnectionClosedException) {
	sendByte(code);
}

/**
Sends an int parameter following the Protocol
@param value is the int to be sent
@throws ConnectionClosedException if connection was lost.
*/

void MessageHandler::sendInt(int value) throw(ConnectionClosedException) {
	sendByte((value >> 24) & 0xFF);
	sendByte((value >> 16) & 0xFF);
	sendByte((value >> 8 ) & 0xFF);
	sendByte((value & 0xFF));
}


/**
Sends an int parameter following the Protocol
@param i is the integer to be sent
@throws ConnectionClosedException if connection was lost
*/
void MessageHandler::sendIntParam(int i) throw(ConnectionClosedException) {
	sendCode(Protocol::PAR_NUM);
	sendInt(i);
}


/**
Sends a string parameter following the Protocol
@param str is the string to be sent
@throws ConnectionClosedException if connection was lost.
*/

void MessageHandler::sendStrParam(const string& str) throw(ConnectionClosedException) {
	sendCode(Protocol::PAR_STRING);
	sendInt(str.length());
	for (unsigned int i = 0; i < str.length(); i++) {
		sendByte(str[i]);
	}
}


/**
Gets an int value
@return the int value
@throws ConnectionClosedException if connection was lost
*/

int MessageHandler::getInt() throw(ConnectionClosedException) {
	int byte1 = getByte();
	int byte2 = getByte();
	int byte3 = getByte();
	int byte4 = getByte();
	
	return byte1 << 24 | byte2 << 16 | byte3 << 8 | byte4;
}

/**
Gets an int parameter.
@return the parameter
@throws ConnectionClosedException if connection was lost
@throws IllegalCommandException
*/

int MessageHandler::getIntParam() throw(ConnectionClosedException, IllegalCommandException) {
	int code = getCode();
	if (code != Protocol::PAR_NUM) {
		throw IllegalCommandException("Get integer parameter", Protocol::PAR_NUM, code);
	}
	return getInt();
}


/**
Gets a string parameter.

@return the parameter
@throws ConnectionClosedException if the connection was lost
@throws IllegalCommandException
*/

string MessageHandler::getStrParam() throw(ConnectionClosedException, IllegalCommandException) {
	int code = getCode();
	if (code != Protocol::PAR_STRING) {
		throw IllegalCommandException("Get string parameter", Protocol::PAR_STRING, code);
	}
	int n = getInt();
	if (n < 1) {
		throw IllegalCommandException("Get string parameter", "Number of characters below 0");
	}
	string result = "";
	for (int i = 1; i <= n; i++) {
		char ch = conn->read();
		result += ch;
	}
	return result;
}

/**
Gets a code = command
@return the code
@throws ConnectionClosedException if connection was lost
*/

int MessageHandler::getCode() throw(ConnectionClosedException) {
	int code = getByte();
	return code;
}

/**

*/
int MessageHandler::getByte() {
	int code;
	try {
		code = conn->read();
	} catch (...) {
		throw ConnectionClosedException();
	}
	return code;
}

/**

*/
void MessageHandler::sendByte(int code) throw(ConnectionClosedException) {
	try {
		conn->write(static_cast<char>(code));
	} catch(...) {
		throw ConnectionClosedException();
	}
}

