#include "connection.h"
#include "protocol.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"
#include "clientmessagehandler.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib> 

using namespace std;


int commandToInt(string &cmd) {
  if (cmd.compare("help") == 0) {
    return 0;
  } else if (cmd.compare("listng") == 0){
    return Protocol::COM_LIST_NG;
  } else if (cmd.compare("createng") == 0) {
    return Protocol::COM_CREATE_NG;
  } else if (cmd.compare("deleteng") == 0) {
    return Protocol::COM_DELETE_NG;
  } else if (cmd.compare("listart") == 0) {
    return Protocol::COM_LIST_ART;
  } else if (cmd.compare("readart") == 0) {
    return Protocol::COM_GET_ART;
  } else if(cmd.compare("writeart") == 0) {
    return Protocol::COM_CREATE_ART;
  } else if (cmd.compare("deleteart") == 0) {
    return Protocol::COM_DELETE_ART;
  }
  return -1;  //Om det blir fel. Kanske throwa något?
}



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
  cout << "Connected to server." << endl;
  cout << "For a list of commands, input 'help'." << endl;
  //cout << "Connection works if you can see this :)" << endl;
  
  MessageHandler mh(con);
  ClientMessageHandler cmh(mh);
  
  string command;
  while (cin >> command) {
    int c = commandToInt(command);
    
    try {
      switch (c) {
      case 0 : {//HELP
      cout << "Ut med helpen" << endl;
      break;
    }
      case Protocol::COM_LIST_NG : {           //temporära namn. finns troligen bättre...
        vector<string> names = cmh.listGroups();
        cout << "The current newsgroups are: " << endl;
        for (string &s : names)
          cout << s << endl;
        break;
      }
      case Protocol::COM_CREATE_NG : {
        cout << "Choose newsgroup name: " << endl;
        string title;
        cin >> title;
        cmh.createGroup(title);
        break;
      }
      case Protocol::COM_DELETE_NG : {
        string group_id;
        cout << "Newsgroup id number: " << endl;
        cin >> group_id;
        //int stoi(group_id) << cin; //kolla om int..? Ifall de kör listng här....
        cmh.deleteGroup(stoi(group_id));
        break;
      }
      case Protocol::COM_LIST_ART : {
        string group_id;
        cout << "Newsgroup id number: ";
        cin >> group_id;
        cout << endl;
        vector<string> arts = cmh.listArticles(stoi(group_id)); //Vad är det som retuneras här..?
        for (string &s : arts)
          cout << s << endl;
        break;
      }
      case Protocol::COM_GET_ART :{
        string group_id, art_id;
        cout << "Newsgroup id number: ";
        cin >> group_id;
        cout << endl;
        cout << "Article id number: ";
        cin >> art_id;
        cout << endl;
        vector<string> artInfo = cmh.getArticle(stoi(group_id), stoi(art_id));
        cout << "Title:  " << artInfo[0] << ". Author:  " << artInfo[1] << endl;
        cout << artInfo[2] << endl;
        break;
      }
      case Protocol::COM_CREATE_ART : {
        string group_id;
        string title, author, text;
        cout << "Choose existing newsgroup id number: ";
        cin >> group_id;
        cout << endl;
        cout << "Choose a title: ";
        cin >> title;
        cout << endl;
        cout << "Choose author name: ";
        cin >> author;
        cout << endl;
        cout << "Write article: " << endl;
        cin >> text;
        cmh.createArticle(stoi(group_id), title, author, text);
        break;
      }
      case (Protocol::COM_DELETE_ART) : 
        string group_id, art_id;
        cout << "Newsgroup id number: "; //här vill man kunna lista grupper
        cin >> group_id;
        cout << endl;
        cout << "Newsgroup id number: "; //och artiklar
        cin >> art_id;
        cout << endl;
        cmh.deleteArticle(stoi(group_id), stoi(art_id));
        break;
        
      }
    }
    catch (...) {
      //cerr << "Server closed down!" << endl;
      cerr << "Something happened!" << endl;
      exit(1);
    }
  }
}
