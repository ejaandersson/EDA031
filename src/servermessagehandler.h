#ifndef SERVERMESSAGEHANDLER_H
#define SERVERMESSAGEHANDLER_H

#include <memory>
#include "illegalcommandexception.h"
#include "messagehandler.h"
#include "serverinterface.h"


class ServerMessageHandler {
public:
		ServerMessageHandler(std::shared_ptr<MessageHandler>, std::shared_ptr<ServerInterface>);
		int newMessage(void) throw(IllegalCommandException);
		void listGroups(void);
		void createGroup(void);
		void deleteGroup(void);
		void listArticles(void);
		void createArticle(void);
		void deleteArticle(void);
		void getArticle(void);
		void checkEnd(void);
private:
  std::shared_ptr<MessageHandler> msgH;
  std::shared_ptr<ServerInterface> server;
};

#endif
