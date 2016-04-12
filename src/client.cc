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

	//cout << "Connection works if you can see this :)" << endl;
	cout << "Connected to server." << endl;
	messagehandler mh;
	clientmessagehandler cmh(mh);
	
	string command;
	while (cin >> command) {
		try {
			switch (command) {
			case "help" :
			  cout << "Ut med helpen" << endl;
			  break;
			case "listng" :           //temporära namn. finns troligen bättre...
			  vector<string> names = cmh.listGroups();
			  for (string s& : names)
			    cout << s << endl;
			  break;
			case "createng" :
			  cout << "Choose newsgroup name: " << endl;
			  string title;
			  cin >> title;
			  cmh.createGroup(title);
			  break;
			}
		case "deleteng" :
		  cout << "Newsgroup id number: " << endl;
		  int group_id << cin; //kolla om int..?
		  cmh.deleteGroup(group_id);
		  break;
		case : "readart" :
		  string artInfo = cmh.getArticle(gruppID, artID);
		  cout << "Title:  " << artInfo[0] << ". Author:  " << artInfo[1] << endl;
		  cout << artInfo[2] << endl;
		  break;
		  } catch (ConnectionClosedException&) {
			cerr << "Server closed down!" << endl;
			exit(1);
		}
	}
}