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

#include"ElementMatrix.h"
#ifndef ASSEMBLY_H
#include"hpBasis1D.h"
#endif
#include <iostream>

namespace FEAPB {

std::tuple<Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>,Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>> ElementMatrix::Submatrices(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& zwbases, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& zwgbases, double h, int _C)
{

    Eigen::MatrixXd B, Nmat, Nmat_force;
    B.setZero(15,11*(_C+2)); Nmat.setZero(6,11*(_C+2)); Nmat_force.setZero(11,11*(_C+2));

    Eigen::MatrixXd B_all(15*zwbases.cols(),11*(_C+2));
    Eigen::MatrixXd Nmat_all(6*zwbases.cols(),11*(_C+2));
    Eigen::MatrixXd Nmat_force_all(11*zwbases.cols(),11*(_C+2));

    // Loop over integration points
    for (int g=0; g<zwbases.cols(); g++)
    {
        for (int i=0; i<11; i++)
        {
            if (i<=5 || i==8)
            {
                for (int index=0; index<zwbases.rows(); index++)
                {
                    B(i,i+11*index)=zwgbases(index,g)*2/h;
                }
            }
            else if (i>5 && i<8)
            {
                for (int index=0; index<zwbases.rows(); index++)
                {
                    B(i,i+11*index)=zwbases(index,g);
                    B(i+3,i+11*index)=zwgbases(index,g)*2/h;
                }
            }
            else if (i>8)
            {
                for (int index=0; index<zwbases.rows(); index++)
                {
                    B(i+2,i+11*index)=zwbases(index,g);
                    B(i+4,i+11*index)=zwgbases(index,g)*2/h;
                }
            }
        }
        for (int index=0; index<zwbases.rows(); index++)
        {
            B(0,4+11*index)=-zwbases(index,g);
            B(1,3+11*index)=zwbases(index,g);
        }

        // For modal/dynamic analysis
        for (int i=0; i<6; i++)
        {
            for (int index=0; index<zwbases.rows(); index++)
            {
                Nmat(i,i+11*index)=zwbases(index,g);
            }
        }
//        std::cout << Nmat.block(0,0,6,6) << std::endl << std::endl;

        // For RHS
        for (int i=0; i<11; i++)
        {
            for (int index=0; index<zwbases.rows(); index++)
            {
                Nmat_force(i,i+11*index)=zwbases(index,g);
            }
        }

        B_all.block(15*g,0,15,11*(_C+2)) = B;
        Nmat_all.block(6*g,0,6,11*(_C+2)) = Nmat;
        Nmat_force_all.block(11*g,0,11,11*(_C+2)) = Nmat_force;


    }

    submatrices << B_all.rows(), B_all.cols(), Nmat_all.rows(),Nmat_all.cols(),Nmat_force_all.rows(),Nmat_force_all.cols();

    return std::make_tuple(B_all,Nmat_all,Nmat_force_all);
}


// Elemental Stiffness Matrix
void ElementMatrix::Stiffness(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& stiffel, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& B, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& zw, Eigen::Matrix<double,15,15>& H, double &L){

    for (int g=0; g<zw.rows(); g++)
    {
        // Build Stiffness Matrix
        stiffel +=(B.block(15*g,0,15,B.cols()).transpose()*H*B.block(15*g,0,15,B.cols())).eval()*zw(g,1)*L/2;
    }

    stiffness << stiffel.rows(), stiffel.cols();
}

// Elemental Mass Matrix
void ElementMatrix::Mass(Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& massel, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& Nmat, Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &zw, Eigen::Matrix<double,6,6> &HD, double &L){

    for (int g=0; g<zw.rows(); g++)
    {
        // Build Mass Matrix
        massel +=(Nmat.block(6*g,0,6,Nmat.cols()).transpose()*HD*Nmat.block(6*g,0,6,Nmat.cols())).eval()*zw(g,1)*L/2;
    }

        mass << massel.rows(), massel.cols();
}

// Elemental RHS
void ElementMatrix::RHS(Eigen::Matrix<double,Eigen::Dynamic,1>& rhsel, Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>& Nmat_force,Eigen::MatrixXi &conc,Eigen::MatrixXd &nodx,Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> &zw, Eigen::MatrixXd &P, Eigen::MatrixXd &Pl, Eigen::MatrixXd &UDL, int _C, double &L,int &ielem,std::string &BasesFunc)
{
    // Compute UDLs
    // Allocate UDL (body force) vector
    Eigen::VectorXd b(11*(_C+2)), vb(11);
    b.setZero(11*(_C+2));
    // For all UDLs in different directions
    for (int i=0; i<UDL.rows(); i++)
    {
        // Determine if this element has a UDL
        if (ielem>=UDL(i,2)-1 && ielem<=(UDL(i,2)+UDL(i,3)-2))
        {
            // OK so it does, now compute on which DoFs UDL is applied
            vb.setZero(11,1);
            if (UDL(i,1)==1 || UDL(i,1)==5)     {vb(0)=UDL(i,0); vb(4)=UDL(i,0);}
            else if (UDL(i,1)==2 || UDL(i,1)==4)    {vb(1)=UDL(i,0); vb(3)=UDL(i,0);}
            else if (UDL(i,1)==3 || UDL(i,1)==6 || UDL(i,1)==9)     {throw std::invalid_argument("UDL cannot be applied in the cross sectional direction (3,6,9)");}
            else if (UDL(i,1)==7 || UDL(i,1)==10)      {vb(6)=UDL(i,0); vb(8)=UDL(i,0); vb(9)=UDL(i,0);}
            else if (UDL(i,1)==8 || UDL(i,1)==11)      {vb(7)=UDL(i,0); vb(8)=UDL(i,0); vb(10)=UDL(i,0);}

            // Compute body force vector
            for (int g=0; g<zw.rows(); g++)
                b +=(Nmat_force.block(11*g,0,11,Nmat_force.cols()).transpose()*vb).eval()*zw(g,1)*L/2;
        }
    }

    // Compute Point Loads
    // Allocate point load vector
    Eigen::VectorXd t(11*(_C+2));
    t.setZero(11*(_C+2));
    double dist,dist_elem,dist_next_elem,xi;
    int opt1;
    if (BasesFunc.compare("Lagrange")==0 || BasesFunc.compare("lagrange")==0) opt1 = 2;
    else opt1 = 1;
    Eigen::MatrixXd N;
    // For all point loads in different directions
    for (int i=0; i<P.rows(); i++)
    {
        // Check if the load's position is within this element
        dist = Pl.row(i).norm();
        dist_elem = nodx.row(conc(ielem,0)-1).norm();
        if (ielem==conc.rows()-1) dist_next_elem = (_C+1)*nodx.row(conc(ielem+1,0)-1).norm()+nodx.row(conc(ielem,0)-1).norm();
        else dist_next_elem = nodx.row(conc(ielem+1,0)-1).norm();
        // For all point loads except the ones applied at the end
        if (ielem<conc.rows() && dist>=dist_elem && dist<dist_next_elem)
        {
            // Ok so it is, now compute the point at which load is to be applied
            xi = (2.0*(Pl(i,0)-nodx(conc(ielem,0)-1,0))/L)-1.0;
            // Evaluate basis function at this point
            hpBasis1D *eval = new hpBasis1D(_C,xi,opt1,false);
            if (BasesFunc.compare("Legendre")==0 || BasesFunc.compare("legendre")==0)  N = eval->Legendre();
            else    N = eval->Lagrange();
            // Apply load based on direction
            if (P(i,1)==1)  { for (int j=0; j<N.rows(); ++j) t(11*j)=P(i,0)*N(j);}
            else if (P(i,1)==2)  { for (int j=0; j<N.rows(); ++j) t(11*j+1) +=P(i,0)*N(j);}
            else if (P(i,1)==3)  { for (int j=0; j<N.rows(); ++j) t(11*j+2) +=P(i,0)*N(j);}
            else if (P(i,1)==4)  { for (int j=0; j<N.rows(); ++j) t(11*j+3) +=P(i,0)*N(j);}
            else if (P(i,1)==5)  { for (int j=0; j<N.rows(); ++j) t(11*j+4) +=P(i,0)*N(j);}
            else if (P(i,1)==6)  { for (int j=0; j<N.rows(); ++j) t(11*j+5) +=P(i,0)*N(j);}
            else if (P(i,1)==7)  { for (int j=0; j<N.rows(); ++j) t(11*j+6) +=P(i,0)*N(j);}
            else if (P(i,1)==8)  { for (int j=0; j<N.rows(); ++j) t(11*j+7) +=P(i,0)*N(j);}
            else if (P(i,1)==0)  { for (int j=0; j<N.rows(); ++j) t(11*j+8) +=P(i,0)*N(j);}
            else if (P(i,1)==10)  { for (int j=0; j<N.rows(); ++j) t(11*j+9) +=P(i,0)*N(j);}
            else if (P(i,1)==11)  { for (int j=0; j<N.rows(); ++j) t(11*j+10) +=P(i,0)*N(j);}
        }
        // For point loads applied at the end node
        else if (ielem==conc.rows()-1 && dist<=dist_next_elem)
        {
            // Ok so it is, now compute the point at which load is to be applied
            xi = (2.0*(Pl(i,0)-nodx(conc(ielem,0)-1,0))/L)-1.0;
            // Evaluate basis function at this point
            hpBasis1D *eval = new hpBasis1D(_C,xi,opt1,false);
            if (BasesFunc.compare("Legendre")==0 || BasesFunc.compare("legendre")==0)  N = eval->Legendre();
            else    N = eval->Lagrange();
            // Apply load based on direction
            if (P(i,1)==1)  { for (int j=0; j<N.rows(); ++j) t(11*j)=P(i,0)*N(j);}
            else if (P(i,1)==2)  { for (int j=0; j<N.rows(); ++j) t(11*j+1) +=P(i,0)*N(j);}
            else if (P(i,1)==3)  { for (int j=0; j<N.rows(); ++j) t(11*j+2) +=P(i,0)*N(j);}
            else if (P(i,1)==4)  { for (int j=0; j<N.rows(); ++j) t(11*j+3) +=P(i,0)*N(j);}
            else if (P(i,1)==5)  { for (int j=0; j<N.rows(); ++j) t(11*j+4) +=P(i,0)*N(j);}
            else if (P(i,1)==6)  { for (int j=0; j<N.rows(); ++j) t(11*j+5) +=P(i,0)*N(j);}
            else if (P(i,1)==7)  { for (int j=0; j<N.rows(); ++j) t(11*j+6) +=P(i,0)*N(j);}
            else if (P(i,1)==8)  { for (int j=0; j<N.rows(); ++j) t(11*j+7) +=P(i,0)*N(j);}
            else if (P(i,1)==0)  { for (int j=0; j<N.rows(); ++j) t(11*j+8) +=P(i,0)*N(j);}
            else if (P(i,1)==10)  { for (int j=0; j<N.rows(); ++j) t(11*j+9) +=P(i,0)*N(j);}
            else if (P(i,1)==11)  { for (int j=0; j<N.rows(); ++j) t(11*j+10) +=P(i,0)*N(j);}
        }

    }

    rhsel = b+t;
}


} // end of namespace
