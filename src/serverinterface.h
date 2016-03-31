/* 
 * File:   ServerInterface.h
 *
 * Created on den 29 mars 2016, 14:26
 */


#include <string>


#ifndef SERVERINTERFACE_H
#define	SERVERINTERFACE_H



class ServerInterface {
public:
    
    using id = size_t; 
    
    virtual std::map<id, std::string> listNG() = 0;
    
    virtual id createNG(std::string) = 0;
    
    virtual bool deleteNG(id) = 0;
    
    virtual std::map<id, std::string> listArt(id art) = 0;
    
    virtual id createArt(id ng, std::string& title, std::string& author, std::string& text) = 0;
    
    virtual bool deleteArt(id ng, id art) = 0;
    
    virtual std::string readArt(id ng, id art) = 0;
    
private:

};


#endif	/* SERVERINTERFACE_H */

