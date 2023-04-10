#include <iostream>
#include <fstream>
#include <Eigen/Dense>
using Eigen::MatrixXd;
using std::cout, std::endl;

// csv files must be in the following form:
// 123, 456, 789
// 135, 246, 357
// ...

namespace file
{
  // reads csv file and returns eigen matrix of data
  Eigen::MatrixXd read_csv(std::string file, int rows, int cols) {
    std::ifstream in;
    in.open(file);
    std::string line;
    int row = 0;
    int col = 0;
    MatrixXd res = MatrixXd(rows, cols);
    if (in.is_open())
    {
      while (std::getline(in, line))
      {
        char *ptr = (char *) line.c_str();
        int len = line.length();
        col = 0;
        char *start = ptr;
        for (int i = 0; i < len; i++) 
        {
          if (ptr[i] == ',')
          {
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

  // reads eigen matrix and writes data to a file with given filename
  void to_csv(MatrixXd data, std::string name)
  {
    std::ofstream file(name.c_str());
    for(int  i = 0; i < data.rows(); i++)
    {
      for(int j = 0; j < data.cols(); j++)
      {
        std::string str = std::to_string(data(i,j));
        if(j+1 == data.cols()) { file<<str; } else { file<<str<<','; }
      }
      file<<'\n';
    }
  }
}
