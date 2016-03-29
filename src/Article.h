/* 
 * File:   Article.h
 * Author: Thoron
 *
 * Created on march 29, 2016, 16:11
 */

#include <memory>
#include <string>

#ifndef ARTICLE_H
#define ARTICLE_H

class Article {
public:
    Article(std::string t, std::string a, std::string te) : title(t), author(a), text(new std::string(te)) {}
    Article(const Article& orig) = delete;
    virtual ~Article();
    
    std::string getTitle() {return title;}
    
private:
    std::string title, author;
    std::unique_ptr<std::string> text;
    
};

#endif /* ARTICLE_H */

