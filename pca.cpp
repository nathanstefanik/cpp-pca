#include <iostream>
#include <Eigen/Dense>
#include <vector>
using Eigen::MatrixXd, Eigen::VectorXd;
using std::cout, std::endl;

struct eigen { 
  double val;
  VectorXd *vec;

  bool operator<(eigen const &other) const { 
      return value < other.val;
  }
};

#include <algorithm>
#include <vector>

void eigen_sort_rows_by_head(MatrixXd& A_nx3)
{
    std::vector<Eigen::VectorXd> vec;
    for (int64_t i = 0; i < A_nx3.rows(); ++i)
        vec.push_back(A_nx3.row(i));

    std::sort(vec.begin(), vec.end(), [](const std::pair<> t1, const std::pair< t2){ return t1.first < t2.first; } );

    for (int64_t i = 0; i < A_nx3.rows(); ++i)
        A_nx3.row(i) = vec[i];
};

class pca {
public:
  // https://www.eigen.tuxfamily.org/dox/group__TopicStructHavingEigenMembers.html
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

  // constructor. data is nxd with n data points and d features
  pca(MatrixXd* data_ptr): data_ptr{data_ptr}, dim{data_ptr->rows(), data_ptr->cols()} { }

  // displays data in matrix form
  void display() { cout << "data =\n" << *data_ptr << endl; }

  // returns dimensions of nxd data
  Eigen::Vector2i get_dim() { return dim; }

  // computes covariance of data located at data_ptr
  void compute_cov() {
    MatrixXd data = *data_ptr;
    // data.colwise.mean() will output scalar of each column's mean
    MatrixXd centered = data.rowwise() - data.colwise().mean(); // centers each column around column mean
    cov = (centered.transpose() * centered) / double(data.rows() - 1); // formula for covariance
    computed_cov = 1;
  }

  // gets covariance of data. computes if not initialized
  MatrixXd get_cov() {
    if (!computed_cov) { compute_cov(); }
    return cov;
  }

  // computes eigenvalues of covariance matrix of data
  void compute_eigen() {
    if (!computed_cov) { compute_cov(); }
    Eigen::EigenSolver<Eigen::MatrixXd> eigensolver;
    eigensolver.compute(cov);
    eigenval = eigensolver.eigenvalues().real();
    eigenvec = eigensolver.eigenvectors().real();
    computed_eigen = 1;
  }
  
  std::pair<VectorXd, MatrixXd> get_eigen() {
    if (!computed_eigen) { compute_eigen(); }
    return std::make_pair(eigenval, eigenvec);
  }

  // gets eigenvalues of covariance matrix. comptues if not initialized
  VectorXd get_eigenval() {
    if (!computed_eigen) { compute_eigen(); }
    return eigenval;
  }

  // gets eigenvectors of covariance matrix. computes if not initialized.
  MatrixXd get_eigenvec() {
    if (!computed_eigen) { compute_eigen(); }
    return eigenvec;
  }

  // returns transformed data = data * selected_covariance. selected covariance will be dxk, k <= d
  MatrixXd transform(int k) {
    if (!sorted_eigen) { sort_eigen(); }
    return *data_ptr * cov.leftCols(k);
  }

  // in-place sorts eigenvalues and corresponding eigenvector in descending order based on eigenval
  void sort_eigen() {
    if (!computed_eigen) { compute_eigen(); }
    
    sorted_eigen = 1;
  }


private:
  MatrixXd* data_ptr;     // pointer to nxd data. n data points, d features
  Eigen::Vector2i dim;    // 2x1 vector of dimensions (n, d)
  MatrixXd cov;           // covariance matrix
  VectorXd eigenval;      // dx1 vector of eigen values
  MatrixXd eigenvec;      // dxd matrix of eigen vectors
  bool computed_cov;      // True if already computed covariance. Else false
  bool computed_eigen;    // True if already computed eigenvalue and eigenvectors. Else false
  bool sorted_eigen;      // True if eigenvalues are sorted
};


int main() {
//  MatrixXd my_data = MatrixXd::Random(3,3); // 10x4 matrix of values randomly sampled from uniform distribution [0,1]
//  MatrixXd my_data(3,3);
//  my_data << 6, 55, 61, 
//            -34, 33, -32, 
//            -39, -4, 61;
//  MatrixXd my_data(2,2);
//  my_data << 1,1,
//             3,0;
  MatrixXd my_data(10,4);
  my_data << -40, 75, 31, -84, 
             1, -87, -84, 36, 
             -42, 98, 83, 86, 
             28, -79, -76, -100, 
             -98, -13, -79, 70, 
             32, 71, -68, -32, 
             -86, 40, -50, 45, 
             -11, -97, -46, -32, 
             32, 38, -71, 75, 
             22, 21, -40, -22;
  pca haha(&my_data);
  haha.display();
  cout << "haha.get_cov() =\n" << haha.get_cov() << '\n';
  auto penis = haha.get_eigen();
  cout << "eigen.first =\n" << penis.first << '\n';
  cout << "eigen.second =\n" << penis.second << '\n';
//  cout << "haha.dim() =\n" << haha.get_dim() << '\n';
//  int k = 2;
//  cout << "my_data.topLeftCorner(k, k) =\n" << my_data.topLeftCorner(k,k) << endl;

  cout << "haha.transform() =\n" << haha.transform(2) << endl;

}
