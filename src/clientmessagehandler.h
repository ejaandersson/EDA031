#ifndef CLIENTMESSAGEHANDLER_H
#define CLIENTMESSAGEHANDLER_H

#include <string>
#include <vector>
#include <memory>
#include "messagehandler.h"
#include "protocol.h"
#include "connectionclosedexception.h"
#include "illegalcommandexception.h"

class ClientMessageHandler {
public:
    //ClientMessageHandler();
    ClientMessageHandler(std::shared_ptr<MessageHandler>);
		std::vector<std::string> listGroups() throw(ConnectionClosedException, IllegalCommandException);
		int createGroup(std::string title) throw(ConnectionClosedException, IllegalCommandException);
		int deleteGroup(int groupId) throw (ConnectionClosedException, IllegalCommandException);
		std::vector<std::string> listArticles(int groupId) throw (ConnectionClosedException, IllegalCommandException);
		int createArticle(int groupId, std::string title, std::string author, std::string text) throw(ConnectionClosedException, IllegalCommandException);
		int deleteArticle(int groupId, int articleId) throw(ConnectionClosedException, IllegalCommandException);
		std::vector<std::string> getArticle(int groupId, int articleId) throw(ConnectionClosedException, IllegalCommandException);
		void checkCode(std::string method, int expectedCode, int code) throw(IllegalCommandException);
		void checkCondition(bool condition, std::string method, std::string message) throw(IllegalCommandException);
private:
    std::shared_ptr<MessageHandler> messageHandler;
};
#endif
