#ifndef FIND_H
#define FIND_H

#ifndef ASSEMBLY_H
#include"Eigen/Dense"
#include"Eigen/Sparse"
#endif

// Sparse version
inline std::tuple<Eigen::Matrix<int,Eigen::Dynamic,1>,Eigen::Matrix<int,Eigen::Dynamic,1>,Eigen::Matrix<double,Eigen::Dynamic,1>>
find(Eigen::SparseMatrix<double>& A){

    int nnz = A.nonZeros();
    Eigen::VectorXi I(nnz), J(nnz);
    Eigen::VectorXd V(nnz);
    int counter = 0;
    for(int k=0; k<A.outerSize(); ++k)
        for (Eigen::SparseMatrix<double>::InnerIterator iter(A,k); iter; ++iter)
            {
                I(counter) = iter.row();
                J(counter) = iter.col();
                V(counter) = iter.value();
                counter+=1;
            }

return std::make_tuple(I,J,V);
}


// Dense version (needs more optimisation)
inline std::tuple<Eigen::Matrix<int,Eigen::Dynamic,1>,Eigen::Matrix<int,Eigen::Dynamic,1>,Eigen::Matrix<double,Eigen::Dynamic,1>>
find(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& A){

    // Converting dense to sparse is inefficient for large matrices
    Eigen::SparseMatrix<double> B = A.sparseView();
    int nnz = B.nonZeros();
    Eigen::VectorXi I(nnz), J(nnz);
    Eigen::VectorXd V(nnz);
    int counter = 0;
    for(int k=0; k<B.outerSize(); ++k)
        for (Eigen::SparseMatrix<double>::InnerIterator iter(B,k); iter; ++iter)
            {
                I(counter) = iter.row();
                J(counter) = iter.col();
                V(counter) = iter.value();
                counter+=1;
            }

return std::make_tuple(I,J,V);
}

#endif // FIND_H
