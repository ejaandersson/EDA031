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
  InMemoryServer server(port);
  
  if (!server.isReady()) {
    cerr << "Server initialization error." << endl;
    exit(1);
  }
  
  while (true) {
    auto conn = server.waitForActivity();
    if (conn != nullptr) {
      try {
        MessageHandler mh(*conn);
        ServerMessageHandler smh(shared_ptr<MessageHandler>(mh), shared_ptr<ServerInterface>(server));
        smh.newMessage();
      } catch (ConnectionClosedException&) {
        server.deregisterConnection(conn);
        cout << "Client closed connection" << endl;
      }
    } else {
      conn = make_shared<Connection>();
      server.registerConnection(conn);
      cout << "New client connects" << endl;
    }
  }
}
