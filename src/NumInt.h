#ifndef NUMINT_H
#define NUMINT_H

#include<Eigen/Dense>

class NumInt {
public:
    //NumInt(const int N=0) {const int _N=N;}
    //NumInt(const int N=0) {}
    NumInt(){}      // Provide default constructor
    ~NumInt(){}     // Provide default destructor
    //NumInt& operator=(const NumInt & other);
    static Eigen::MatrixXd GuassQaudrature(const int &N, double &a, double &b);
    static Eigen::MatrixXd GuassLobattoQaudrature(const int& N);
};

#endif // NUMINT_H
