#include <iostream>
#include <string>
#include <sstream>
#include <vector>
int main() {
  std::string st;
  std::getline(std::cin, st);
  std::istringstream iss(st);
  std::vector<std::string> words;
  std::string word;
  int sumlens = 0;
  while (iss >> word){
    words.push_back(word);
  }
  for (int i = 0; i < words.size(); i++){
    sumlens+=words[i].length();
  }
  sumlens = sumlens / words.size();
  for (int i = 0; i < words.size(); i++){
    if(words[i].size() <= sumlens) {
      words.erase(words.begin() + i); i--;
    }
  }
  for(int i = 0; i < words.size(); i++){
    std::cout << words[i] << " ";
  }
  return 0;
}
