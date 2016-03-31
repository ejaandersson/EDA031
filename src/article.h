#ifndef ARTICLE_H
#define ARTICLE_H

#include <memory>
#include <string>

class Article {
public:
    
    Article(std::string titl, std::string auth, std::string txt) : title(titl), author(auth), text(new std::string(txt)) {}
    Article(const Article& orig) : title(orig.title), author(orig.author), text(new std::string(*orig.text)) {}
    virtual ~Article(){};
    
    std::string getTitle() const {return title;}
    std::string getAuthor() const {return author;}
    const std::string& getText() const {return *text;}
    
    void operator=(const Article& orig){
        title = orig.title;
        author = orig.author;
        *text = *orig.text;
        }
    
private:
    std::string title, author;
    std::unique_ptr<std::string> text;
    
};

#endif /* ARTICLE_H */

