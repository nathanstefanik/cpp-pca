#include "file_matrix.h"
#include "pca.h"
using namespace file;
using namespace pca_class;
using std::cout, std::endl;

int main()
{
  MatrixXd my_data = read_csv("data.csv", 200, 2);
  //cout << "my_data =\n" << my_data << endl;
//  MatrixXd my_data = MatrixXd::Random(3,3); // 10x4 matrix of values randomly sampled from uniform distribution [0,1]
//  MatrixXd my_data(3,3);
//  my_data << 6, 55, 61, 
//            -34, 33, -32, 
//            -39, -4, 61;
//  MatrixXd my_data(2,2);
//  my_data << 1,1,
//             3,0;
  //MatrixXd my_data(10,4);
  //my_data << -40, 75, 31, -84, 
  //           1, -87, -84, 36, 
  //           -42, 98, 83, 86, 
  //           28, -79, -76, -100, 
  //           -98, -13, -79, 70, 
  //           32, 71, -68, -32, 
  //           -86, 40, -50, 45, 
  //           -11, -97, -46, -32, 
  //           32, 38, -71, 75, 
  //           22, 21, -40, -22;
  pca haha(&my_data);
  //haha.display();
  cout << "haha.get_cov() =\n" << haha.get_cov() << '\n';
  MatrixXd reduced = haha.transform(2);
  //cout << "reduced =\n" << reduced << endl;
  to_csv(reduced, "reduced.csv");
}
