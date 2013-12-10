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

#include"JacobiPolynomials.h"

using namespace Eigen;


Eigen::MatrixXd JacobiPolynomials::getJacobiPolynomials()
{
    MatrixXd pdp; //Declare pdp here otherwise it goes out of scope
    if (*_N>0)
    {
        //Alocate Size
        VectorXd p = VectorXd::Zero(*_N+1);
        VectorXd dp = VectorXd::Zero(*_N+1);

        //The first two polynomials are known
        p(0) = 1;   p(1) = 0.5*(*_a-*_b+(*_a+*_b+2)*(*_z));
        // The derivative of first polynomial
        dp(0) = 0;

        // Compute the rest upto degree n
        int an1,an2,an3,an4;
        for (int i=2; i<=*_N; i++)
        {
            an1 = 2*(i)*(i+*_a+*_b)*(2*i+*_a+*_b-2);
            an2 = (2*i+*_a+*_b-1)*(*_a*(*_a)-*_b*(*_b));
            an3 = (2*i+*_a+*_b-2)*(2*i+*_a+*_b-1)*(2*i+*_a+*_b);
            an4 = 2*(i+*_a-1)*(i+*_b-1)*(2*i+*_a+*_b);
            // Recursive formula for Jacobi polynomials
            p(i) = ((an2+an3*(*_z))*p(i-1)-an4*p(i-2))/an1;
        }

        for (int j=0; j<=*_N-1; j++)
        {
            dp(j+1) = 0.5*(*_a+*_b+j+2)*p(j);
        }

        //Store
        //MatrixXd pdp; //Declare pdp here otherwise it goes out of scope
        if (_opt)
        {
            pdp = MatrixXd::Zero(*_N+1,2);
            pdp.col(0)=p;    pdp.col(1)=dp;
        }
        else
        {
            pdp = VectorXd::Zero(*_N+1);    pdp = p;
        }
    }
    else
    {
        //Alocate Size
        VectorXd p = VectorXd::Zero(*_N+2);
        VectorXd dp = VectorXd::Zero(*_N+2);

        //The first two polynomials are known
        p(0) = 1;   p(1) = 0.5*(*_a-*_b+(*_a+*_b+2)*(*_z));
        //Store
        if (_opt)
        {
            pdp = MatrixXd::Zero(*_N+2,2);
            pdp.col(0)=p;    pdp.col(1)=dp;
        }
        else
        {
            pdp = VectorXd::Zero(*_N+2);    pdp = p;
        }
    }


    return pdp;
}

// Destructor not needed-added here for clarity
/*JacobiPolynomials::~JacobiPolynomials(){
    if (this->_a!=NULL)
    {
        // this points to the object i.e. JacobiPolynomials itself
        delete this->_a;
    }
    // or
    if (_a!=NULL)
    {
        delete _a;
    }
}*/
