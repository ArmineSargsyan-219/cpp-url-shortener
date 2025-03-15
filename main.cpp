#include <iostream>
#include <unordered_map>
#include <fstream>
#include <cstdlib>

std::unordered_map<std::string, std::string> urlDatabase;

void loadDatabase() {
  std::ifstream file("url_db.txt");
  std::string shortUrl, originalUrl;
  while (std::getline(file, shortUrl) && std::getline(file, originalUrl)) {
    urlDatabase[shortUrl] = originalUrl;
  }
  file.close();
}

void saveDatabase() {
  std::ofstream file("url_db.txt");
  for (const auto& pair : urlDatabase) {
    file << pair.first << std::endl << pair.second << std::endl;
  }
  file.close();
}

std::string generateShortUrl(int count) {
  return std::to_string(count);
}

void shortenUrl(const std::string& originalUrl) {
  static int count = 1;
  std::string shortUrl = generateShortUrl(count);
  urlDatabase[shortUrl] = originalUrl;
  saveDatabase();
  std::cout << "Shortened URL: http://short.ly/" << shortUrl << std::endl;
  count++;
}

void lookupUrl(const std::string& shortUrl) {
  if (urlDatabase.find(shortUrl) != urlDatabase.end()) {
    std::string originalUrl = urlDatabase[shortUrl];
    std::cout << "Opening: " << originalUrl << std::endl;
    
    #ifdef _WIN32
        std::system(("start " + originalUrl).c_str()); // Windows
    #elif __APPLE__
        std::system(("open " + originalUrl).c_str());  // macOS
    #else
        std::system(("xdg-open " + originalUrl).c_str()); // Linux
    #endif
  } else {
    std::cout << "URL not found!" << std::endl;
  }
}

void deleteUrl(const std::string& shortUrl) {
  auto it = urlDatabase.find(shortUrl);
  if (it != urlDatabase.end()) {
    urlDatabase.erase(it); 
    saveDatabase();        
    std::cout << "Shortened URL " << shortUrl << " has been deleted." << std::endl;
  } else {
    std::cout << "Shortened URL not found!" << std::endl;
  }
}

int main() {
  loadDatabase();

  int choice;
  std::string url, shortUrl;

  while (true) {
    std::cout << "\n1. Shorten a URL\n2. Lookup a shortened URL\n3. Delete a shortened URL\n4. Exit\nEnter your choice: ";
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
        std::cout << "Enter the shortened URL to delete: ";
        std::getline(std::cin, shortUrl);
        deleteUrl(shortUrl);
        break;
      case 4:
        std::cout << "Exiting program." << std::endl;
        return 0;
      default:
        std::cout << "Invalid choice. Please try again." << std::endl;
    }
  }
}