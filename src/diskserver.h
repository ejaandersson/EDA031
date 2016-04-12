
#ifndef DISKSERVER_H
#define DISKSERVER_H

#include "server.h"
#include "serverinterface.h"

class DiskServer : public Server, public ServerInterface {
public:
    explicit DiskServer(int port) : Server(port){};
    virtual ~DiskServer(){};
    
    std::vector<std::pair<id,std::string>> list_ng() const override;
    id create_ng(std::string&) override;
    bool delete_ng(id) override;
    std::vector<std::pair<id, std::string> > listArt(id) const override;
    bool add_art(id, const std::shared_ptr<Article>&) override;
    bool delete_art(id, id) override;
    std::shared_ptr<const Article> read_art(id, id) const override;
private:

};

#endif /* DISKSERVER_H */

