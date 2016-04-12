#include "diskserver.h"

using namespace std;

DiskServer::DiskServer() {
}

DiskServer::DiskServer(const DiskServer& orig) {
}

/*
     * Lists all the news groups on the server.
     * Returns a vector containing id numbers and names for all the news groups. 
     */
    std::vector<std::pair<id,std::string> > list_ng() const = 0;
    
    /*
     * Creates a new news group.
     * Returns the id number of the newly created news group if successful, 
     * otherwise 0 if the name was already taken.
     */
    id create_ng(std::string& name) = 0;
    
    /*
     * Deletes a news group from the server.
     * Returns true if successful.
     */
    bool delete_ng(id ng) = 0;
    
    /*
     * Lists all the articles in a news group.
     * Returns a vector containing id numbers and names for all the articles. 
     */
    std::vector<std::pair<id, std::string> > listArt(id ng) const = 0;
    
    /*
     * Adds a new article in news group ng.
     * Returns true if the article was successfully added to ng.
     */
    bool add_art(id ng, const std::shared_ptr<Article>&) = 0;
    
    /*
     * Deletes an article.
     * Returns true if the article was successfully deleted.
     */
    bool delete_art(id ng, id art) = 0;
    
    /*
     * Get an article.
     * Returns a pointer to the article.
     * Returns nullptr if nothing was found.
     */
    std::shared_ptr<const Article> read_art(id ng, id art) const = 0;
    
    test