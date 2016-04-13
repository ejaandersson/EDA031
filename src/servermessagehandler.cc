#include <string>
#include <vector>
#include <utility>
#include "servermessagehandler.h"
#include "protocol.h"
#include "inmemoryserver.h"

using namespace std;


ServerMessageHandler::ServerMessageHandler(MessageHandler& msgHandler, shared_ptr<ServerInterface>& s) : msgH(msgHandler), server(s) {}

void ServerMessageHandler::newMessage() {
	uint command = msgH.getCode();
	switch (command) {
		case Protocol::COM_LIST_NG:
			listGroups();
			msgH.sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_CREATE_NG:
			createGroup();
			msgH.sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_DELETE_NG:
			deleteGroup();
			msgH.sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_LIST_ART:
			listArticles();
			msgH.sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_CREATE_ART:
			createArticle();
			msgH.sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_DELETE_ART:
			deleteArticle();
			msgH.sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_GET_ART:
			getArticle();
			msgH.sendCode(Protocol::ANS_END);
			break;
		default:
			throw IllegalCommandException("", "");
	}
}

void ServerMessageHandler::listGroups() {
	checkEnd();
	msgH.sendCode(Protocol::ANS_LIST_NG);
	vector<pair<id, string>> newsGroups = server->list_ng();
	msgH.sendIntParam(newsGroups.size());

	for (auto it = newsGroups.begin(); it != newsGroups.end(); ++it) {
		msgH.sendIntParam(it->first);
		msgH.sendStrParam(it->second);
	}
}

void ServerMessageHandler::createGroup() {
	string title = msgH.getStrParam();
	checkEnd();
	msgH.sendCode(Protocol::ANS_CREATE_NG);
	id res = server->create_ng(title);
	if (id != 0){
		msgH.sendCode(Protocol::ANS_ACK);
	} else {
	  msgH.sendCode(Protocol::ANS_NAK);
	  msgH.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
	}
}

void ServerMessageHandler::deleteGroup() {
	int ngInt = msgH.getIntParam();
	checkEnd();
	msgH.sendCode(Protocol::ANS_DELETE_NG);
  if (server->delete_ng(ngInt)){
    msgH.sendCode(Protocol::ANS_ACK);
  } else {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::listArticles() {
	int ngInt = msgH.getIntParam();
	checkEnd();
	msgH.sendCode(Protocol::ANS_LIST_ART);
	try {
		vector<Article> articles = server.listArt(ngInt);
		msgH.sendCode(Protocol::ANS_ACK);
		msgH.sendIntParam(articles.size());
		for(auto it = articles.begin(); it != articles.end(); ++it) {
			msgH.sendIntParam(it->id);
			msgH.sendStrParam(it->title);
		}
	} catch (NewsGroupNonexistantException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::createArticle() {
	int ngInt = msgH.getIntParam();
	string title = msgH.getStrParam();
	string author = msgH.getStrParam();
	string text = msgH.getStrParam();
	checkEnd();
	msgH.sendCode(Protocol::ANS_CREATE_ART);
	Article article(title, author, text);
	try {
		server.add_art(ngInt, article);
		msgH.sendCode(Protocol::ANS_ACK);
	} catch (NewsGroupDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::deleteArticle() {
	int ngInt = msgH.getIntParam();
	int article = msgH.getIntParam();
	checkEnd();
	msgH.sendCode(Protocol::ANS_DELETE_ART);
	try {
		server.delete_art(ngInt, article);
		msgH.sendCode(Protocol::ANS_ACK);
	} catch (NewsGroupNonexistanException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	} catch (ArticleNonexistantException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::getArticle() {
	int ngInt = msgH.getIntParam();
	int article = msgH.getIntParam();
	checkEnd();
	msgH.sendCode(Protocol::ANS_GET_ART);
	try { //fel typar
		Article article = server.read_art(ngInt, article);
		msgH.sendCode(Protocol::ANS_ACK);
		msgH.sendStrParam(article.title);
		msgH.sendStrParam(article.author);
		msgH.sendStrParam(article.text);
	} catch (NewsGroupNonexistanException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	} catch (ArticleDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::checkEnd() {
	if (msgH.getCode() != Protocol::COM_END) {
		throw IllegalCommandException("", "");
	}
}
