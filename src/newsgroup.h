#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"
#include <map>
#include <vector>
#include <memory>

using id = unsigned int;

class Newsgroup {
public:
    
    Newsgroup(std::string n) : name(n), number(0) {};
    virtual ~Newsgroup(){};
    
    id add_art(std::shared_ptr<Article>);
    bool delete_art(id nubr);
    const std::string& getName() const {return name;}
    std::shared_ptr<Article> get_art(id nbr) const;
    std::vector<std::pair<id, std::string> > list_art() const;

private:
    std::string name;
    id number;
    std::map<id, std::shared_ptr<Article> > articles; 
};

#endif /* NEWSGROUP_H */

