#include "clientmessagehandler.h"
#include <algorithm>
#include <iostream>
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
  return -1;
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
    cerr << "Port must be > 1024" << endl;
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
      case 0 : {
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
      case Protocol::COM_LIST_NG : {
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
        string title;
        cout << "Choose newsgroup name: ";
        cin >> ws;
        getline(cin, title);
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
        vector<string> arts = cmh.listArticles(gId);
        if (arts.empty()) {
          cout << "There are no articles in this newsgroup." << endl;
        } else {
          for (string &s : arts) {
            cout << s << endl;
          }
        }
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
          cout << "Article does not exist." << endl;
          break;
        }
        cout  << artInfo[0] << " " << artInfo[1] << endl;
        cout << artInfo[2] << endl;
        break;
      }
      case Protocol::COM_CREATE_ART : {
        string group_id, title, author, text;
        cout << "Choose newsgroup id number: ";
        cin >> group_id;
        int gId = -1;
        try {
          gId = stoi(group_id);
        } catch (exception& e) {
          cout << "Group id must be a number." << endl;
          break;
        }
        cout << "Choose a title: ";
        cin >> ws;
        getline(cin, title);
        cout << "Choose author name: ";
        cin >> ws;
        getline(cin, author);
        cout << "Write article: ";
        cin >> ws;
        getline(cin, text);
        if (cmh.createArticle(gId, title, author, text) == 0) {
          cout << "Article created." << endl;
        } else {
          cout << "That newsgroup does not exist." << endl;
        }
        
        break;
      }
      case (Protocol::COM_DELETE_ART) :  {
        string group_id, art_id;
        cout << "Newsgroup id number: ";
        cin >> group_id;
        int gId = -1;
        try {
          gId = stoi(group_id);
        } catch (exception& e) {
          cout << "Newsgroup id must be a number." << endl;
          break;
        }
        cout << "Article id number: ";
        cin >> art_id;
        int aId = -1;
        try {
          aId = stoi(art_id);
        } catch (exception& e) {
          cout << "Article id must be a number." << endl;
          break;
        }
        cout << endl;
        if (cmh.deleteArticle(gId, aId) == 0) {
          cout << "Article removed." << endl;
        } else {
          cout << "That article does not exist." << endl;
        }
        break;
      }
      }
      }
      catch (...) {
        cerr << "Something went wrong!" << endl;
        exit(1);
      }
    }
  }
  