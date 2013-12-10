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

#include"hpBasis1D.h"
#include"NumInt.h"
#include<iostream>

using namespace Eigen;

//inline Eigen::MatrixXd hpBasis1D::Lagrange() {   inline does not work when a class is splitted into .h and .cpp
Eigen::MatrixXd hpBasis1D::Lagrange() {

    int n=_C+2;
    int nsize =n-1;
    double ndiv = 2.0/nsize;
    VectorXd eps=VectorXd::Zero(n);
    eps(0)=-1; eps(n-1)=1;
    if (_opt1==1)
    {
        for (int i=0; i<nsize; i++)
        {
            eps(i+1) = eps(i)+ndiv;
        }
    }
    else
    {
        const int n0=n;
        MatrixXd eps1=NumInt::GuassLobattoQaudrature(n0);
        eps = eps1.col(0);
    }

    //Construct Vandermonde Matrix
    MatrixXd A = MatrixXd::Zero(n,n);
    A.col(0)=VectorXd::Constant(A.rows(),1);

    for (int i=1; i<n; i++)
    {
        for (int s=0; s<n; s++)
        {
            A(s,i)=pow(eps(s),i);
        }
    }

    VectorXd N = VectorXd::Zero(n);
    VectorXd dN = VectorXd::Zero(n);
    VectorXd coeff = VectorXd::Zero(n);

    for (int ishape=0; ishape<n; ishape++)
    {
        VectorXd RHS = VectorXd::Zero(n);
        //VectorXd coeff = VectorXd::Zero(n);
        RHS(ishape)=1;
        //LU factorisation with full pivoting
        coeff = A.fullPivLu().solve(RHS);
//        if(!(A*coeff).isApprox(RHS))
//        {
//          std::cout << "The equation Ax=b does not have any solution." << std::endl;
//        }

        for (int incr=0; incr<n; incr++)
            N(ishape) += coeff(incr)*pow(_zi,incr);

        for (int incr=0; incr<n-1; incr++)
            dN(ishape) += (incr+1)*coeff(incr+1)*pow(_zi,incr);
    }

    MatrixXd basis;
    if (_opt2)
    {
        basis = MatrixXd::Zero(n,2);
        basis.col(0)=N; basis.col(1)=dN;
    }
    else
    {
        basis = MatrixXd::Zero(n,1);
        basis=N;
    }

    return basis;
}


Eigen::MatrixXd hpBasis1D::Legendre() {

    //Allocate
    VectorXd N(_C+2);
    VectorXd dN(_C+2);

    if (_C==0)
    {
        N << 1.0/2.0*(1-_zi), 1.0/2.0*(1+_zi);
        if (_opt2)
        {
            dN << -0.5, 0.5;
        }
    }
    else if (_C>0)
    {
     double p0=1.0; double p1=_zi;
     double dp0=0.0; double dp1=1.0;
     int ndim=_C+2;
     VectorXd P = VectorXd::Zero(ndim);
     P(0)=p0; P(1)=p1;
     VectorXd dP = VectorXd::Zero(ndim);
     dP(0)=dp0; dP(1)=dp1;
     // Generate Legendre Polynomials
     for (int i=1; i<ndim-1; i++)
     {
       P(i+1)=((2*i+1)*_zi*P(i) - (i)*P(i-1))/(i+1);
       if (_opt2)
       {
           dP(i+1)= ((2*i+1)*_zi*dP(i) + (2*i+1)*P(i) - (i)*dP(i-1))/(i+1);
       }
     }

     // From Legendre polynomials generate FE bases
     for (int i=2; i<ndim; i++)
     {
         N(i)= (P(i)-P(i-2))/sqrt(2.0*(2*i-1));
         if (_opt2)
         {
         dN(i) =  (dP(i)-dP(i-2))/sqrt(2*(2*i-1));
         }
     }

     N.segment(1,ndim-2) = N.segment(2,ndim-2).eval(); //eval is to ensure aliasing does not occur (uses temps)
     N(0)= 1.0/2.0*(1-_zi); N(ndim-1)= 1.0/2.0*(1+_zi);

     if (_opt2)
     {
         dN.segment(1,ndim-2) = dN.segment(2,ndim-2).eval(); //eval is to ensure aliasing does not occur
         dN(0)= -0.5; dN(ndim-1)= 0.5;
     }


    }
    else
    {
        std::cout <<"Invalid Interpolation Degree for Legendre Bases!"<< std::endl;
    }

    MatrixXd basis;
    if (_opt2)
    {
        basis = MatrixXd::Zero(_C+2,2);
        basis.col(0)=N; basis.col(1)=dN;
    }
    else
    {
        basis = MatrixXd::Zero(_C+2,1);
        basis=N;
    }

    return basis;
}
