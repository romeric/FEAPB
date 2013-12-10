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

#include"Assembly.h"
#include"BasisFunctions.h"
#include"PiezoAreaMoments.h"
#include"ElementMatrix.h"
#include"find.h"


namespace FEAPB {

void Assembly(FEAPB::ReadData &InputData, Eigen::MatrixXi &conc,Eigen::MatrixXd &nodx,double &h, int &C, int &n, Eigen::SparseMatrix<double> &stiffg,Eigen::SparseMatrix<double> &massg,Eigen::VectorXd &F,Eigen::MatrixXd &Dirichlet_data){

    std::string BasesFunc = boost::trim_copy(InputData.Base);
    std::string IntScheme = boost::trim_copy(InputData.NInt);

    Eigen::MatrixXd zw;
    Eigen::MatrixXd zwbases;
    Eigen::MatrixXd zwgbases;
    if (boost::iequals(IntScheme,"GaussLobatto")|| boost::iequals(IntScheme,"Gauss Lobatto"))
    {
       zw=Eigen::MatrixXd::Zero(C+3,2);
       zwbases= Eigen::MatrixXd::Zero(C+2,C+3);
       zwgbases= Eigen::MatrixXd::Zero(C+2,C+3);
    }
    else
    {
       zw=Eigen::MatrixXd::Zero(C+2,2);
       zwbases= Eigen::MatrixXd::Zero(C+2,C+2);
       zwgbases= Eigen::MatrixXd::Zero(C+2,C+2);
    }
    // Compute basis functions at all integration points
    typedef FEAPB::BasisFunctions<std::string,int,std::string> BS;
    BS hp(BasesFunc,C,IntScheme);
    hp.BasesPointsWeights(zwbases,zwgbases,zw);

    Eigen::Matrix<double,15,15> H;
    Eigen::Matrix<double,6,6> HD;

    FEAPB::PiezoAreaMomentsTensors(InputData.IsoElast,InputData.densi,InputData.Elast,InputData.Piezo,
                                   InputData.Die,InputData.shfac,InputData.x1,InputData.x2,InputData.NInt,InputData.AIso,
                                              InputData.Analysis,H,HD);

    // Compute submatrices (matrices for basis functions and their gradients)
    FEAPB::ElementMatrix element;
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(15*zwbases.cols(),11*(C+2));
    Eigen::MatrixXd Nmat = Eigen::MatrixXd::Zero(6*zwbases.cols(),11*(C+2));
    Eigen::MatrixXd Nmat_force = Eigen::MatrixXd::Zero(11*zwbases.cols(),11*(C+2));
    std::tie(B,Nmat,Nmat_force)=element.Submatrices(zwbases,zwgbases,h,C);

    // Allocate for local stiffness & mass matrices
    Eigen::MatrixXd stiffel = Eigen::MatrixXd::Zero(11*(C+2),11*(C+2));
    Eigen::MatrixXd massel = Eigen::MatrixXd::Zero(11*(C+2),11*(C+2));
    Eigen::Matrix<double,Eigen::Dynamic,1> rhsel = Eigen::MatrixXd::Zero(11*(C+2),1);

    // Allocate for local triplets
    Eigen::VectorXi Ik, Jk; Eigen::VectorXd Vk;
    Eigen::VectorXi Im, Jm; Eigen::VectorXd Vm;

    // Pre-allocate
    typedef Eigen::Triplet<double> T;
    std::vector<T> tripletList_k, tripletList_m;

//    Allocation not necessary, throws bad_alloc for small size matrices
//    tripletList_k.reserve(121*nodx.rows()*nodx.rows());

//    if (InputData.Analysis!=1)
//    {
//        tripletList_m.reserve(121*nodx.rows()*nodx.rows());
//    }


    // Generate Local matrices to avoid computing stiffness and mass matrices within each loop
    Eigen::MatrixXd stiffel_temp = stiffel;
    Eigen::MatrixXd massel_temp = massel;
    // Also for local triplets
    Eigen::VectorXi Ik_temp, Jk_temp; Eigen::VectorXd Vk_temp;
    Eigen::VectorXi Im_temp, Jm_temp; Eigen::VectorXd Vm_temp;

    int rem=0;
    // Loop over elements
    for (int ielem=0; ielem<n; ielem++)
    {
        // Compute stiffness and mass matrices only once
        if (ielem==0)
        {
            // Compute stiffness matrix
            element.Stiffness(stiffel,B,zw,H,h);
            // Fill triplets
            std::tie(Ik_temp,Jk_temp,Vk_temp)=find(stiffel);
            // Compute mass matrix for modal/dynamic analysis
            if (InputData.Analysis!=1)
            {
                element.Mass(massel,Nmat,zw,HD,h);
                std::tie(Im_temp,Jm_temp,Vm_temp)=find(massel);
            }
        }

        // REMOVE THE BIT BETWEEN /** */ IF THIS METHOD IS NOT DESIRABLE
        /** */
        // Assign Local matrices to avoid computing stiffness and mass matrices within each loop
        stiffel_temp = stiffel;
        if (InputData.Analysis!=1)
            massel_temp = massel;
        // Apply Dirichlet boundary condition
        bool help = false;
        for (int k=rem; k<Dirichlet_data.rows(); k++)
        {
            int row_col=0;
            if (ielem==Dirichlet_data(k,0))
            {
                // Get node and DoF number from Dirichlet data
                int node = Dirichlet_data(k,1);
                int dof = Dirichlet_data(k,2);
                // Get local node number
                int node_ielem=0;
                for (int j=0; j<conc.cols(); j++)
                {
                    if (node==conc(ielem,j))
                        node_ielem = j;
                }
                // Now row and column to be set zero are
                row_col = 11*node_ielem+(dof-1);
                // within stiffness matrix
                stiffel_temp.col(row_col).setZero();
                stiffel_temp.row(row_col).setZero();
                if (Dirichlet_data(k,4)==1)
                    stiffel_temp(row_col,row_col)=Dirichlet_data(k,4);
                else
                    stiffel_temp(row_col,row_col)=0.5;
                // within mass matrix
                if (InputData.Analysis!=1)
                {
                    massel_temp.col(row_col).setZero();
                    massel_temp.row(row_col).setZero();
                    if (Dirichlet_data(k,4)==1)
                        massel_temp(row_col,row_col)=Dirichlet_data(k,4);
                    else
                        massel_temp(row_col,row_col)=0.5;
                }

                help = true;
                rem=k+1;
            }
            else
            {
                break;
            }
        }
        /** */

        // Get elemental triplets
        if (help)
        {
            std::tie(Ik,Jk,Vk)=find(stiffel_temp);
            std::tie(Im,Jm,Vm)=find(massel_temp);
        }
        else if (!help)
        {
            Ik = Ik_temp; Jk = Jk_temp; Vk = Vk_temp;
            Im = Im_temp; Jm = Jm_temp; Vm = Vm_temp;
        }

        // Fill triplets for stiffness
        for (int j=0; j<Ik.rows(); j++)
        {
            tripletList_k.push_back(T(Ik(j)+11*(C+1)*ielem,Jk(j)+11*(C+1)*ielem,Vk(j)));
        }

        // Fill triplets for mass
        if (InputData.Analysis!=1)
        {
            for (int j=0; j<Im.rows(); j++)
                tripletList_m.push_back(T(Im(j)+11*(C+1)*ielem,Jm(j)+11*(C+1)*ielem,Vm(j)));
        }


        // RHS Assembly
        element.RHS(rhsel,Nmat_force,conc,nodx,zw,InputData.pForce,InputData.pForcePos,InputData.udl_Force,C,h,ielem,BasesFunc);
        F.segment(ielem*(11*(C+1)),rhsel.rows()) +=rhsel;
    }


    // Build stiffness matrix from triplets
    stiffg.setFromTriplets(tripletList_k.begin(),tripletList_k.end());
    if (InputData.Analysis!=1)
        massg.setFromTriplets(tripletList_m.begin(),tripletList_m.end());
}

} // end of namespace
