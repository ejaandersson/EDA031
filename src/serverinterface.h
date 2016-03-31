#ifndef SERVERINTERFACE_H
#define	SERVERINTERFACE_H

#include <string>

  using id = unsigned int; 
  
class ServerInterface {
public:
    
    /*
     * Lists all the news groups on the server.
     * Returns a vector containing id numbers and names for all the news groups. 
     */
    virtual std::vector<std::pair<id, std::string>> list_ng() const = 0;
    
    /*
     * Creates a new news group.
     * Returns the id number of the newly created news group if successful, 
     * otherwise 0 if the name was already taken.
     */
    virtual id create_ng(std::string name) = 0;
    
    /*
     * Deletes a news group from the server.
     * Returns true if successful.
     */
    virtual bool delete_ng(id ng) = 0;
    
    /*
     * Lists all the articles in a news group.
     * Returns a vector containing id numbers and names for all the articles. 
     */
    virtual std::vector<std::pair<id, std::string>> listArt(id ng) const = 0;
    
    /*
     * Creates a new article in news group ng.
     * Returns true if the article was successfully added to ng.
     */
    virtual bool create_art(id ng, std::string& title, std::string& author, std::string& text) = 0;
    
    /*
     * Deletes an article.
     * Returns true if the article was successfully deleted.
     */
    virtual bool delete_art(id ng, id art) = 0;
    
    /*
     * Get an article.
     * Returns an array containing title, author and text in that
     *  order starting at position zero through two.
     * Returns nullptr if nothing was found
     */
    virtual const char* read_art(id ng, id art) const = 0;
    
private:

};


#endif	/* SERVERINTERFACE_H */

