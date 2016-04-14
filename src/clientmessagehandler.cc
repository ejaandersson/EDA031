#include "clientmessagehandler.h"


using namespace std;

ClientMessageHandler::ClientMessageHandler(std::shared_ptr<MessageHandler> mh): messageHandler(mh) {}

vector<string> ClientMessageHandler::listGroups() throw (ConnectionClosedException, IllegalCommandException){
  messageHandler->sendCode(Protocol::COM_LIST_NG);
  messageHandler->sendCode(Protocol::COM_END);
  
  int code = messageHandler->getCode();
  checkCode("List groups", Protocol::ANS_LIST_NG, code);
  
  int nbrGroups = messageHandler->getIntParam();
  checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
  vector<string> groupNames(nbrGroups);
  for(int i = 0; i < nbrGroups; ++i){
    groupNames[i] = to_string(messageHandler->getIntParam()) + ". ";
    groupNames[i] = groupNames[i] + messageHandler->getStrParam();
  }
  code = messageHandler->getCode();
  checkCode("List groups", Protocol::ANS_END, code);
  return groupNames;	
}

int ClientMessageHandler::createGroup(string title) throw (ConnectionClosedException, IllegalCommandException) {		
  messageHandler->sendCode(Protocol::COM_CREATE_NG);
  messageHandler->sendStrParam(title);
  messageHandler->sendCode(Protocol::COM_END);
  
  int errorCode = 0;
  int code = messageHandler->getCode();
  checkCode("Create group", Protocol::ANS_CREATE_NG, code);
  code = messageHandler->getCode();
  
  if (code != Protocol::ANS_ACK) {
    checkCondition(code == Protocol::ANS_NAK, "Create group",
                   "Did not receive ANS_ACK or ANS_NAK");
    errorCode = messageHandler->getCode();
  }
  
  code = messageHandler->getCode();
  checkCode("Create group", Protocol::ANS_END, code);
  return errorCode;
}

int ClientMessageHandler::deleteGroup(int groupId) throw (ConnectionClosedException, IllegalCommandException) {
  messageHandler->sendCode(Protocol::COM_DELETE_NG);
  messageHandler->sendIntParam(groupId);
  messageHandler->sendCode(Protocol::COM_END);
  
  int errorCode = 0;
  int code = messageHandler->getCode();
  checkCode("Delete group", Protocol::ANS_DELETE_NG, code);
  code = messageHandler->getCode();
  
  if (code != Protocol::ANS_ACK) {
    checkCondition(code == Protocol::ANS_NAK, "Create group",
                   "Did not receive ANS_ACK or ANS_NAK");
    errorCode = messageHandler->getCode();
  }
  code = messageHandler->getCode();
  checkCode("Delete group", Protocol::ANS_END, code);
  
  return errorCode;
}

vector<string> ClientMessageHandler::listArticles(int groupId) throw (ConnectionClosedException, IllegalCommandException){
  messageHandler->sendCode(Protocol::COM_LIST_ART);
  messageHandler->sendIntParam(groupId);
  messageHandler->sendCode(Protocol::COM_END);
  
  int code = messageHandler->getCode();
  checkCode("List articles", Protocol::ANS_LIST_ART, code);
  code = messageHandler->getCode();
  if (code != Protocol::ANS_ACK) {
    checkCondition(code == Protocol::ANS_NAK, "Create group",
                   "Did not receive ANS_ACK or ANS_NAK");
    code = messageHandler->getCode(); // error code
    messageHandler->getCode();
    return vector<string>();
  }
  int nbrArticles = messageHandler->getIntParam();
  checkCondition(nbrArticles >= 0, "List articles",
                 "Number of groups < 0");
  vector<string> articleNames(nbrArticles);
  for (int i = 0; i < nbrArticles; i++) {
    articleNames[i] = to_string(messageHandler->getIntParam()) + ". ";
    articleNames[i] = articleNames[i] + messageHandler->getStrParam();
    
  }
  code = messageHandler->getCode();
  checkCode("List articles", Protocol::ANS_END, code);
  
  return articleNames;
}

int ClientMessageHandler::createArticle(int groupId, string title, string author, string text) throw (ConnectionClosedException,
                                        IllegalCommandException){
  messageHandler->sendCode(Protocol::COM_CREATE_ART);
  messageHandler->sendIntParam(groupId);
  messageHandler->sendStrParam(title);
  messageHandler->sendStrParam(author);
  messageHandler->sendStrParam(text);
  messageHandler->sendCode(Protocol::COM_END);
  
  int errorCode = 0;
  int code = messageHandler->getCode();
  checkCode("Create article", Protocol::ANS_CREATE_ART, code);
  code = messageHandler->getCode();
  if (code != Protocol::ANS_ACK) {
    checkCondition(code == Protocol::ANS_NAK, "Create group",
                   "Did not receive ANS_ACK or ANS_NAK");
    errorCode = messageHandler->getCode();
  }
  code = messageHandler->getCode();
  checkCode("Create article", Protocol::ANS_END, code);
  
  return errorCode;
}

int ClientMessageHandler::deleteArticle(int groupId, int articleId) throw (ConnectionClosedException, IllegalCommandException){
  
  messageHandler->sendCode(Protocol::COM_DELETE_ART);
  messageHandler->sendIntParam(groupId);
  messageHandler->sendIntParam(articleId);
  messageHandler->sendCode(Protocol::COM_END);
  
  int errorCode = 0;
  
  int code = messageHandler->getCode();
  checkCode("Delete article", Protocol::ANS_DELETE_ART, code);
  code = messageHandler->getCode();
  if (code != Protocol::ANS_ACK) {
    checkCondition(code == Protocol::ANS_NAK, "Create group",
                   "Did not receive ANS_ACK or ANS_NAK");
    errorCode = messageHandler->getCode();
  }
  code = messageHandler->getCode();
  checkCode("Delete article", Protocol::ANS_END, code);
  
  return errorCode;
}

vector<string> ClientMessageHandler::getArticle(int groupId, int articleId) throw (ConnectionClosedException, IllegalCommandException){
  
  messageHandler->sendCode(Protocol::COM_GET_ART);
  messageHandler->sendIntParam(groupId);
  messageHandler->sendIntParam(articleId);
  messageHandler->sendCode(Protocol::COM_END);	
  
  vector<string> result;
  
  int code = messageHandler->getCode();
  checkCode("Get article", Protocol::ANS_GET_ART, code);
  code = messageHandler->getCode();
  if (code != Protocol::ANS_ACK) {
    checkCondition(code == Protocol::ANS_NAK, "Create group",
                   "Did not receive ANS_ACK or ANS_NAK");
    code = messageHandler->getCode();
    checkCode("Delete article", Protocol::ANS_END, messageHandler->getCode());
    if (code == Protocol::ERR_NG_DOES_NOT_EXIST || code == Protocol::ERR_ART_DOES_NOT_EXIST) {
      return vector<string>();
    }
  } else {
    result = vector<string>();
    result.push_back("Title: " + messageHandler->getStrParam());
    result.push_back("Author: " + messageHandler->getStrParam());
    result.push_back("Text: " + messageHandler->getStrParam());
  }
  code = messageHandler->getCode();
  checkCode("Delete article", Protocol::ANS_END, code);
  
  return result;
}

void ClientMessageHandler::checkCode(string method, int expectedCode, int code) throw(IllegalCommandException){
  if (code != expectedCode) {
    throw IllegalCommandException(method, expectedCode, code);
  }
}

void ClientMessageHandler::checkCondition(bool condition, string method, string message) throw(IllegalCommandException){
  if (!condition) {
    throw new IllegalCommandException(method, message);
    
  }
}
