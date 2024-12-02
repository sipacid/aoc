#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isSafeReport(const std::vector<int> &levels) {
  if (levels.size() < 2)
    return false;

  int type = 0; // 0 unknown; 1 increasing; 2 decreasing

  for (size_t i = 1; i < levels.size(); ++i) {
    int difference = levels[i] - levels[i - 1];

    if (std::abs(difference) < 1 || std::abs(difference) > 3) {
      return false;
    }

    if (difference > 0) {
      if (type == 0)
        type = 1;
      if (type == 2)
        return false;
    } else if (difference < 0) {
      if (type == 0)
        type = 2;
      if (type == 1)
        return false;
    }
  }

  return true;
}

bool isSafeReport2(const std::vector<int> &levels) {
  if (isSafeReport(levels))
    return true;

  for (int i = 0; i < levels.size(); i++) {
    std::vector<int> newLevels = levels;
    newLevels.erase(newLevels.begin() + i);
    if (isSafeReport(newLevels))
      return true;
  }

  return false;
}

int main(int argc, char *argv[]) {
  std::ifstream f("input.txt");
  if (!f.is_open()) {
    std::cerr << "Error opening the file." << std::endl;
    return 1;
  }

  int safeReports = 0;
  int safeReports2 = 0;
  std::string line;

  while (std::getline(f, line)) {
    std::vector<int> levels;
    std::istringstream iss(line);
    int level;

    while (iss >> level)
      levels.push_back(level);

    if (isSafeReport(levels))
      safeReports++;

    if (isSafeReport2(levels))
      safeReports2++;
  }

  std::cout << safeReports << std::endl;
  std::cout << safeReports2 << std::endl;

  return 0;
}
