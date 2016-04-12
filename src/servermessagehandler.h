#ifndef SERVERMESSAGEHANDLER_H
#define SERVERMESSAGEHANDLER_H


class ServerMessageHandler {
public:
		ServerMessageHandler(MessageHandler&, Server&);
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
  Server server;
};

#endif
