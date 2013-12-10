#ifndef ELEMENTMATRIX_H
#define ELEMENTMATRIX_H

#ifndef ASSEMBLY_H
#include<Eigen/Dense>
#endif

namespace FEAPB {

class ElementMatrix {

public:

    Eigen::RowVector2i stiffness, mass,rhs;
    Eigen::Matrix<int,2,3> submatrices;

    std::tuple<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>> Submatrices(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& zwbases, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& zwgbases, double h, int _C);

    void Stiffness(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& stiffel, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& B, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& zw, Eigen::Matrix<double,15,15>& H, double &L);
    void Mass(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& massel, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& Nmat, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &zw, Eigen::Matrix<double,6,6> &HD, double &L);
    void RHS(Eigen::Matrix<double,Eigen::Dynamic,1>& rhsel, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& Nmat_force, Eigen::MatrixXi &conc, Eigen::MatrixXd &nodx, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &zw, Eigen::MatrixXd &P, Eigen::MatrixXd &Pl, Eigen::MatrixXd &UDL, int _C, double &L, int &ielem, std::string &BasesFunc);
};

} // end of namespace

#endif // ELEMENTMATRIX_H
