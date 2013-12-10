#ifndef DIRICHLETBOUNDARYCONDITIONS_H
#define DIRICHLETBOUNDARYCONDITIONS_H

#ifndef ASSEMBLY_H
#include<Eigen/Dense>
#include<Eigen/Sparse>
#endif


namespace FEAPB {

void DirichletBoundaryConditions(Eigen::SparseMatrix<double,Eigen::ColMajor>& stiffg, Eigen::VectorXd& F, Eigen::Matrix<double,Eigen::Dynamic,3>& Dirichlet_Boundary_Conditions);
void DirichletBoundaryConditions(Eigen::Matrix<double,Eigen::Dynamic,3>& Dirichlet_Boundary_Conditions, Eigen::MatrixXi &conc,Eigen::MatrixXd &Dirichlet_data);

template<typename T>
std::vector<size_t> ordered(std::vector<T> const& values)
{
    std::vector<size_t> indices(values.size());
    std::iota(begin(indices),end(indices),static_cast<size_t>(0));

    std::sort(begin(indices),end(indices),[&](size_t a, size_t b){return values[a]<values[b];});
    return indices;
}

} // end of namespace


#endif // DIRICHLETBOUNDARYCONDITIONS_H
