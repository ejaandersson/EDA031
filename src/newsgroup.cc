#include "newsgroup.h"

using namespace std;

id Newsgroup::add_art(Article& a){
    articles.insert(make_pair(++number, a));
    return number;
}

bool Newsgroup::delete_art(id nbr){
    return articles.erase(nbr); 
}

const Article* Newsgroup::get_art(id nbr) const{
    auto a = articles.find(nbr); 
    return a != articles.end() ? &a->second : nullptr; 
}

vector<pair<id, string>> Newsgroup::list_art() const{
    vector<pair<id, string>> v;
    v.reserve(articles.size());
    for (const auto& kv : articles)
        v.push_back(make_pair(kv.first, kv.second.getTitle()));
    return v;
}