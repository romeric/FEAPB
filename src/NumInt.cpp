/** This program is an implemention of hp-finite elements for
*   three-dimensional linear piezoelectric beams.
*
*   © Copyright 2013 Roman Poya
*
*   This file is part of FEAPB.
*   FEAPB is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   any later version.
*
*   FEAPB is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with FEAPB.  If not, see <http://www.gnu.org/licenses/>.
*
*
*   Contact details: romanpoya@gmail.com or roman.poya@cimne.com
*/

#include"NumInt.h"
#include"JacobiPolynomials.h"

using namespace Eigen;

// Assignment Constructor : Not used
/*NumInt& NumInt::operator=(const NumInt & other) {
    if (this !=&other)
    {
        NumInt = other.NumInt;
        return *this;
    }
}
*/

MatrixXd NumInt::GuassQaudrature(const int& N, double& a, double& b) {

    int N0=N-1;
    const int N1 = N0+1;
    const int N2 = N0+2;

    VectorXd xu;
    xu.setLinSpaced(N1,-1.0,1.0);


    // Legendre-Gauss-Vandermonde Matrix
    //Matrix<double,N1,N2> L = Matrix<double,N1,N2>::Zero();
    MatrixXd L(N1,N2);
    L = MatrixXd::Zero(N1,N2);

    // Derivative of Legendre-Gauss-Vandermonde Matrix
    //Matrix<double,N1,1> Lp = Matrix<double,N1,1>::Zero();
    VectorXd Lp(N1);
    Lp = VectorXd::Zero(N1);


    VectorXd dum;
    dum.setLinSpaced(N1,0.0,N0);
    ArrayXd y;
    y = cos((2*dum.array()+1)*M_PI/(2*N0+2))+(0.27/N1)*sin(M_PI*xu.array()*N0/N2);

    double deps = std::numeric_limits<double>::epsilon();

    //Initial Guess
    //Array<double,N1,1> y0 = Array<double,N1,1>::Constant(2);
    ArrayXd y0 = ArrayXd::Constant(N1,2);

    while ((y-y0).abs().matrix().maxCoeff() > deps) {


        // L.col(0) = Matrix<double,N1,1>::Constant(1);
        L.col(0) = VectorXd::Constant(N1,1);
        //Lp = Matrix<double,N1,1>::Zero();
        Lp = VectorXd::Zero(N1);

        L.col(1) = y;

        for (int k=1; k!=N1; k++)
        {
            L.col(k+1) = ((2*k+1)*L.col(k).cwiseProduct(y.matrix())-k*L.col(k-1))/(k+1);
        }

        Lp = (N2)*(L.col(N0)-L.col(N1).cwiseProduct(y.matrix())).cwiseQuotient((1-y.square()).matrix());


        y0 = y;
        y = y0-(L.col(N1).cwiseQuotient(Lp)).array();
    }

    // Gauss Points
    //Matrix<double,N1,1> z = ((a*(1-y)+b*(1+y))/2).matrix();
    VectorXd z(N1);
    z = ((a*(1-y)+b*(1+y))/2).matrix();

    // Gauss Weights
    //Matrix<double,N1,1> w;
    VectorXd w(N1);
    w = (b-a)/(((1-y.square()).matrix()).cwiseProduct(Lp.cwiseProduct(Lp))).array()*pow((double)N2/N1,2);

    // Store
    //Matrix<double,N1,2> zw;
    Matrix<double,Dynamic,Dynamic> zw(N1,2);
    zw.col(0)=z;
    zw.col(1)=w;

    return zw;
}


MatrixXd NumInt::GuassLobattoQaudrature(const int &N) {

    int N0=N;
    double a=1.0; double b=1.0;
    double a1=2.0; double b1 = 2.0;
    if (N0>=1)
    {
        N0=N0-2;
    }

    // Build the pointers
    int* _N = &N0;
    double* _a=&a;     double* _b=&b;
    double* _a1=&a1;     double* _b1=&b1;

    // Initial Guess - Chebyshev-Gauss-Lobatto points
    ArrayXd xu;
    xu.setLinSpaced(N0+2,0.0,N0+1);
    ArrayXd x=-cos(xu/(N0+1)*M_PI);

    // Allocate space for points and weights
    VectorXd z = VectorXd::Zero(x.size());
    VectorXd w = VectorXd::Zero(x.size());

    double x0,x1,del; double* _x0 = &x0; double* _x1 = &x1;
    double deps = std::numeric_limits<double>::epsilon();
    for (int k=0; k<=x.size()-1; k++)
    {
        x0=x(k);
        del=2.0;
        while (fabs(del) > deps)
        {
            // Polynomial Deflation: Exclude the already determined roots
            VectorXd s1 = x.head(k);
            VectorXd ones = VectorXd::Constant(s1.size(),1);
            double s = (ones.cwiseQuotient((x0-s1.array()).matrix())).sum();
            // Compute Jacobi polynomial p(a,b)
            JacobiPolynomials J(_N,_a,_b,_x0,false);
            VectorXd p = J.getJacobiPolynomials();
            // Compute Jacobi polynomial p(a+1,b+1) for derivative dp(a,b)
            JacobiPolynomials J1(_N,_a1,_b1,_x0,false);
            VectorXd p1 = J1.getJacobiPolynomials();
            VectorXd dp=VectorXd::Zero(p1.size()); dp(0)=0;
            // Compute derivative of Jacobi polynomial p(a,b)
            for (int j=0; j<=*_N-1; j++)
            {
                dp(j+1) = 0.5*(*_a+*_b+j+2)*p1(j);
            }
            //Gauss-Lobatto points are roots of (1-x^2)*dp, hence
            double nom = (1-x0*x0)*p(N0);     double dnom = -2*x0*p(N0)+(1-x0*x0)*dp(N0);
            del = - nom/(dnom-nom*s);
            x1 = x0+del;
            x0=x1;
        }
        z(k)=x1;
        double a2=0; double b2=0; int N1=N0+1;
        double* _a2=&a2; double* _b2=&b2; int* _N1 = &N1;
        JacobiPolynomials J(_N1,_a2,_b2,_x1,false);
        VectorXd p = J.getJacobiPolynomials();

        w(k) = 2.0/((N1)*(N1+1)*p(N1)*p(N1));

    }

    // Store
    Matrix<double,Dynamic,Dynamic> zw(N0+2,2);
    zw.col(0)=z;
    zw.col(1)=w;

    return zw;
}
