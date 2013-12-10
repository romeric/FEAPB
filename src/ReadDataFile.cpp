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

#include"ReadDataFile.h"

namespace FEAPB {

ReadData ReadDataFile()
{

//    std::ifstream id("C:\\Users\\Roman\\Documents\\C++\\Piezo_3D_Beam\\Problem1.txt");
//    std::ifstream id("C:\\Users\\Roman\\Documents\\C++\\Piezo_3D_Beam\\problem2.txt");
    std::ifstream id("C:\\Users\\Roman\\Documents\\C++\\Piezo_3D_Beam\\problem_check.txt");

    // Ask for the path to the data file
//    std::string path;
//    std::cout << "Specify the path to the data file:" << std::endl;
//    std::cin >> path;
//    std::ifstream id(path);

    if (id.is_open())
    {
    ReadData InputData;
    while (id.good())
    {

    // Allocate
    Eigen::Matrix<double,6,6> elast=Eigen::Matrix<double,6,6>::Zero();
    Eigen::Matrix<double,3,9> piezo=Eigen::Matrix<double,3,9>::Zero();
    Eigen::Matrix<double,3,3> dielec=Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,1,5> geom;
    Eigen::Vector2d isoelast=Eigen::Matrix<double,2,1>::Zero();
    double density=0;
    Eigen::Matrix<double,Eigen::Dynamic,2> P,dynP;
    Eigen::Matrix<double,Eigen::Dynamic,3> Pl, D_BC;
    Eigen::Matrix<double,Eigen::Dynamic,4> UDL;
    Eigen::Matrix<double,1,2> dynnode;

    int rowcountp=0;     int rowcounte=0;   int rowcountm=0;
    int nline=0;
    std::string line, bass, numint, mater, dynint;
    int analysis=0; int plane=0;
    while(std::getline(id,line,'\n'))
    {
        ++nline;  //line counter

        // Ignore blank lines in the begining of the file (if any)
        if(line.empty()) continue;

        // Trim white space from the beginning of the string
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
//        std::string bline = boost::trim_left_copy(line); // boost solution for trimming

        // If line starts with /, //, #, * and %, ignore it
        if(line[0] == '#' || line[0]=='/' || line[0]=='%' || line[0]=='*') continue;

        if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Lagrange"))
            bass = line;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"LagrangeES"))
            bass = line;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Legendre"))
            bass = line;

        if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Gauss"))
            numint = line;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"GaussLobatto"))
            numint = line;

        if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Isotropic"))
            mater = line;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Anisotropic"))
            mater = line;

        if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Newmark"))
            dynint = line;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Alpha"))
            dynint = line;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Gen Alpha")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"GenAlpha")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Gen_Alpha")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Generalised Alpha")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"GeneralisedAlpha")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Generalised_Alpha"))
            dynint = line;

        if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Static"))
            analysis= 1;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Modal")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"EigenValue")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Eigen Value")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Eigen_Value"))
            analysis = 2;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"Dynamic"))
            analysis = 3;


        if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"two dimension")||
                boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"twodimension")||
                boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"two_dimension"))
            plane = 2;
        else if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"three dimension")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"threedimension")||
                 boost::iequals(boost::trim_right_copy(boost::trim_left_copy(line)),"three_dimension"))
            plane = 3;


        if (line[0]=='p' || line[0]=='P')
        {
            // Split the string into two parts i.e. into RHS and LHS
            typedef std::vector<std::string> split_vector_type;
            split_vector_type splitvec,splitvec_rhs;
            boost::split(splitvec,line,boost::is_any_of(":")); // the splitter/delimiter here is :

            // Read Mechanical Point Loads
            if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(splitvec[0])),"p"))
            {
                // Split the resulting RHS into parts by ;
                if (boost::find_first(splitvec[1],";"))
                {
                    boost::split(splitvec_rhs,splitvec[1],boost::is_any_of(";"));
                    P = Eigen::MatrixXd::Zero(splitvec_rhs.size(),2);
                    for (unsigned j=0; j<splitvec_rhs.size(); j++)
                    {
                        std::vector<double> pinputs;
                        std::istringstream pline(splitvec_rhs[j]);
                        std::copy(std::istream_iterator<double>(pline),
                                  std::istream_iterator<double>(),
                                  std::back_inserter(pinputs));

                        for (unsigned int i=0; i<pinputs.size(); i++)
                            P(j,i)=pinputs[i];
                    }
                }
                else
                {
                    P = Eigen::MatrixXd::Zero(1,2);
                    std::vector<double> pinputs;
                    std::istringstream pline(splitvec[1]);
                    std::copy(std::istream_iterator<double>(pline),
                              std::istream_iterator<double>(),
                              std::back_inserter(pinputs));

                    for (unsigned int i=0; i<pinputs.size(); i++)
                        P(i)=pinputs[i];
                }
            }

            // Read Point Loads' Positions
            if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(splitvec[0])),"pl"))
            {
                // Split the resulting RHS into parts by ; or ,
                if (boost::find_first(splitvec[1],";"))
                {
                    boost::split(splitvec_rhs,splitvec[1],boost::is_any_of(";"));
                    Pl = Eigen::MatrixXd::Zero(splitvec_rhs.size(),3);
                    for (unsigned int j=0; j<splitvec_rhs.size(); j++)
                    {
                        std::vector<double> pinputs;
                        std::istringstream pline(splitvec_rhs[j]);
                        std::copy(std::istream_iterator<double>(pline),
                                  std::istream_iterator<double>(),
                                  std::back_inserter(pinputs));

                        for (unsigned int i=0; i<pinputs.size(); i++)
                            Pl(j,i)=pinputs[i];
                    }
                }
                else
                {
                    Pl = Eigen::MatrixXd::Zero(1,3);
                    std::vector<double> pinputs;
                    std::istringstream pline(splitvec[1]);
                    std::copy(std::istream_iterator<double>(pline),
                              std::istream_iterator<double>(),
                              std::back_inserter(pinputs));

                    for (unsigned int i=0; i<pinputs.size(); i++)
                        Pl(i)=pinputs[i];
                }
            }
        } //end of if (line[0]=='p')


        // Read Uniformly Distributed Loads
//        if (line[0]=='u' || line[0]=='U')
        if (line.find("udl")==0)
        {
            // Split the string into two parts i.e. into RHS and LHS
            typedef std::vector<std::string> split_vector_type;
            split_vector_type splitvec,splitvec_rhs;
            boost::split(splitvec,line,boost::is_any_of(":")); // the splitter/delimiter here is :

            // Read Mechanical UDL
            if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(splitvec[0])),"udl"))
            {
                // Split the resulting RHS into parts by ; or ,
                if (boost::find_first(splitvec[1],";"))
                {
                    boost::split(splitvec_rhs,splitvec[1],boost::is_any_of(";"));
                    UDL = Eigen::MatrixXd::Zero(splitvec_rhs.size(),4);
                    for (unsigned int j=0; j<splitvec_rhs.size(); j++)
                    {
                        std::vector<double> pinputs;
                        std::istringstream pline(splitvec_rhs[j]);
                        std::copy(std::istream_iterator<double>(pline),
                                  std::istream_iterator<double>(),
                                  std::back_inserter(pinputs));

                        for (unsigned int i=0; i<pinputs.size(); i++)
                            UDL(j,i)=pinputs[i];
                    }
                }
                else
                {
                    UDL = Eigen::MatrixXd::Zero(1,4);
                    std::vector<double> pinputs;
                    std::istringstream pline(splitvec[1]);
                    std::copy(std::istream_iterator<double>(pline),
                              std::istream_iterator<double>(),
                              std::back_inserter(pinputs));

                    for (unsigned int i=0; i<pinputs.size(); i++)
                        UDL(i)=pinputs[i];
                }
            }
        }


        // Read Dirichlet Boundary Conditions
        if (line.find("bc")==0)
        {
            // Split the string into two parts i.e. into RHS and LHS
            typedef std::vector<std::string> split_vector_type;
            split_vector_type splitvec,splitvec_rhs;
            boost::split(splitvec,line,boost::is_any_of(":")); // the splitter/delimiter here is :

            // Read Mechanical & Electrical BC
            if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(splitvec[0])),"bc"))
            {
                // Split the resulting RHS into parts by ; or ,
                if (boost::find_first(splitvec[1],";"))
                {
                    boost::split(splitvec_rhs,splitvec[1],boost::is_any_of(";"));
                    D_BC = Eigen::MatrixXd::Zero(splitvec_rhs.size(),3);
                    for (unsigned int j=0; j<splitvec_rhs.size(); j++)
                    {
                        std::vector<double> pinputs;
                        std::istringstream pline(splitvec_rhs[j]);
                        std::copy(std::istream_iterator<double>(pline),
                                  std::istream_iterator<double>(),
                                  std::back_inserter(pinputs));

                        for (unsigned int i=0; i<pinputs.size(); i++)
                            D_BC(j,i)=pinputs[i];
                    }
                }
                else
                {
                    D_BC = Eigen::MatrixXd::Zero(1,3);
                    std::vector<double> pinputs;
                    std::istringstream pline(splitvec[1]);
                    std::copy(std::istream_iterator<double>(pline),
                              std::istream_iterator<double>(),
                              std::back_inserter(pinputs));

                    for (unsigned int i=0; i<pinputs.size(); i++)
                        D_BC(i)=pinputs[i];
                }
            }
        }


        // Read Dirichlet Boundary Conditions
        if (line.find("dyn")==0)
        {
            // Split the string into two parts i.e. into RHS and LHS
            typedef std::vector<std::string> split_vector_type;
            split_vector_type splitvec,splitvec_rhs;
            boost::split(splitvec,line,boost::is_any_of(":")); // the splitter/delimiter here is :

            // Read dynamic load data
            if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(splitvec[0])),"dynp"))
            {
                // Split the resulting RHS into parts by ; or ,
                if (boost::find_first(splitvec[1],";"))
                {
                    boost::split(splitvec_rhs,splitvec[1],boost::is_any_of(";"));
                    dynP = Eigen::MatrixXd::Zero(splitvec_rhs.size(),2);
                    for (unsigned int j=0; j<splitvec_rhs.size(); j++)
                    {
                        std::vector<double> pinputs;
                        std::istringstream pline(splitvec_rhs[j]);
                        std::copy(std::istream_iterator<double>(pline),
                                  std::istream_iterator<double>(),
                                  std::back_inserter(pinputs));

                        for (unsigned int i=0; i<pinputs.size(); i++)
                            dynP(j,i)=pinputs[i];
                    }
                }
                else
                {
                    dynP = Eigen::MatrixXd::Zero(1,2);
                    std::vector<double> pinputs;
                    std::istringstream pline(splitvec[1]);
                    std::copy(std::istream_iterator<double>(pline),
                              std::istream_iterator<double>(),
                              std::back_inserter(pinputs));

                    for (unsigned int i=0; i<pinputs.size(); i++)
                        dynP(i)=pinputs[i];
                }
            }

            // Read dynamic node to be output
            if (boost::iequals(boost::trim_right_copy(boost::trim_left_copy(splitvec[0])),"dynnode"))
            {
                // Split the resulting RHS into parts by ; or ,
                dynnode = Eigen::MatrixXd::Zero(1,2);
                std::vector<double> pinputs;
                std::istringstream pline(splitvec[1]);
                std::copy(std::istream_iterator<double>(pline),
                          std::istream_iterator<double>(),
                          std::back_inserter(pinputs));

                for (unsigned int i=0; i<pinputs.size(); i++)
                    dynnode(i)=pinputs[i];
            }
        }


        // Note: automatically rules out strings and does not convert them. No need for checking
        std::vector<double> inputs;
        std::istringstream sline(line);
        std::copy( std::istream_iterator<double>(sline),
                   std::istream_iterator<double>(),
                   std::back_inserter(inputs));



        // Build Piezoelectric Matrix
        if (inputs.size()==9)
        {
            for (unsigned int i=0; i<inputs.size();i++)
            {
                piezo(rowcountp,i)=inputs[i];
            }
            rowcountp++;
        }

        // Build Dielectric Matrix
        if (inputs.size()==3)
        {
            for (unsigned int i=0; i<inputs.size();i++)
            {
                dielec(rowcounte,i)=inputs[i];
            }
            rowcounte++;
        }

        // Build Anistropic Elasticity Matrix
        if (inputs.size()==6)
        {
            for (unsigned int i=0; i<inputs.size();i++)
            {
                elast(rowcountm,i)=inputs[i];
            }
            rowcountm++;
        }

        // Build Vector containing isotropic elastic properties
        if (inputs.size()==2)
        {
            for (unsigned int i=0; i<inputs.size();i++)
            {
                isoelast(i)=inputs[i];
            }
        }

        // Density
        if (inputs.size()==1)
        {
            density=inputs[0];
        }

        // Geometrical Properties including C(order) and n(nelem)
        if (inputs.size()==5)
        {
            for (unsigned int i=0; i<inputs.size();i++)
            {
                geom(i)=inputs[i];
            }
        }

     }


    // Data Checking: Use default values if any property is not defined
    if (mater.empty())
        mater="Isotropic";
    if (numint.empty())
        numint="Gauss";
    if (bass.empty())
        bass="Lagrange";
    if (dynint.empty())
        dynint="Alpha";
    if (analysis==0)
        analysis=1;
    if (plane==0)
        plane=3;

    const double deps=1e-30;
    //const double deps=0;
    if (analysis!=1 && density==0)
        throw std::invalid_argument("Density not defined!");
    if (isoelast.isZero(deps) && elast.isZero(deps))
        throw std::invalid_argument("No elastic properties defined!");
    if (P.col(0).isZero(deps) && UDL.col(0).isZero(deps) && dynP.isZero(deps))
        std::cout << "Warning: No Load(s) defined!" << std::endl;
    if (P.rows()!=Pl.rows())
        throw std::invalid_argument("Incompatible mechanical point loads and load poistions!");

    for (int i=0; i<P.rows();i++)
    {
        if(P(i,1)>11 || P(i,1)<1)
        {
            throw std::invalid_argument("Invalid point load direction! direction=1,2,3,...,11");
        }
    }

    for (int i=0; i<dynP.rows();i++)
    {
        if(dynP(i,1)>11 || dynP(i,1)<1)
        {
            throw std::invalid_argument("Invalid dynamic load direction! direction=1,2,3,...,11");
        }
    }

    for (int i=0; i<UDL.rows();i++)
    {
        if(UDL(i,1)>11 || UDL(i,1)<1)
        {
            throw std::invalid_argument("Invalid direction for UDL! direction=1,2,3,...,11");
        }
        if(UDL(i,2)>geom(4) || UDL(i,2)<1)
        {
            throw std::invalid_argument("Invalid mechanical UDL!");
        }
    }

    // Check Boundary condition
    for (int i=0; i<D_BC.rows();i++)
    {
        if(D_BC(i,2)>11 || D_BC(i,2)<1)
        {
            throw std::invalid_argument("Invalid variable in Dirichlet boundary condition, variable must be 1-11, or check any typo");
        }
    }




    // Now store the data in a structure

    InputData.Base = bass;
    InputData.NInt = numint;
    InputData.AIso = mater;
    InputData.DInt = dynint;
    InputData.dim = plane;

    InputData.Analysis = analysis;
    InputData.C = (int)geom(3);
    InputData.n = (int)geom(4);
    InputData.x1 = geom(0);
    InputData.x2 = geom(1);
    InputData.x3 = geom(2);

    InputData.densi = density;
    InputData.Elast = elast;
    InputData.IsoElast = isoelast;
    InputData.Piezo = piezo;
    InputData.Die = dielec;

    InputData.pForce = P;
    InputData.pForcePos = Pl;
    InputData.udl_Force = UDL;
    InputData.Dirichlet_Boundary_Conditions = D_BC;
    InputData.dynForce = dynP;
    InputData.dynNode = dynnode;
    }
    return InputData;
    }
    else
    {
        throw std::invalid_argument("Could not open the file!");
        // Now store the data in a structure
        ReadData InputData;

    /** Default values (if needed)
     *
        InputData.Base = "Lagrange";
        InputData.NInt = "Gauss";
        InputData.AIso = "Isotropic";
        InputData.DInt = "Alpha";
        InputData.sc = 0;
        InputData.dim = 3;

        InputData.Analysis = 1;
        InputData.C = 0;
        InputData.n = 10;
        InputData.x1 = 10;
        InputData.x2 = 10;
        InputData.x3 = 1000;

        InputData.densi = 0;
        InputData.Elast = Eigen::Matrix<double,6,6>::Zero();
        InputData.IsoElast = Eigen::Matrix<double,2,1>::Zero();
        InputData.Piezo = Eigen::Matrix<double,3,9>::Zero();
        InputData.Die = Eigen::Matrix<double,3,3>::Zero();


        InputData.pForce = Eigen::Matrix<double,2,1>::Zero();
        InputData.pForcePos = Eigen::Matrix<double,3,1>::Zero();
        InputData.udl_Force = Eigen::Matrix<double,3,1>::Zero();
        InputData.dynForce = Eigen::Matrix<double,1,2>::Zero();
        InputData.dynNode = dynnode;    */

        return InputData;
    }
}


void CheckPrintDataFile(ReadData *InputData)
{
//    std::streamsize prc = std::cout.precision();
    int wid = 30;
    std::cout << std::endl;
    std::cout << "Verifying your input..." << std::endl << std::endl;
    if (InputData->Analysis==1)
    {
        std::cout << "Analysis Type:" << std::setw(wid-3) << "Static" << std::endl;
    }
    else if (InputData->Analysis==2)
    {
        std::cout << "Analysis Type:" << std::setw(wid-4) << "Modal" << std::endl;
    }
    else if (InputData->Analysis==3)
    {
        std::cout << "Analysis Type:" << std::setw(wid-2) << "Dynamic" << std::endl;
        int dumdint = (boost::trim_right_copy(boost::trim_left_copy(InputData->DInt))).size();
        std::cout << "Dynamic Integrator:" << std::setw(wid-14+dumdint)
                  << boost::trim_copy(InputData->DInt) << std::endl;
    }

    int dumc = (int)(std::log10(InputData->C)+1); int dumn = (int)(std::log10(InputData->n)+1);
    if (InputData->C>0)
        std::cout << "Order of Interpolation:" << std::setw(wid-18+dumc) << InputData->C << std::endl;
    else
        std::cout << "Order of Interpolation:" << std::setw(wid-17) << InputData->C << std::endl;
    std::cout << "Number of Elements:" << std::setw(wid-14+dumn) << InputData->n << std::endl;

    int dumb = (boost::trim_right_copy(boost::trim_left_copy(InputData->Base))).size();
    std::cout << "Basis Functions:" << std::setw(wid-11+dumb) << boost::trim_copy(InputData->Base) << std::endl;
    int dumnint = (boost::trim_right_copy(boost::trim_left_copy(InputData->NInt))).size();
    std::cout << "Numerical Integration:" << std::setw(wid-17+dumnint)
              <<boost::trim_copy(InputData->NInt) << std::endl;

    if (InputData->dim==3)
    {
        std::cout << "Dimension:" << std::setw(wid-3) << "3D" << std::endl;
    }
    else
    {
        std::cout << "Dimension:" << std::setw(wid-3) << "3D" << std::endl;
    }

    std::cout << "Geometric properties:" << std::endl;
    int dum1 = (int)(std::log10(InputData->x1)+1);
    int dum2 = (int)(std::log10(InputData->x2)+1);
    int dum3 = (int)(std::log10(InputData->x3)+1);
    std::cout << "Height:" << std::setw(wid+5+dum1) << std::fixed << InputData->x1 << std::endl;
    std::cout << "Width:" << std::setw(wid+6+dum2) << std::fixed << InputData->x2 << std::endl;
    std::cout << "Length:" << std::setw(wid+5+dum3) << std::fixed << InputData->x3 << std::endl;

    std::cout << "Material properties:" << std::endl;
    if (boost::iequals(boost::trim_copy(InputData->AIso),"Anisotropic"))
    {
        std::cout << "Elasticity Tensor:" << std::setw(wid-13) << std::fixed
                  << InputData->Elast.row(0) << std::endl;
        for (int i=1; i<InputData->Elast.rows(); i++)
        {
            std::cout << std::setw(wid+5) << std::fixed << InputData->Elast.row(i) << std::endl;
        }

    }
    else
    {
        std::cout << "Elastic Properties:" << std::setw(wid-2) << InputData->IsoElast(0)
                  << "\t" << InputData->IsoElast(1) << std::endl;
    }

    if (InputData->Analysis!=1)
    {
        int dumden = (int)(std::log10(InputData->densi)+1);
        std::cout << std::endl;
        std::cout << "Density:" << std::setw(wid+9+dumden) << std::fixed << InputData->densi << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Piezoelectric Tensor:" << std::setw(wid-16) << std::fixed
              << InputData->Piezo.row(0) << std::endl;
    for (int i=1; i<InputData->Piezo.rows(); i++)
    {
        std::cout << std::setw(wid+5) << std::fixed << InputData->Piezo.row(i) << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Dielectric Tensor:" << std::setw(wid-13) << std::fixed
              << InputData->Die.row(0) << std::endl;
    for (int i=1; i<InputData->Die.rows(); i++)
    {
        std::cout << std::setw(wid+5) << std::fixed << InputData->Die.row(i) << std::endl;
    }

    std::cout << "Loads:" << std::endl;
    std::cout << "Point Load(s):" << std::setw(wid-9) << std::fixed
              << InputData->pForce.row(0) << std::endl;
    for (int i=1; i<InputData->pForce.rows(); i++)
    {
        std::cout << std::setw(wid+5) << std::fixed << InputData->pForce.row(i) << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Point Load(s)' Position(s):" << std::setw(wid-22) << std::fixed
              << InputData->pForcePos.row(0) << std::endl;
    for (int i=1; i<InputData->pForcePos.rows(); i++)
    {
        std::cout << std::setw(wid+5) << std::fixed << InputData->pForcePos.row(i) << std::endl;
    }


    if (InputData->udl_Force.rows()!=0)
    {
        std::cout << std::endl;
        std::cout << "Uniformly Distributed Load(s):" << std::setw(wid-25) << std::fixed
                  << InputData->udl_Force.row(0) << std::endl;
        for (int i=1; i<InputData->udl_Force.rows(); i++)
        {
            std::cout << std::setw(wid+5) << std::fixed << InputData->udl_Force.row(i) << std::endl;
        }
    }

    if (InputData->Dirichlet_Boundary_Conditions.rows()!=0)
    {
        std::cout << std::endl;
        std::cout << "Dirichlet Boundary Condition(s):" << std::setw(wid-27) << std::fixed
                  << InputData->Dirichlet_Boundary_Conditions.row(0) << std::endl;
        for (int i=1; i<InputData->Dirichlet_Boundary_Conditions.rows(); i++)
        {
            std::cout << std::setw(wid+5) << std::fixed << InputData->Dirichlet_Boundary_Conditions.row(i) << std::endl;
        }
    }
    else
    {
        throw std::invalid_argument("Dirichlet boundary conditions not defined");
    }

    if (InputData->Analysis==3)
    {
        if (InputData->dynForce.rows()!=0)
        {
            std::cout << std::endl;
            std::cout << "Dynamic Load Data:" << std::setw(wid-13) << std::fixed
                      << InputData->dynForce.row(0) << std::endl;
            for (int i=1; i<InputData->dynForce.rows(); i++)
            {
                std::cout << std::setw(wid+5) << std::fixed << InputData->dynForce.row(i) << std::endl;
            }
        }
        else
        {
            std::cout << std::endl;
            std::cout << "Dynamic load-data not defined" << std::endl;
        }

        std::cout << std::endl;
        std::cout << "Dynamic Output Node/DoF's:" << std::setw(wid-21) << InputData->dynNode << std::endl;
    }
    std::cout << std::endl << std::endl;


    // Ask the user for verification
    std::cout << "Are the input data correct?(y/n):\t";
    std::string verify;
    std::cin >> verify;
    if (boost::iequals(boost::trim_copy(verify),"Y")||boost::iequals(boost::trim_copy(verify),"Yes")
            ||boost::iequals(boost::trim_copy(verify),"Yeap")||boost::iequals(boost::trim_copy(verify),"Yep"))
    {
        std::cout << std::endl << std::endl;
        std::cout << "Simulation starts..." << std::endl;
    }
    else
        throw std::invalid_argument("Program restarts. Correct the input data!");
}




// Element Connectivity and Nodal Coordinates Function (tuple type)

std::tuple<Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic>,
Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>,double> ConcNodx(int &C,int &n,double &Length)
{
    // Element Size
    double h= Length/n;

    // Element Connectivity
    Eigen::MatrixXi conc = Eigen::Matrix<int,Eigen::Dynamic,Eigen::Dynamic>::Zero(n,C+2);
    int r=-1;
    for (int i=0; i<n; i++)
    {
        conc.row(i)=Eigen::RowVectorXi::LinSpaced(Eigen::Sequential,((r+2)*(C+2)-(r+1))-((r+1)*(C+2)-r)+1,(r+1)*(C+2)-r,(r+2)*(C+2)-(r+1));
        r+=1;
    }

    // Nodal Coordinates
    Eigen::MatrixXd nodx = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>::Zero(conc(n-1,C+1),3);
    nodx.col(0)=Eigen::VectorXd::LinSpaced(Eigen::Sequential,conc(n-1,C+1),0,Length);
    return std::make_tuple(conc,nodx,h);
}


}  // end of namespace
