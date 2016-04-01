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
    
    virtual std::vector<std::pair<id,std::string> > list_ng() const override;
    virtual id create_ng(std::string) override;
    virtual bool delete_ng(id) override;
    virtual std::vector<std::pair<id, std::string> > listArt(id) const override;
    virtual bool add_art(id, Article&) override;
    virtual bool delete_art(id, id) override;
    virtual const Article* read_art(id, id) const override;
    
private:
    id number;
    std::map<id, Newsgroup> newsgroups;
    std::set<std::string> ng_names;

};

#endif /* INMEMORYSERVER_H */

