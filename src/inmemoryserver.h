#ifndef INMEMORYSERVER_H
#define INMEMORYSERVER_H

#include "server.h"
#include "serverinterface.h"
#include "newsgroup.h"
#include <set>

class InMemoryServer : public Server, public ServerInterface {
public:
    explicit InMemoryServer(int port) : Server(port), number(0) {}
    virtual ~InMemoryServer();
    
    virtual std::vector<std::pair<id,std::string> > list_ng() const;
    virtual id create_ng(std::string name);
    virtual bool delete_ng(id ng);
    virtual std::vector<std::pair<id, std::string> > listArt(id ng) const;
    virtual bool create_art(id ng, Article&);
    virtual bool delete_art(id ng, id art);
    virtual const Article* read_art(id ng, id art) const;
    
private:
    id number;
    std::map<id, Newsgroup> newsgroups;
    std::set<std::string> ng_names;

};

#endif /* INMEMORYSERVER_H */

