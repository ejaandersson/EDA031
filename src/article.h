#ifndef ARTICLE_H
#define ARTICLE_H

#include <memory>
#include <string>

class Article {
public:
    
    Article(std::string titl, std::string auth, std::string txt) : title(titl), author(auth), text(txt) {}
    virtual ~Article(){}
    
    std::string getTitle() const {return title;}
    std::string getAuthor() const {return author;}
    const std::string& getText() const {return text;}
        
private:
    std::string title, author, text;
    
};


#endif /* ARTICLE_H */

