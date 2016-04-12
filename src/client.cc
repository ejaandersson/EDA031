#include "connection.h"
#include "exceptions/connectionclosedexception.h"
#include "messagehandler.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Required parameters: hostname portnumber" << endl;
		exit(1);
	}
	//host number, portnumber
	//Connection con(argv[0], argv[1]);
	Connection con("localhost", 5555);
	if (!con.isConnected()) {
		cerr << "Connection failed!" << endl;
		exit(1);
	}

	cout << "Connection works if you can see this :)" << endl;

	string command;

	while (cin >> command) {
		try {
			if (command == "hej") {
				cout << command << endl;
			}
		} catch (ConnectionClosedException&) {
			cerr << "Server closed down!" << endl;
			exit(1);
		}
	}
}