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

void saveDatabase(){
  std::ofstream file("url_db.txt");
  for (const auto& pair : urlDatabase){
    file << pair.first << std::endl << pair.second << std::endl;
  }
  file.close();
}

std::string generateShortUrl(int count){
  return std::to_string(count);
}

void shortenUrl(const std::string& originalUrl){
  static int count = 1;
  std::string shortUrl = generateShortUrl(count);
  urlDatabase[shortUrl] = originalUrl;
  saveDatabase();
  std::cout << "Shortened URL: http://short.ly/" << shortUrl << std::endl;
  count++;
}

void lookupUrl(const std::string& shortUrl){
  if(urlDatabase.find(shortUrl) != urlDatabase.end()){
    std::cout << "Original URL: " << urlDatabase[shortUrl] << std::endl;
  }else {
    std::cout << "URL not found!" << std::endl;
  }
}

int main(){
  loadDatabase();

  int choice;
  std::string url, shortUrl;

  while(true) {
    std::cout << "\n1. Shorten a URL\n2. Lookup a shortened URL\n3. Exit\nEnter your choice: ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
      case 1:
          std::cout << "Enter the URL to shorten: ";
          std::getline(std::cin, url);
          shortenUrl(url);
          break;
      case 2:
      std::cout << "Enter the shortened URL (e.g., '1'): ";
      std::getline(std::cin, shortUrl);
          lookupUrl(shortUrl);
          break;
      case 3:
      std::cout << "Exiting program." << std::endl;
          return 0;
      default:
      std::cout << "Invalid choice. Please try again." << std::endl;
  }
  }
}