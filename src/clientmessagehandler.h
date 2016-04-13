#ifndef CLIENTMESSAGEHANDLER_H
#define CLIENTMESSAGEHANDLER_H

#include <string>
#include <vector>
#include "protocol.h"
#include "clientmessagehandler.h"
#include "connectionclosedexception.h"
#include "illegalcommandexception.h"

class ClientMessageHandler {
public:
    ClientMessageHandler();
    ClientMessageHandler(MessageHandler& mh);
		std::vector<std::string> listGroups() throw(ConnectionClosedException, IllegalCommandException);
		int createGroup(std::string title) throw(ConnectionClosedException, IllegalCommandException);
		int deleteGroup(int groupId) throw (ConnectionClosedException, IllegalCommandException);
		std::vector<std::string> listArticles(int groupId) throw (ConnectionClosedException, NewsGroupNonexistantException, ArticleNonexistantException, IllegalCommandException);
		int createArticle(int groupId, std::string title, std::string author, std::string text) throw(ConnectionClosedException, IllegalCommandException);
		int deleteArticle(int groupId, int articleId) throw(ConnectionClosedException, IllegalCommandException);
		std::vector<std::string> getArticle(int groupId, int articleId) throw(ConnectionClosedException, NewsGroupNonexistantException, ArticleNonexistantException, IllegalCommandException);
		void checkCode (std::string method, int expectedCode, int code) throw(IllegalCommandException);
		void checkCondition(bool condition, std::string method, std::string message) throw(IllegalCommandException);
private:
  MessageHandler messageHandler;
};
#endif
