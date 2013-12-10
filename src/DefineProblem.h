#ifndef DEFINEPROBLEM_H
#define DEFINEPROBLEM_H

#include"Assembly.h"
#include"DirichletBoundaryConditions.h"
#include<unsupported/Eigen/src/IterativeSolvers/Scaling.h>

namespace FEAPB {

class DefineProblem {
public:
    DefineProblem(ReadData &InputData);
    Eigen::MatrixXd Solve();
    void Write();
private:
    Eigen::SparseMatrix<double,Eigen::ColMajor> stiffg;
    Eigen::SparseMatrix<double,Eigen::ColMajor> massg;
    Eigen::VectorXd F,_napp;
    Eigen::MatrixXd sol;
    int _analysis,_nwant;
    std::string time_int;
    Eigen::Matrix<double,Eigen::Dynamic,2> _dynP;
    std::string dynamicDataFileID;
    double mass;
};

} // end of namespace

#endif // SOLVE_H
