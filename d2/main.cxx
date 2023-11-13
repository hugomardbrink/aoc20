#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <omp.h>
#include <algorithm>

struct Entry{
  int min;
  int max;
  char letter;
  std::string password;
};


int main() {
    // Sequential IO
    std::ifstream file{"../d2/input.txt"};
    std::vector<Entry> entries;
    std::string password, ignore;
    int rangeMin, rangeMax;
    char letter;
    
    std::string line;
    while (std::getline(file, line))
    {
      std::replace(line.begin(), line.end(), '-', ' ');
      std::stringstream iss(line);
      iss >> rangeMin >> rangeMax >> letter >> ignore >> password;
      entries.push_back({rangeMin, rangeMax, letter, password});
    }

    int N = entries.size();
    int valid{0}, i;

    // Parallel kernel
    #pragma omp parallel shared(N, entries) private(i)
    {
      #pragma omp for reduction(+:valid)
      for(i = 0; i < N; i++)
       {
        Entry entry = entries[i];
        int count = std::ranges::count(entry.password, entry.letter);
        valid += !(entry.password[entry.min-1] == entry.letter) != !(entry.password[entry.max-1] == entry.letter);
      }
    }
    
    std::cout << valid << std::endl;

    return 0;
}