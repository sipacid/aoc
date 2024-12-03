#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char *argv[]) {
  std::ifstream f("input.txt");
  if (!f.is_open()) {
    std::cerr << "Error opening the file." << std::endl;
    return 1;
  }

  const std::regex mulRegex(
      R"(mul\(([0-9]{1,3}),([0-9]{1,3})\)|do\(\)|don't\(\))");

  int total = 0;
  int totalFiltered = 0;
  bool doAdd = true;

  std::string inputText;
  std::string line;

  while (std::getline(f, line)) {
    for (std::sregex_iterator it(line.begin(), line.end(), mulRegex), end_it;
         it != end_it; ++it) {
      if (it->str() == "do()") {
        doAdd = true;
        continue;
      }

      if (it->str() == "don't()") {
        doAdd = false;
        continue;
      }

      total += (std::stoi(it->str(1)) * std::stoi(it->str(2)));

      if (doAdd)
        totalFiltered += (std::stoi(it->str(1)) * std::stoi(it->str(2)));
    }
  }

  f.close();

  std::cout << total << std::endl;
  std::cout << totalFiltered << std::endl;

  return 0;
}
