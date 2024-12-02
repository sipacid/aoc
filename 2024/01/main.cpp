#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>

int main(int argc, char *argv[]) {
  std::ifstream f("input.txt");
  if (!f.is_open()) {
    std::cerr << "Error opening the file." << std::endl;
    return 1;
  }

  std::vector<int> firstList, secondList;
  int first, second;

  while (f >> first >> second) {
    firstList.push_back(first);
    secondList.push_back(second);
  }

  f.close();

  int lengthOfList = sizeof(firstList) / sizeof(firstList[0]);
  std::sort(firstList.begin(), firstList.end());
  std::sort(secondList.begin(), secondList.end());

  int totalDifference = 0;
  for (int i = 0; i < firstList.size(); i++) {
    totalDifference += std::abs(firstList[i] - secondList[i]);
  }

  std::cout << totalDifference << std::endl;

  std::pmr::unordered_map<int, int> firstListFrequency;
  for (int number : firstList) {
    firstListFrequency[number]++;
  }

  std::pmr::unordered_map<int, int> secondListFrequency;
  for (int number : secondList) {
    secondListFrequency[number]++;
  }

  int similarityScore = 0;
  for (const std::pair<const int, int> &pair : firstListFrequency) {
    similarityScore +=
        (pair.first * pair.second * secondListFrequency[pair.first]);
  }

  std::cout << similarityScore << std::endl;

  return 0;
}
