#include "inmemoryserver.h"
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
  //Ska vara 3 argument dar tredje anger vilken typ av server.
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
  
  //If-sats som bestammer vilken typ av server.
  InMemoryServer* s = new InMemoryServer(port);
  shared_ptr<ServerInterface> serverptr(s);
  
  if (!serverptr->isReady()) {
    cerr << "Server initialization error." << endl;
    exit(1);
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
