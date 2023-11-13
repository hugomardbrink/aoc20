#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <omp.h>
#include <algorithm>

int main() {
  // Sequential IO
  std::ifstream file{"../d3/input.txt"};
  std::vector<std::string> rows;

  std::string line;
  while (std::getline(file, line))
    rows.push_back(line);
  
  int N = rows.size(), j, width = rows[0].size();
  long long hits = 1;
  std::vector<int> slopes{1,1,3,1,5,1,7,1,1,2};
  
  // Parallel kernel
  #pragma omp parallel for reduction(*:hits) private(j)
  for(j = 0; j < slopes.size()/2; j++)
  {
      int right = slopes[j*2], down = slopes[(j*2)+1], treeHits = 0;
      for(int i = 0; i < N; i += down)
        treeHits += rows[i][(i / down * right) % width] == '#';
      
      hits *= treeHits;
  }
  std::cout << hits << std::endl;
    
  return 0;
}