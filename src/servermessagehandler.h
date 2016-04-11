#ifndef SERVERMESSAGEHANDLER_H
#define SERVERMESSAGEHANDLER_H

#include <string>

class ServerMessageHandler {
public:
		
		void newMessage();
		void listGroups();
		void createGroup();
		void deleteGroup();
		void listArticles();
		void createArticle();
		void deleteArticle();
		void getArticle();
		void checkEnd();
};

#endif
