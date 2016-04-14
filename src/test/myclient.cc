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
  } else if(cmd.compare("createart") == 0) {
    return Protocol::COM_CREATE_ART;
  } else if (cmd.compare("deleteart") == 0) {
    return Protocol::COM_DELETE_ART;
  }
  return -1;  //Om det blir fel. Kanske throwa något?
}



int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "Required parameters: hostname portnumber" << endl;
    exit(1);
  }
  int port = -1;
  try {
    port = stoi(argv[2]);
  } catch (exception& e) {
    cerr << "Port must be an integer." << endl;
    exit(1);
  }
  if (port < 1025) {
    cerr << "Port must be > 1025" << endl;
    exit(1);
  }
  
  
  Connection* ptr = new Connection(argv[1], stoi(argv[2]));
  shared_ptr<Connection> con = shared_ptr<Connection>(ptr);
  if (!con->isConnected()) {
    cerr << "Connection failed!" << endl;
    exit(1);
  }
  cout << "Connected to server." << endl;
  cout << "For a list of commands, input 'help'." << endl;
  //cout << "Connection works if you can see this :)" << endl;
  
  shared_ptr<MessageHandler> msgptr = make_shared<MessageHandler>(MessageHandler(con));
  ClientMessageHandler cmh(msgptr);
  
  string command;
  while (cin >> command) {
    int c = commandToInt(command);
    
    try {
      switch (c) {
      case -1 : {
        cout << "Invalid command. Use 'help' to see commands." << endl;
      break;
    }
      case 0 : {//HELP
      cout << "Valid commands:" << endl;
      cout << "listng - Lists all newsgroups with id numbers." << endl;
      cout << "createng - Creates a new newsgroup." << endl;
      cout << "deleteng - Deletes a newsgroup." << endl;
      cout << "listart - Lists all articles in a newsgroup." << endl;
      cout << "readart - Reads an article in a newsgroup." << endl;
      cout << "createart - Creates a new article in a newsgroup." << endl;
      cout << "deleteart - Delets an article in a newsgroup." << endl;
      break;
    }
      case Protocol::COM_LIST_NG : {           //temporära namn. finns troligen bättre...
        vector<string> names = cmh.listGroups();
        if (names.empty()) {
          cout << "There are no newsgroups." << endl;
        } else {
          cout << "The current newsgroups are: " << endl;
          for (string &s : names) {
            cout << s << endl;
          }
        }
        break;
      }
      case Protocol::COM_CREATE_NG : {
        cout << "Choose newsgroup name: ";
        string title;
        cin >> title;
        cmh.createGroup(title);
        cout << "Newsgroup created." << endl;
        break;
      }
      case Protocol::COM_DELETE_NG : {
        string group_id;
        cout << "Newsgroup id number: ";
        cin >> group_id;
        int gId = -1;
        try {
          gId = stoi(group_id);
        } catch (exception& e) {
          cout << "Group id must be a number." << endl;
          break;
        }
        //int stoi(group_id) << cin; //kolla om int..? Ifall de kör listng här....
        if (cmh.deleteGroup(gId) == 0) {
          cout << "Newsgroup deleted." << endl;
        } else {
          cout << "Invalid newsgroup id." << endl;
        }
        
        break;
      }
      case Protocol::COM_LIST_ART : {
        string group_id;
        cout << "Newsgroup id number: ";
        cin >> group_id;
        int gId = -1;
        try {
          gId = stoi(group_id);
        } catch (exception& e) {
          cout << "Group id must be a number." << endl;
          break;
        }
        vector<string> arts = cmh.listArticles(gId); //Vad är det som retuneras här..?
        for (string &s : arts)
          cout << s << endl;
        break;
      }
      case Protocol::COM_GET_ART :{
        string group_id, art_id;
        cout << "Newsgroup id number: ";
        cin >> group_id;
        int gId = -1;
        try {
          gId = stoi(group_id);
        } catch (exception& e) {
          cout << "Group id must be a number." << endl;
          break;
        }
        cout << "Article id number: ";
        cin >> art_id;
        cout << endl;
        int aId = -1;
        try {
          aId = stoi(art_id);
        } catch (exception& e) {
          cout << "Article id must be a number." << endl;
          break;
        }
        vector<string> artInfo = cmh.getArticle(gId, aId);
        if (artInfo.empty()) {
          cout << "Newsgroup is empty." << endl;
          break;
        }
        cout  << artInfo[0] << " " << artInfo[1] << endl;
        cout << artInfo[2] << endl;
        break;
      }
      case Protocol::COM_CREATE_ART : {
        string group_id, title, author, text;
        cout << "Choose existing newsgroup id number: ";
        cin >> group_id;
        cout << endl;
        cout << "Choose a title: ";
        cin >> title;
        cout << "Choose author name: ";
        cin >> author;
        cout << "Write article: ";
        cin >> ws;
        getline(cin, text);
        cmh.createArticle(stoi(group_id), title, author, text);
        cout << "Article created." << endl;
        break;
      }
      case (Protocol::COM_DELETE_ART) : 
        string group_id, art_id;
        cout << "Newsgroup id number: "; //här vill man kunna lista grupper
        cin >> group_id;
        cout << endl;
        cout << "Article id number: "; //och artiklar
        cin >> art_id;
        cout << endl;
        cmh.deleteArticle(stoi(group_id), stoi(art_id));
        cout << "Article removed." << endl;
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
