// eigen class for eigenvalues and eigenvectors
// provides custom sorting algorithm

#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <algorithm>
using Eigen::MatrixXd, Eigen::VectorXd;
using std::cout, std::endl, std::pair;

// TODO
// * fix rebuilding of eigen

namespace eigen_class
{
class eigen 
{
public:
  // constructor
  eigen(VectorXd val, MatrixXd vec): val{val}, vec{vec}, dim{val.size()} { }

  // sorts eigenvalues and corresponding eigenvectors in descdending value by eigenvalue
  void sort() 
  {
    if (sorted) { return; }

    // load up eigen pairs into an array
    std::vector<pair<double, VectorXd>> eigen_pairs;
    for (int i = 0; i < dim; i++)
    {
      pair<double, VectorXd> curr(val(i), vec.col(i)); 
      eigen_pairs.push_back(curr);
    }
    
    // sort array of (eigenvalue, eigenvector) pairs by descending eigenvalue
    std::sort(eigen_pairs.begin(), 
              eigen_pairs.end(), 
              [](const pair<double, VectorXd> p1, const pair<double, VectorXd> p2) // lambda function
              {
                return p1.first > p2.first; // we only want to sort based off of eigenvalues
              });

    // rebuild eigenvalue vector and eigenvector matrix
    VectorXd new_val(dim);
    MatrixXd new_vec(dim, dim);
    for (int i = 0; i < dim; i++)
    {
      new_val(i) = eigen_pairs[i].first;
      new_vec.row(i) = eigen_pairs[i].second;
    }

    // set pointers to new values
    val = new_val;
    vec = new_vec;
    sorted = 1;
  }

  // gets val
  VectorXd get_val() { return val;  }
    
  // gets vec
  MatrixXd get_vec() { return vec; }

  private:
    VectorXd val;   // pointer to eigenvalues
    MatrixXd vec;   // pointer to eigenvectors
    bool sorted;    // True if sorted by descending eigenvalue. False otherwise
    long dim;       // Eigen implements size to be type long
  };
};
