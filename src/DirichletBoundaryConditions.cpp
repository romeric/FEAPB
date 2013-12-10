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

#include"DirichletBoundaryConditions.h"

namespace FEAPB {


void DirichletBoundaryConditions(Eigen::SparseMatrix<double,Eigen::ColMajor>& stiffg,Eigen::VectorXd& F,Eigen::Matrix<double,Eigen::Dynamic,3>& Dirichlet_Boundary_Conditions){

    for (int i=0; i<Dirichlet_Boundary_Conditions.rows(); i++)
    {
        // Get the index for the column to be transfered to to RHS
        int col = 11*(Dirichlet_Boundary_Conditions(i,1)-1)+Dirichlet_Boundary_Conditions(i,2)-1;
        // Apply non-zero Dirichlet boundary conditions
        if (Dirichlet_Boundary_Conditions(i,0)!=0)
        {
            F -= Dirichlet_Boundary_Conditions(i,0)*stiffg.col(col);
        }
    }
}


void DirichletBoundaryConditions(Eigen::Matrix<double,Eigen::Dynamic,3>& Dirichlet_Boundary_Conditions, Eigen::MatrixXi &conc,Eigen::MatrixXd &Dirichlet_data){

    // First sort Dirichlet boundary conditions
    std::vector<double> D_BC_stl_amount,D_BC_stl_node, D_BC_stl_var;
    for (int i=0; i<Dirichlet_Boundary_Conditions.rows(); i++)
    {
        D_BC_stl_amount.push_back(Dirichlet_Boundary_Conditions(i,0));
        D_BC_stl_node.push_back(Dirichlet_Boundary_Conditions(i,1));
        D_BC_stl_var.push_back(Dirichlet_Boundary_Conditions(i,2));
    }

    std::vector<unsigned int> sorted; sorted = ordered(D_BC_stl_node);
    Eigen::Matrix<double,Eigen::Dynamic,3> D_BC_sorted(Dirichlet_Boundary_Conditions.rows(),Dirichlet_Boundary_Conditions.cols());

    // Sort nodes
    for (unsigned int m=0; m<sorted.size(); m++)
    {
        D_BC_sorted(m,0) = Dirichlet_Boundary_Conditions(sorted[m],0);
        D_BC_sorted(m,1) = Dirichlet_Boundary_Conditions(sorted[m],1);
        D_BC_sorted(m,2) = Dirichlet_Boundary_Conditions(sorted[m],2);
    }

    // Now sort variables
    std::vector<double> var_sort_stl;
    std::vector<int> nodes_stl;
    var_sort_stl.push_back(0); nodes_stl.push_back(D_BC_sorted(0,1));
    for (int m=1; m<D_BC_sorted.rows(); m++)
    {
        if (D_BC_sorted(m,1)!=D_BC_sorted(m-1,1))
        {
            var_sort_stl.push_back(m-1);
            nodes_stl.push_back(D_BC_sorted(m,1));
        }
    }
    var_sort_stl.push_back(D_BC_sorted.rows()-1);


    // Build final sorted Dirichlet boundary condition matrix
    Eigen::MatrixXd D_BC_sorted_final(D_BC_sorted.rows(),D_BC_sorted.cols());

    unsigned int rem=0, rem2=0;
    for (unsigned int j=0; j<var_sort_stl.size();j++)
    {
        std::vector<unsigned int > v_temp;
        for (unsigned int m=var_sort_stl[j]+rem; m<=var_sort_stl[j+1]; m++)
            v_temp.push_back(D_BC_sorted(m,2));

       std::vector<unsigned int> sorted_var;
       sorted_var = ordered(v_temp);
       for (unsigned int m=0; m<sorted_var.size(); m++)
       {
           D_BC_sorted_final(m+rem2,2) = D_BC_sorted(sorted_var[m]+rem2,2);
           D_BC_sorted_final(m+rem2,1) = D_BC_sorted(sorted_var[m]+rem2,1);
           D_BC_sorted_final(m+rem2,0) = D_BC_sorted(sorted_var[m]+rem2,0);
       }
       rem=1;
       rem2 +=v_temp.size();
    }
    Eigen::Map<Eigen::VectorXi> nodes(nodes_stl.data(),nodes_stl.size());

    std::vector<int> BC_nodes_stl, BC_elements_stl,BC_info_stl;
    for (int inode=0; inode<nodes.size(); inode++)
    {
        for (int i=0; i<conc.rows(); i++)
        {
            typedef Eigen::Matrix<bool,1,Eigen::Dynamic> Matb;
            Matb vv_temp(1,conc.cols());
            vv_temp =(conc.row(i).array()==nodes(inode)).matrix();
            for (int j=0; j<vv_temp.cols(); j++)
            {
                if (vv_temp(j)==1)
                {
                    BC_nodes_stl.push_back(conc(i,j));
                    BC_elements_stl.push_back(i);
                    if (i==0 && j==0)
                        BC_info_stl.push_back(1);
                    else if (i==conc.rows()-1 && j==conc.cols()-1)
                        BC_info_stl.push_back(1);
                    else if (j!=0 && j!=conc.cols()-1)
                        BC_info_stl.push_back(1);
                    else
                        BC_info_stl.push_back(0);
                }
            }
        }
    }

    Eigen::MatrixXi BC_nodes_elements(BC_nodes_stl.size(),3);
    Eigen::Map<Eigen::VectorXi> BC_nodes(BC_nodes_stl.data(),BC_nodes_stl.size());
    Eigen::Map<Eigen::VectorXi> BC_elements(BC_elements_stl.data(),BC_elements_stl.size());
    Eigen::Map<Eigen::VectorXi> BC_info(BC_info_stl.data(),BC_info_stl.size());
    BC_nodes_elements.col(0)=BC_elements; BC_nodes_elements.col(1)=BC_nodes; BC_nodes_elements.col(2)=BC_info;

    std::vector<double> elem,node,var,amnt,info;
    for (int k=0; k<BC_nodes_elements.rows(); k++)
    {
        for (int m=0; m<D_BC_sorted_final.rows();m++)
        {
            if (BC_nodes_elements(k,1)==D_BC_sorted_final(m,1))
            {
                elem.push_back(BC_nodes_elements(k,0));
                node.push_back(BC_nodes_elements(k,1));
                amnt.push_back(D_BC_sorted_final(m,0));
                var.push_back(D_BC_sorted_final(m,2));
                info.push_back(BC_nodes_elements(k,2));
            }
        }
    }

    Eigen::Map<Eigen::VectorXd> elem1(elem.data(),elem.size());
    Eigen::Map<Eigen::VectorXd> node1(node.data(),node.size());
    Eigen::Map<Eigen::VectorXd> var1(var.data(),var.size());
    Eigen::Map<Eigen::VectorXd> amnt1(amnt.data(),amnt.size());
    Eigen::Map<Eigen::VectorXd> info1(info.data(),info.size());

    // Fill Dirichlet data
    Dirichlet_data.setZero(elem.size(),5);
    Dirichlet_data.col(0) = elem1;
    Dirichlet_data.col(1) = node1;
    Dirichlet_data.col(2) = var1;
    Dirichlet_data.col(3) = amnt1;
    Dirichlet_data.col(4) = info1;
}


} // end of namespace
