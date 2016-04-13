#ifndef INMEMORYSERVER_H
#define INMEMORYSERVER_H

#include "serverinterface.h"
#include "newsgroup.h"
#include <set>

class InMemoryServer : public ServerInterface {
public:
    explicit InMemoryServer(int port) : ServerInterface(port), number(0) {}
    virtual ~InMemoryServer();
    
    std::vector<std::pair<id,std::string>> list_ng() const override;
    id create_ng(std::string&) override;
    bool delete_ng(id) override;
    std::vector<std::pair<id, std::string> > listArt(id) const override;
    id add_art(id, const std::shared_ptr<Article>&) override;
    bool delete_art(id, id) override;
    std::shared_ptr<const Article> read_art(id, id) const override;
    
private:
    id number;
    std::map<id, Newsgroup> newsgroups;
    std::set<std::string> ng_names;

};

#endif /* INMEMORYSERVER_H */

