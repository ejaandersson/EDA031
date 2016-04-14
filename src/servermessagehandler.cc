#include <string>
#include <vector>
#include <utility>
#include "servermessagehandler.h"
#include "protocol.h"
#include "inmemoryserver.h"
//#include "diskserver.h"

#include <iostream>

using namespace std;


ServerMessageHandler::ServerMessageHandler(shared_ptr<MessageHandler> msgHandler, shared_ptr<ServerInterface> s) : msgH(msgHandler), server(s) {}

int ServerMessageHandler::newMessage(void) throw(IllegalCommandException){
	uint command = msgH->getCode();
	switch (command) {
		case Protocol::COM_LIST_NG:
			listGroups();
			msgH->sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_CREATE_NG:
			createGroup();
			msgH->sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_DELETE_NG:
			deleteGroup();
			msgH->sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_LIST_ART:
			listArticles();
			msgH->sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_CREATE_ART:
			createArticle();
			msgH->sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_DELETE_ART:
			deleteArticle();
			msgH->sendCode(Protocol::ANS_END);
			break;
		case Protocol::COM_GET_ART:
			getArticle();
			msgH->sendCode(Protocol::ANS_END);
			break;
		default:
			throw IllegalCommandException("", "");
	}
	return 0;
}

void ServerMessageHandler::listGroups(void) {
	checkEnd();
	msgH->sendCode(Protocol::ANS_LIST_NG);
	vector<pair<id, string>> newsGroups = server->list_ng();
	msgH->sendIntParam(newsGroups.size());

	for (auto it = newsGroups.begin(); it != newsGroups.end(); ++it) {
		msgH->sendIntParam(it->first);
		msgH->sendStrParam(it->second);
	}
}

void ServerMessageHandler::createGroup(void) {
	string title = msgH->getStrParam();
	checkEnd();
	msgH->sendCode(Protocol::ANS_CREATE_NG);
	id res = server->create_ng(title);
	if (res != 0){
		msgH->sendCode(Protocol::ANS_ACK);
	} else {
	  msgH->sendCode(Protocol::ANS_NAK);
	  msgH->sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
	}
}

void ServerMessageHandler::deleteGroup(void) {
	int ngInt = msgH->getIntParam();
	checkEnd();
	msgH->sendCode(Protocol::ANS_DELETE_NG);
  if (server->delete_ng(ngInt)){
    msgH->sendCode(Protocol::ANS_ACK);
  } else {
		msgH->sendCode(Protocol::ANS_NAK);
		msgH->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::listArticles(void) {
	int ngInt = msgH->getIntParam();
	checkEnd();
	msgH->sendCode(Protocol::ANS_LIST_ART);
	std::vector<std::pair<id, string>> articles = server->listArt(ngInt);
	if (!server->exists_ng(ngInt)) {
	  msgH->sendCode(Protocol::ANS_NAK);
	  msgH->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	} else {
		msgH->sendCode(Protocol::ANS_ACK);
		msgH->sendIntParam(articles.size());
		for(auto it = articles.begin(); it != articles.end(); ++it) {
			msgH->sendIntParam(it->first);
			msgH->sendStrParam(it->second);
		}
	}
	//} else {
	  //msgH->sendCode(Protocol::ANS_NAK);
	  //msgH->sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
}

void ServerMessageHandler::createArticle(void) {
	int ngInt = msgH->getIntParam();
	string title = msgH->getStrParam();
	string author = msgH->getStrParam();
	string text = msgH->getStrParam(); //kan va skumt
	checkEnd();
	msgH->sendCode(Protocol::ANS_CREATE_ART);
	if (server->exists_ng(ngInt)) {
		server->add_art(ngInt, shared_ptr<Article>(new Article(title, author, text)));
		msgH->sendCode(Protocol::ANS_ACK);
	} else {
		msgH->sendCode(Protocol::ANS_NAK);
		msgH->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::deleteArticle(void) {
	int ngInt = msgH->getIntParam();
	int article = msgH->getIntParam();
	checkEnd();
	msgH->sendCode(Protocol::ANS_DELETE_ART);
	if (server->exists_ng(ngInt)) {
	  if (server->delete_art(ngInt, article)) {
	    msgH->sendCode(Protocol::ANS_ACK);
	  } else {
	    msgH->sendCode(Protocol::ANS_NAK);
	    msgH->sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
	  }
	} else {
	  msgH->sendCode(Protocol::ANS_NAK);
	  msgH->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::getArticle(void) {
	int ngInt = msgH->getIntParam();
	int articleId = msgH->getIntParam();
	checkEnd();
	msgH->sendCode(Protocol::ANS_GET_ART);
	if (server->exists_ng(ngInt)) {
	  shared_ptr<const Article> article = server->read_art(ngInt, articleId);
	  if (article != nullptr) {
	    msgH->sendCode(Protocol::ANS_ACK);
	    msgH->sendStrParam(article->getTitle());
	    msgH->sendStrParam(article->getAuthor());
	    msgH->sendStrParam(article->getText());
	  } else {
	    msgH->sendCode(Protocol::ANS_NAK);
	    msgH->sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
	  }
	} else {
	  msgH->sendCode(Protocol::ANS_NAK);
	  msgH->sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerMessageHandler::checkEnd(void) {
	if (msgH->getCode() != Protocol::COM_END) {
		throw IllegalCommandException("", "");
	}
}
