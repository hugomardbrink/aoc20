#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <omp.h>

int main() {
    // Sequential IO
    std::ifstream file{"../d1/input.txt"};
    std::vector<int> values;
    int n, answer;

    std::string line;
    while (std::getline(file, line))
    {
      std::stringstream iss(line);
      iss >> n;
      values.push_back(n);
    }
    
    int N = values.size();

    // Parallel kernel
    #pragma omp parallel shared(N, values, answer)
    {
      #pragma omp for schedule(static) nowait
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for(int k = 0; k < N; k++)
            {
                if(values[i] + values[j] + values[k] == 2020)
                {
                    #pragma omp critical
                    {
                        answer = values[i] * values[j] * values[k];
                    }
                }
            }
    }


    std::cout << answer << std::endl;

    return 0;
}