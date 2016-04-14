
#ifndef DISKSERVER_H
#define DISKSERVER_H


#include "serverinterface.h"
#include "tinyxml2.h"

class DiskServer : public ServerInterface{
public:
    explicit DiskServer(int port, std::string fileName = "");
    virtual ~DiskServer(){};
    
    std::vector<std::pair<id,std::string>> list_ng() const override;
    id create_ng(std::string&) override;
    bool delete_ng(id) override;
    std::vector<std::pair<id, std::string> > listArt(id) const override;
    id add_art(id, const std::shared_ptr<Article>&) override;
    bool delete_art(id, id) override;
    std::shared_ptr<const Article> read_art(id, id) const override;
    bool exists_ng(id nbr) const override;
private:
    std::string file;
    tinyxml2::XMLDocument xmlDoc;
    
    void init_file();
    bool exists_ng(std::string&) const;
    tinyxml2::XMLElement* find_ng_tag(id ng, id art = 0) const;
};

#endif /* DISKSERVER_H */

