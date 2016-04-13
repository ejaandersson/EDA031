#ifndef SERVERMESSAGEHANDLER_H
#define SERVERMESSAGEHANDLER_H

#include <memory>
#include "illegalcommandexception.h"
#include "messagehandler.h"
#include "serverinterface.h"


class ServerMessageHandler {
public:
		ServerMessageHandler(MessageHandler&, std::shared_ptr<ServerInterface>&);
		void newMessage();
		void listGroups();
		void createGroup();
		void deleteGroup();
		void listArticles();
		void createArticle();
		void deleteArticle();
		void getArticle();
		void checkEnd();
private:
  MessageHandler msgH;
  std::shared_ptr<ServerInterface> server;
};

#endif
