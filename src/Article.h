/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Article.h
 * Author: Thoron
 *
 * Created on den 29 mars 2016, 16:11
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

