#ifndef CLIENTMESSAGEHANDLER_H
#define CLIENTMESSAGEHANDLER_H

#include <string>


class ClientMessageHandler {
public:
		vector<string> listGroups() throw(ConnectionClosedException, IllegalCommandException);
		int createGroup(string title) throw(ConnectionClosedException, IllegalCommandException)
		int deleteGroup(int groupId)  throw (ConnectionClosedException, IllegalCommandException);
		vector<string> listArticles(int groupId) throw (ConnectionClosedException, NewsGroupNonexistantException, ArticleNonexistantException, IllegalCommandException);
		int createArticle(int groupId, string title, string author, string text) throw(ConnectionClosedException, IllegalCommandException);
		int deleteArticle(int groupId, int articleId) throw(ConnectionClosedException, IllegalCommandException);
		vector<string> getArticle(int groupId, int articleId) throw(ConnectionClosedException, NewsGroupNonexistantException, ArticleNonexistantException, IllegalCommandException);
		void checkCode (string method, int expectedCode, int code) throw(IllegalCommandException);
		void checkCondition(bool condition, string method, string message) throw(IllegalCommandException);
		
};
#endif
