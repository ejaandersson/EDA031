#include "inmemoryserver.h"

using namespace std;

/*
     * Lists all the news groups on the server.
     * Returns a vector containing id numbers and names for all the news groups. 
     */
    vector<pair<id,string>> InMemoryServer::list_ng() const{
        vector<pair<id,string>> v;
        v.reserve(newsgroups.size());
        for (const auto& kv : newsgroups)
            v.push_back(make_pair(kv.first, kv.second.getName()));
        return v;
    }
    
    /*
     * Creates a new news group.
     * Returns the id number of the newly created news group if successful, 
     * otherwise 0 if the name was already taken.
     */
    id InMemoryServer::create_ng(string& name){
        if(!ng_names.insert(name).second)
            return 0;
        newsgroups.insert(make_pair(++number, Newsgroup(name)));
        return number;
    }
    
    /*
     * Deletes a news group from the server.
     * Returns true if successful.
     */
    bool InMemoryServer::delete_ng(id ng){
        return false;
    }
    
    /*
     * Lists all the articles in a news group.
     * Returns a vector containing id numbers and names for all the articles. 
     */
    vector<pair<id, std::string>> InMemoryServer::listArt(id ng) const{
        vector<pair<id, std::string>> v;
        return v;
    }
    
    /*
     * Creates a new article in news group ng.
     * Returns true if the article was successfully added to ng.
     */
    bool InMemoryServer::add_art(id ng, Article& a){
        return false;
    }
    
    /*
     * Deletes an article.
     * Returns true if the article was successfully deleted.
     */
    bool InMemoryServer::delete_art(id ng, id art){
        return false;
    }
    
    /*
     * Get an article.
     * Returns an array containing title, author and text in that
     *  order starting at position zero through two.
     * Returns nullptr if nothing was found
     */
    const Article* InMemoryServer::read_art(id ng, id art) const {
        return nullptr;
    }
