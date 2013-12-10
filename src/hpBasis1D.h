#ifndef HPBASIS1D_H
#define HPBASIS1D_H

#include<Eigen/Dense>

class hpBasis1D {
private:
    int _C;
    double _zi;
    int _opt1;  // 1- ES, 2- GLL
    bool _opt2; // true-[N,dN], false-[N]
public:
    hpBasis1D(){_C=0; _zi=0; _opt2=true; _opt1=2;}
    hpBasis1D(int C){_C=C; _zi=0; _opt2=true; _opt1=2;}
    hpBasis1D(int C, double zi) {_C=C; _zi=zi; _opt1=2; _opt2=true;}
    hpBasis1D(int C, double zi, int opt1) {_C=C; _zi=zi; _opt2=true; _opt1=opt1;}
    hpBasis1D(int C, double zi, int opt1, bool opt2) {_C=C; _zi=zi; _opt2=opt2; _opt1=opt1;}
    Eigen::MatrixXd Lagrange();
    Eigen::MatrixXd Legendre();
};

#endif // HPBASIS1D_H
