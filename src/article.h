#ifndef ARTICLE_H
#define ARTICLE_H

#include <memory>
#include <string>

class Article {
public:
    using id = unsigned int;
    
    Article(id nbr, std::string titl, std::string auth, std::string txt) : number(nbr), title(titl), author(auth), text(new std::string(txt)) {}
    virtual ~Article();
    
    id getId() const {return number;}
    std::string getTitle() const {return title;}
    std::string getAuthor() const {return author;}
    const std::string& getText() const {return *text;}
    
private:
    const id number;
    std::string title, author;
    std::unique_ptr<std::string> text;
};

#endif /* ARTICLE_H */

