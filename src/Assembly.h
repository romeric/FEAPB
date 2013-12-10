#ifndef ASSEMBLY_H
#define ASSEMBLY_H

// Forward declare FEAPB::ReadData class
//namespace FEAPB { class ReadData;}

#include<Eigen/Sparse>
#include"ReadDataFile.h"

// Do include these in the final release mode
//#include <emmintrin.h>
//#include <xmmintrin.h>


namespace FEAPB {
void Assembly(FEAPB::ReadData &InputData, Eigen::MatrixXi &conc, Eigen::MatrixXd &nodx, double &h, int &C, int &n, Eigen::SparseMatrix<double> &stiffg, Eigen::SparseMatrix<double> &massg, Eigen::VectorXd &F, Eigen::MatrixXd &Dirichlet_data);
}

#endif // ASSEMBLY_H
