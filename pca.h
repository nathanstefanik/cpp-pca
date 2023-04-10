#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <stdexcept>
#include "eigen.h"
using Eigen::MatrixXd, Eigen::VectorXd;
using std::cout, std::endl;
using namespace eigen_class;

// TODO
// 1. add argument validation
namespace pca_class
{
  class pca 
  {
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
      computed_eigen = true;
      sorted_eigen = false;
    }
   
    // gets eigenvalue and eigenvector pairs of covariance matrix. computes if not initialized
    std::pair<VectorXd, MatrixXd> get_eigen() {
      if (!computed_eigen) { compute_eigen(); }
      return std::make_pair(eigenval, eigenvec);
    }

    // gets eigenvalues of covariance matrix. computes if not initialized
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
      return *data_ptr * eigenvec.leftCols(k);
    }

    // in-place sorts eigenvalues and corresponding eigenvector in descending order based on eigenval
    void sort_eigen() 
    {
      if (!computed_eigen) { compute_eigen(); }
      if (sorted_eigen) { cout << "\nloser\n" << endl; return; }
      eigen tmp(eigenval, eigenvec);
      tmp.sort();
      eigenval = tmp.get_val();
      eigenvec = tmp.get_vec();
      sorted_eigen = true;
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
}
