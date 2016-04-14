#include "inmemoryserver.h"
#include "diskserver.h"
#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "messagehandler.h"
#include "servermessagehandler.h"
#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
  if (argc != 2) {
    cerr << "Usage: myserver port-number" << endl;
    exit(1);
  }
  
  int port = -1;
  try {
    port = stoi(argv[1]);
  } catch (exception& e) {
    cerr << "Wrong port number. " << e.what() << endl;
    exit(1);
  }
  
  string servertype;
  cout << "Choose server type: " << endl;
  cout << "1. InMemoryServer" << endl;
  cout << "2. DiskServer" << endl;
  cin >> servertype;
  
  ServerInterface* s;
  if (servertype.compare("1") == 0) {
    s = new InMemoryServer(port);
  } else if (servertype.compare("2") == 0) {
    s = new DiskServer(port, "savexml.xml");
  } else {
    cerr << "Invalid server choise." << endl;
  }
  
  shared_ptr<ServerInterface> serverptr(s);
  
  if (!serverptr->isReady()) {
    cerr << "Server initialization error." << endl;
    exit(1);
  } else {
    cout << "Server is ready." << endl;
  }
  
  while (true) {
    auto conn = serverptr->waitForActivity();
    if (conn != nullptr) {
      try {
        shared_ptr<MessageHandler> msgptr = make_shared<MessageHandler>(MessageHandler(shared_ptr<Connection>(conn)));
        ServerMessageHandler smh(msgptr, serverptr);
        smh.newMessage();
      } catch (ConnectionClosedException&) {
        serverptr->deregisterConnection(conn);
        cout << "Client closed connection" << endl;
      }
    } else {
      conn = make_shared<Connection>();
      serverptr->registerConnection(conn);
      cout << "New client connects" << endl;
    }
  }
}
