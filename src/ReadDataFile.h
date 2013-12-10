#ifndef READDATAFILE_H
#define READDATAFILE_H

#if defined __cplusplus

#include<Eigen/Dense>

//#pragma warning(push, 0) // compile-time inefficiency, also compiler specific and doesnot work here.
//include librarys with warning
//#pragma warning(pop)

#include <boost/algorithm/string/find.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include<iostream>
#include <iomanip>
#include<math.h>
#include<fstream>
#include<ios>
#include <tuple>

#endif

namespace FEAPB {

struct ReadData {
    std::string Base,NInt,AIso,DInt,DynFile;
    int C,n,dim,Analysis,nnz,nrows,ncols;
    double x1,x2,x3,densi,shfac;
    //Eigen::MatrixXd Elast,IsoElast,Piezo,Die;
    Eigen::Matrix<double,6,6> Elast;
    Eigen::Vector2d IsoElast;
    Eigen::Matrix<double,3,9> Piezo;
    Eigen::Matrix<double,3,3> Die;
    Eigen::Matrix<double,Eigen::Dynamic,3> Dirichlet_Boundary_Conditions;
    Eigen::MatrixXd pForce,pForcePos,udl_Force;
    Eigen::Matrix<double,Eigen::Dynamic,2> dynForce;
    Eigen::Matrix<double,1,2> dynNode;
};

ReadData ReadDataFile();
void CheckPrintDataFile(ReadData *InputData);

std::tuple<Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic>,
Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>,double> ConcNodx(int &C,int &n,double &Length);


} // end of namespace


#endif // READDATAFILE_H
