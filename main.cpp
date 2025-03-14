#include <iostream>
#include <unordered_map>
#include <fstream>

std::unordered_map<std::string, std::string> urlDatabase;

void loadDatabase(){
  std::ifstream file( "url_db.txt" );
  std::string shortUrl, originalUrl;
  while(getline( file, shortUrl) && getline(file, originalUrl)){
    urlDatabase[shortUrl] = originalUrl;
  }
  file.close();
}