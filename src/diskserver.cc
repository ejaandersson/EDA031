#include "diskserver.h"

using namespace std;
using namespace tinyxml2;
    
    DiskServer::DiskServer(int port, string fileName) : ServerInterface(port), file(fileName) {
            if(xmlDoc.LoadFile(file.c_str()) != XML_SUCCESS)
                init_file();               
    }
    
    /*
     * A private function that initialize a new empty xml database file
     */
    void DiskServer::init_file(){
            file = "savexml.xml";
            XMLNode* root = xmlDoc.NewElement("newsserver");
            XMLElement* id_tag = xmlDoc.NewElement("newsgroup-id-count");
            id_tag->SetText(0);
        
            xmlDoc.InsertFirstChild(root);
            root->InsertFirstChild(id_tag);
            xmlDoc.SaveFile(file.c_str());
    }
    
    /*
     * Lists all the news groups on the server.
     * Returns a vector containing id numbers and names for all the news groups.
     * Returns an empty vector if no newsgroup exists.
     */
    vector<std::pair<id,string> > DiskServer::list_ng() const{
        vector<pair<id,string> > v;
        const char* ng_name;
        id ng_nbr;
        const XMLElement* name_tag;
        
        const XMLNode* root = xmlDoc.FirstChild();
        const XMLElement* newsgroup_tag = root->FirstChildElement("newsgroup");
        
        
        while(newsgroup_tag != nullptr){
            name_tag = newsgroup_tag->FirstChildElement("name");
            ng_name = name_tag->GetText();
            newsgroup_tag->QueryUnsignedAttribute("id", &ng_nbr);
            v.push_back(make_pair(ng_nbr, string(ng_name)));
            newsgroup_tag = newsgroup_tag->NextSiblingElement("newsgroup");
        }
        return v;
    }
    
    /*
     * Creates a new news group.
     * Returns the id number of the newly created news group if successful, 
     * otherwise 0 if the name was already taken.
     */
    id DiskServer::create_ng(string &name){
        if (exists_ng(name))
            return 0;
        
        id number;
        XMLElement* root = xmlDoc.RootElement();
        XMLElement* id_tag = const_cast<XMLElement*>(root->FirstChildElement());
        id_tag->QueryUnsignedText(&number);
        id_tag->SetText(++number);
        
        XMLElement* newsgroup_tag = xmlDoc.NewElement("newsgroup");
        newsgroup_tag->SetAttribute("id", number);
        
        XMLElement* name_tag = xmlDoc.NewElement("name");
        name_tag->SetText(name.c_str());
        
        XMLElement* art_id_tag = xmlDoc.NewElement("article-id-count");
        art_id_tag->SetText(0);
        
        root->InsertEndChild(newsgroup_tag);
        newsgroup_tag->InsertFirstChild(name_tag);
        newsgroup_tag->InsertEndChild(art_id_tag);
        xmlDoc.SaveFile(file.c_str());
        return number;
    }
    
    /*
     * Deletes a news group from the server.
     * Returns true if successful.
     */
    bool DiskServer::delete_ng(id ng){

        XMLElement* newsgroup_tag = find_ng_tag(ng);
        if (newsgroup_tag == nullptr)
            return false;
        
        xmlDoc.DeleteNode(newsgroup_tag);
        xmlDoc.SaveFile(file.c_str());
        return true;
    }
    
    /*
     * Lists all the articles in a news group.
     * Returns a vector containing id numbers and names for all the articles. 
     * Returns an empty vector if the newsgroup is empty or doesn't exist. 
     */
    std::vector<std::pair<id, std::string> > DiskServer::listArt(id ng) const{
        std::vector<std::pair<id, std::string> > v;
        
        XMLElement* ng_tag = find_ng_tag(ng);
        if(ng_tag == nullptr)
            return v;
        
        id art_nbr;
        string art_title;
        const XMLElement* title_tag;
        
        XMLElement* article_tag = ng_tag->FirstChildElement("article");        
        while(article_tag != nullptr){
            title_tag = article_tag->FirstChildElement("title");
            art_title = title_tag->GetText();
            article_tag->QueryUnsignedAttribute("id", &art_nbr);
            v.push_back(make_pair(art_nbr, string(art_title)));
            article_tag = article_tag->NextSiblingElement("article");
        }
        
        return v;
    }
    
    /*
     * Adds a new article in newsgroup ng.
     * Returns true if the article was successfully added to ng.
     */
    id DiskServer::add_art(id ng, const std::shared_ptr<Article>& a){
       
                id art_nbr = 0;

                XMLElement* ngt = find_ng_tag(ng);
                if (ngt == nullptr)
                    return art_nbr;
                
                const XMLElement* art_id_tag = ngt->FirstChildElement("article-id-count");
                art_id_tag->QueryUnsignedText(&art_nbr);
                (const_cast<XMLElement*>(art_id_tag))->SetText(++art_nbr);
                
                XMLElement* article_tag = xmlDoc.NewElement("article");
                ngt->InsertEndChild(article_tag);
              
                article_tag->SetAttribute("id", art_nbr);
                
                XMLElement* title_tag = xmlDoc.NewElement("title");
                article_tag->InsertFirstChild(title_tag);
                title_tag->SetText(a->getTitle().c_str());
                
                XMLElement* author_tag = xmlDoc.NewElement("author");
                article_tag->InsertEndChild(author_tag);
                author_tag->SetText(a->getAuthor().c_str());
                
                XMLElement* text_tag = xmlDoc.NewElement("text");
                article_tag->InsertEndChild(text_tag);
                text_tag->SetText(a->getText().c_str());
                
                xmlDoc.SaveFile(file.c_str());
                
                return art_nbr;
        
    }
    
    /*
     * Deletes an article.
     * Returns true if the article was successfully deleted.
     */
    bool DiskServer::delete_art(id ng, id art){
        
        XMLNode* article_tag = find_ng_tag(ng, art);
        if (article_tag == nullptr)
            return false;
        
        xmlDoc.DeleteNode(article_tag);
        xmlDoc.SaveFile("savexml.xml");
        return true;
    }
    
    /*
     * Gets an article.
     * Returns a pointer to the article.
     * Returns nullptr if any of the ids are invalid.
     */
    shared_ptr<const Article> DiskServer::read_art(id ng, id art) const{
        
        XMLElement* art_tag = find_ng_tag(ng, art);
        if(art_tag == nullptr)
            return nullptr;
        
        const XMLElement* title_tag = art_tag->FirstChildElement("title");
        shared_ptr<string> title = make_shared<string>(string(title_tag->GetText()));
        
        const XMLElement* author_tag = art_tag->FirstChildElement("author");
        shared_ptr<string> author = make_shared<string>(string(author_tag->GetText()));
        
        const XMLElement* text_tag = art_tag->FirstChildElement("text");
        shared_ptr<string> text = make_shared<string>(string(text_tag->GetText()));
        
        const Article* a = new const Article(*title, *author, *text); 
        return shared_ptr<const Article>(a);
    }
    
    /*
     * Checks if the newsgroup exists by id.
     * Returns true if it does.
     */
    bool DiskServer::exists_ng(id nbr) const{
        return find_ng_tag(nbr) != nullptr;
    }
    
    /*
     * Checks if the newsgroup exists by name.
     * Returns true if it does.
     */
    bool DiskServer::exists_ng(string &name) const{
        for(auto &p : list_ng()){
            if(!p.second.compare(name))
                return true;
        }
        return false;
    }
    
    /*
     * A private function
     * Fetches an an article tag
     * Fetches a newsgroup tag if art is set to 0 or left unset.
     * Returns the tag requested or nullptr if any id is invalid
     */
    XMLElement* DiskServer::find_ng_tag(id ng, id art) const{
        const XMLNode* root = xmlDoc.FirstChild();
        const XMLElement* newsgroup_tag = root->FirstChildElement("newsgroup");
        
        id nbr;
        while(newsgroup_tag != nullptr){
            newsgroup_tag->QueryUnsignedAttribute("id", &nbr);
            if (nbr == ng){
                if (art == 0)
                    return const_cast<XMLElement*>(newsgroup_tag);
                
                const XMLElement* article_tag = newsgroup_tag->FirstChildElement("article");
                while (article_tag != nullptr){
                    article_tag->QueryUnsignedAttribute("id", &nbr);                                       
                    if (nbr == art)
                        return const_cast<XMLElement*>(article_tag);
                    
                    article_tag = article_tag->NextSiblingElement("article");
                } 
                break;
            }               
            newsgroup_tag = newsgroup_tag->NextSiblingElement("newsgroup");
        }
        return nullptr;
    }
    
    
    
    
