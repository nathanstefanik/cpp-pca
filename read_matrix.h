// Copyright Robert Eisele 2017
#include <iostream>
#include <fstream>
#include <Eigen/Dense>

namespace file
{
  Eigen::MatrixXd readCSV(std::string file, int rows, int cols) {
    
    std::ifstream in;
    in.open(file);

    std::string line;

    int row = 0;
    int col = 0;

    Eigen::MatrixXd res = Eigen::MatrixXd(rows, cols);

    if (in.is_open()) {
      std::cout << "\ngrr 1\n" << std::endl; 
      while (std::getline(in, line)) {
  
        char *ptr = (char *) line.c_str();
        int len = line.length();
  
        col = 0;
  
        char *start = ptr;
        for (int i = 0; i < len; i++) {
          std::cout << "\ngrr 2\n" << std::endl;
          if (ptr[i] == ',') {
            std::cout << "start = " << start << std::endl;
            res(row, col++) = atof(start);
            start = ptr + i + 1;
          }
        }
        res(row, col) = atof(start);

        row++;
      }
  
      in.close();
    }
    return res;
  }
}
