#include "inmemoryserver.h"

using namespace std;

/*
     * Lists all the news groups on the server.
     * Returns a vector containing id numbers and names for all the news groups. 
     */
    vector<pair<id,string>> InMemoryServer::list_ng() const {
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
    id InMemoryServer::create_ng(string& name) {
        if (!ng_names.insert(name).second)
            return 0;
        newsgroups.insert(make_pair(++number, Newsgroup(name)));
        return number;
    }
    
    /*
     * Deletes a news group from the server.
     * Returns true if successful.
     */
    bool InMemoryServer::delete_ng(id ng) {
        auto it = newsgroups.find(ng);
        if (it == newsgroups.end())
          return false;
        newsgroups.erase(it);
        return true;
    }
    
    /*
     * Lists all the articles in a news group.
     * Returns a vector containing id numbers and names for all the articles. 
     */
    vector<pair<id, string>> InMemoryServer::listArt(id ng) const {
        auto it = newsgroups.find(ng);
        if (it == newsgroups.end()) {
          return vector<pair<id, string>>();
        }
        return  it->second.list_art();
    }
    
    /*
     * Adds a new article in news group ng.
     * Returns the id number of the inserted article if successful,
     * otherwise 0 if the newsgroup id coudln't be found.
     */
    id InMemoryServer::add_art(id ng, const shared_ptr<Article> &a) {
        auto it = newsgroups.find(ng);
        if (it == newsgroups.end()) {
          return 0;
        }
        return it->second.add_art(a);
    }
    
    /*
     * Deletes an article.
     * Returns true if the article was successfully deleted.
     */
    bool InMemoryServer::delete_art(id ng, id art) {
        auto it = newsgroups.find(ng);
        if (it == newsgroups.end()) {
          return false;
        }
        return it->second.delete_art(art);
    }
    
    /*
     * Get an article.
     * Returns an array (nopes: an Article ptr at the moment) containing title, author and text in that
     *  order starting at position zero through two.
     * Returns nullptr if nothing was found
     */
    shared_ptr<const Article> InMemoryServer::read_art(id ng, id art) const {
        auto it = newsgroups.find(ng);
        if (it == newsgroups.end()) {
          return nullptr;
        }
        return it->second.get_art(art);
    }
    
    bool InMemoryServer::exists_ng(id ng) {
      if (newsgroups.empty()) {
        return false;
      }
      auto it = newsgroups.find(ng);
      if (it == newsgroups.end()) {
        return false;
      }
      return true;
    }
