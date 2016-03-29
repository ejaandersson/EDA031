#include "messagehandler.h"

#include "protocol.h"
#include "connection.h"

using namespace std;


MessageHandler::MessageHandler(Connection &conn) : con(conn) {}

/* 
 Read and returns byte from server through connection.
 Throws ConnectionClosedException if not connected to server.
 */

unsigned char MessageHandler::readByte() throw (ConnectionClosedException) {
	return con.read();
}

/* 
Read and returns string from server through connection.
Throws IllegalCommandException if the command doesn't match the Message Protocol
Throws ConnectionClosedException if not connected to the server.
 */

string MessageHandler::readStr() throw (IllegalCommandException, ConnectionClosedException) {
	if (con.read() != Protocol::PAR_STRING)
		throw IllegalCommandException();
	size_t size = readUInt();
	string str;
	while(size > 0){
		str += con.read();
		--size;
	}
	return str;
}

/* 
Read and returns number from server through connection.
Throws IllegalCommandException if the command doesn't match the Message Protocol.
Throws ConnectionClosedException if not connected to the server.
 */

size_t MessageHandler::readNbr() throw (IllegalCommandException, ConnectionClosedException) {
	if (con.read() != Protocol::PAR_NUM)
		throw IllegalCommandException();
	unsigned int num = readUInt();
	return num;
}


/* 
Reads and return unsigned integer from server through connection.
Throws ConnectionClosedException if not connected to the server.
 */
unsigned int MessageHandler::readUInt() throw (ConnectionClosedException) {
	unsigned int res;
	for (unsigned char i = 0; i < 4; ++i){
		unsigned char tmp = con.read();
		res <<= 8;
		res += tmp;
	}
	return res;
}


/* 
Prints paramenter &byte to console.
Throws ConnectionClosedException if not connected to the server.
 */
void MessageHandler::printByte(const unsigned char &byte) throw(ConnectionClosedException) {
	con.write(byte);
}


/* 
Prints paramenter &nbr to console.
Throws ConnectionClosedException if not connected to the server.
 */

void MessageHandler::printNbr(const int &nbr) throw(ConnectionClosedException) {
	con.write(Protocol::PAR_NUM);
	printInt(nbr);
}

/* 
Prints paramenter &i to console.
Throws ConnectionClosedException if not connected to the server.
 */
void MessageHandler::printInt(const int &i) throw(ConnectionClosedException) {
	con.write((i >> 24) & 0xFF);
	con.write((i >> 16) & 0xFF);
	con.write((i >> 8) & 0xFF);
	con.write(i & 0xFF);
}

/*  
Prints paramenter &str to console.
Throws ConnectionClosedException if not connected to the server.
 */
void MessageHandler::printStr(const string &str) throw(ConnectionClosedException) {
	con.write(Protocol::PAR_STRING);
	print_int(str.size());
	for (size_t i = 0; i < str.size(); ++i) {
		con.write(str[i]);
	}
}
