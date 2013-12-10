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

#include"DefineProblem.h"
#include"TimeIntegration.h"

namespace FEAPB {

DefineProblem::DefineProblem(ReadData &InputData)
{
    // Build element connectivity and nodal coordinates
    double Length = InputData.x3; int n = InputData.n; int C = InputData.C;
    Eigen::MatrixXi conc; Eigen::MatrixXd nodx; double h;
    std::tie(conc,nodx,h)=FEAPB::ConcNodx(C,n,Length);

    // pre-allocate for sparse global matrices
    stiffg.resize(11*nodx.rows(),11*nodx.rows());
    massg.resize(11*nodx.rows(),11*nodx.rows());
    F.setZero(11*nodx.rows());

    // Determine Dirichlet boundary conditions
    Eigen::MatrixXd Dirichlet_data;
    // Dirichlet boundary conditions are applied on LHS during the assembly
    FEAPB::DirichletBoundaryConditions(InputData.Dirichlet_Boundary_Conditions,conc,Dirichlet_data);

    // Assembly
    FEAPB::Assembly(InputData,conc,nodx,h,C,n,stiffg,massg,F,Dirichlet_data);

    // Dirichlet boundary conditions are applied on RHS after the assembly
    FEAPB::DirichletBoundaryConditions(stiffg,F,InputData.Dirichlet_Boundary_Conditions);

    // Determine analysis type
    _analysis = InputData.Analysis;
    sol.setZero(11*nodx.rows(),1);

    // Get DoF's where dynamic load is applied
    if (_analysis==3)
    {
        _napp.setZero(InputData.dynForce.rows());
        for (int i=0; i<InputData.dynForce.rows(); ++i)
            _napp(i) = (InputData.dynForce(i,0)-1)*6+InputData.dynForce(i,1)-1;

        _nwant = (InputData.dynNode(0,0)-1)*6+InputData.dynNode(0,1)-1;

        // calculate mass
        mass = InputData.densi*(InputData.x1*InputData.x2*InputData.x3);

        // Determine time integrator type
        time_int = InputData.DInt;

        // Get dynamic data file ID
        dynamicDataFileID = InputData.DynFile;
    }

    // For GUI output
    InputData.nrows = stiffg.rows(); InputData.ncols = stiffg.cols(); InputData.nnz = stiffg.nonZeros();
}

Eigen::MatrixXd DefineProblem::Solve()
{
    // Solve
    if (_analysis==1)
    {
        // Scale global matrices
        Eigen::IterScaling<Eigen::SparseMatrix<double,Eigen::ColMajor>> scale;
        // Compute the left and right scaling vectors. The matrix is equilibrated at output
        scale.computeRef(stiffg);
        // Scale the right hand side
        F = scale.LeftScaling().cwiseProduct(F);

        // Solve
        Eigen::SparseLU<Eigen::SparseMatrix<double, Eigen::ColMajor>> solver;
        // Compute the ordering permutation vector from the structural pattern of A
        solver.analyzePattern(stiffg);
        // Compute the numerical factorization
        solver.factorize(stiffg);
        // Use the factors to solve the linear system
        sol = solver.solve(F);

        // Scale back the computed solution
        sol = scale.RightScaling().cwiseProduct(sol);
    }

    else if (_analysis!=1)
    {
        std::vector<int> mech_dofs, elec_dofs;
        for (int i=0; 11*i<stiffg.rows(); ++i)
        {
            mech_dofs.push_back(11*i);
            mech_dofs.push_back(1+11*i);
            mech_dofs.push_back(2+11*i);
            mech_dofs.push_back(3+11*i);
            mech_dofs.push_back(4+11*i);
            mech_dofs.push_back(5+11*i);

            elec_dofs.push_back(6+11*i);
            elec_dofs.push_back(7+11*i);
            elec_dofs.push_back(8+11*i);
            elec_dofs.push_back(9+11*i);
            elec_dofs.push_back(10+11*i);
        }

        // Convert sparse matrices to dense (this is an expensive copy, but cannot be avoided!)
        Eigen::MatrixXd stiffg_dense =Eigen::MatrixXd(stiffg);
        Eigen::MatrixXd massg_dense =Eigen::MatrixXd(massg);

        // Make eight additional matrices
        Eigen::MatrixXd Kaa(mech_dofs.size(),mech_dofs.size()), Kab(mech_dofs.size(),elec_dofs.size()), Kba(elec_dofs.size(),mech_dofs.size()), Kbb(elec_dofs.size(),elec_dofs.size());
        Eigen::MatrixXd Maa(mech_dofs.size(),mech_dofs.size());

        for (unsigned int i=0; i<mech_dofs.size(); ++i)
            for (unsigned int j=0; j<mech_dofs.size(); ++j)
            {
                Kaa(i,j) = stiffg_dense(mech_dofs[i],mech_dofs[j]);
                Maa(i,j) = massg_dense(mech_dofs[i],mech_dofs[j]);
            }

        for (unsigned int i=0; i<mech_dofs.size(); ++i)
            for (unsigned int j=0; j<elec_dofs.size(); ++j)
            {
                Kab(i,j) = stiffg_dense(mech_dofs[i],elec_dofs[j]);
            }

        for (unsigned int i=0; i<elec_dofs.size(); ++i)
            for (unsigned int j=0; j<mech_dofs.size(); ++j)
            {
                Kba(i,j) = stiffg_dense(elec_dofs[i],mech_dofs[j]);
            }

        for (unsigned int i=0; i<elec_dofs.size(); ++i)
            for (unsigned int j=0; j<elec_dofs.size(); ++j)
            {
                Kbb(i,j) = stiffg_dense(elec_dofs[i],elec_dofs[j]);
            }

        // Compute equivalent matrix
        Eigen::MatrixXd Keq = Kaa-Kab*(Kbb.fullPivLu().solve(Kba));


        // Modal Analysis
        if (_analysis==2)
        {
            // Instantiate generalised eigenvalue solver
            Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXd> ges;
            sol.setZero(Kaa.rows(),Kaa.cols()+1);
            // Compute eigenvalues and eigenvectors
            ges.compute(Keq,Maa,true);
            // Get real part of eigenvalues (take square root)
            for (int i=0; i<Kaa.rows(); ++i)
                sol(i,0) = ges.eigenvalues().array().sqrt().real()[i];
            // Get real part of eigenvectors
            sol.block(0,1,Kaa.rows(),Kaa.cols()) = ges.eigenvectors().real();
        }

        // Dynamic Analysis
        else if (_analysis==3)
        {
            // Instantiate dyanmic solver
            std::ifstream dyn_id(dynamicDataFileID);
            TimeIntegrator *dynamic_solver = new TimeIntegrator(_napp,dyn_id,mass);

            if (time_int.compare("Newmark")==0 || time_int.compare("newmark")==0 || time_int.compare("Newmark's")==0)
            {
                double del = 0.6; double gam = 0.3*(0.5+del)*(0.5+del);
                sol = dynamic_solver->Newmark(Keq,Maa,del,gam);
            }
            else if (time_int.compare("Alpha")==0 || time_int.compare("alpha")==0)
            {
                double alpha = -0.1;  // -0.33 << alpha << 0
                double del = 0.5-alpha, gam = 0.3*(1-alpha)*(1-alpha);
                sol = dynamic_solver->Alpha(Keq,Maa,del,gam,alpha);
            }
            else
            {
                double sr = 0.8;
                double alphaf = sr/(sr+1), alpham = (2*sr-1)/(sr+1); // if alpham=0, Alpha method and if alpham=alphaf=0, Newmark
                double del = 0.5+ (alphaf-alpham), gam = 0.25+0.5*(alphaf-alpham);
                sol = dynamic_solver->GeneralisedAlpha(Keq,Maa,del,gam,alphaf,alpham);                
            }
        }

    }
    return sol;
}



// Write solution to a data file
void DefineProblem::Write()
{
    // Ask the user for verification
    std::cout << "Do you want to write the solution to a data file?(y/n):\t";
    std::string verify;
    std::cin >> verify;
    if (boost::iequals(boost::trim_copy(verify),"Y")||boost::iequals(boost::trim_copy(verify),"Yes")
            ||boost::iequals(boost::trim_copy(verify),"Yeap")||boost::iequals(boost::trim_copy(verify),"Yep"))
    {
        if (_analysis!=3)
        {
            std::ofstream oID;
            if (_analysis==1)
                oID.open("FEAPB_static_solution.txt");
            else
                oID.open("FEAPB_modal_solution.txt");
            for (int i=0; i<sol.rows(); ++i)
            {
                oID << sol(i);
                oID << "\n";
            }
            oID.close();
        }
        else if (_analysis==3)
        {
            std::ofstream oID;
            oID.open("FEAPB_dynamic_solution.txt");
            for (int i=0; i<sol.cols(); ++i)
            {
                oID << sol(_nwant,i);
                oID << "\n";
            }
            oID.close();
        }
    }
}

} // end of namespace



