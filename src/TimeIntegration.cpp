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

#include "TimeIntegration.h"

namespace FEAPB {

TimeIntegrator::TimeIntegrator(Eigen::VectorXd &napp)
{
    _napp = napp;
    // Determine nstep, dt, F
    _nstep = 10;
    _dt = 1.0/_nstep;
    Eigen::VectorXd x; x.setLinSpaced(_nstep,0.0,60.0);
    F1=200*x.array().sin();
}

TimeIntegrator::TimeIntegrator(Eigen::VectorXd &napp, std::ifstream &dyn_id, double &mass)
{
    _napp = napp;

    std::string line;
    if (dyn_id.is_open())
    {
        std::vector<double> F_std, T_std;
        while (dyn_id.good())
        {
            while(std::getline(dyn_id,line,'\n'))
            {
                // Ignore blank lines in the begining of the file (if any)
                if(line.empty()) continue;
                // Trim white space from the beginning of the string
                line.erase(line.begin(), std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(isspace))));
                // If line starts with /, //, #, * and %, ignore it
                if(line[0] == '#' || line[0]=='/' || line[0]=='%' || line[0]=='*') continue;

                // Read data
                // Note: automatically rules out strings and does not convert them. No need for checking
                std::vector<double> inputs;
                std::istringstream sline(line);
                std::copy( std::istream_iterator<double>(sline),std::istream_iterator<double>(),std::back_inserter(inputs));

                // Build Piezoelectric Matrix
                if (inputs.size()==2)
                {
                    T_std.push_back(inputs[0]);
                    F_std.push_back(inputs[1]);
                }
            }
        }
        // Determine nstep, dt, F1
        // Map F1 using temp
        Eigen::Map<Eigen::VectorXd> Acc_temp(F_std.data(),F_std.size());
        F1=Acc_temp*mass; // accecelaration into mass
        _nstep = T_std.size();
        for (unsigned int i=0; i<T_std.size(); ++i)
        {
            if (T_std[i+1]>T_std[i])
            {
                _dt = T_std[i+1]-T_std[i];
                break;
            }
            else
            {
                // Turn this off for GUI mode
//                throw std::invalid_argument("Could not determine time-step size");
            }
        }
    }
    else
    {
        // Turn this off for GUI mode
//        throw std::invalid_argument("Could not open the file!");
    }
}



Eigen::MatrixXd TimeIntegrator::Newmark(Eigen::MatrixXd &K, Eigen::MatrixXd &M, double &del, double &gam)
{
    Eigen::MatrixXd U,V,A;
    U.setZero(K.rows(),_nstep+1);
    V.setZero(K.rows(),_nstep+1); A.setZero(K.rows(),_nstep+1);
    Eigen::VectorXd F = Eigen::VectorXd::Zero(K.rows());
    // Loop over time steps
    for (int istep=0; istep<_nstep; ++istep)
    {
        for (int i=0; i<_napp.rows(); ++i)
        {
            F(_napp(i)) = F1(istep);
        }

        U.col(istep+1) = (1.0/(_dt*_dt*gam)*M+K).llt().solve(F+1.0/(_dt*_dt*gam)*M*U.col(istep)+1/(_dt*gam)*M*V.col(istep)+(1.0/(2*gam)-1.0)*M*A.col(istep));
        A.col(istep+1) = 1.0/(_dt*_dt*gam)*(U.col(istep+1)-U.col(istep))-1.0/(_dt*gam)*V.col(istep)+(1.0-1.0/(2.0*gam))*A.col(istep);
        V.col(istep+1) = V.col(istep)+_dt*(del*A.col(istep+1)+(1-del)*A.col(istep));
    }
    return U;
}


Eigen::MatrixXd TimeIntegrator::Alpha(Eigen::MatrixXd &K, Eigen::MatrixXd &M, double &del, double &gam, double &alpha)
{
    Eigen::MatrixXd U,V,A;
    U.setZero(K.rows(),_nstep+1);
    V.setZero(K.rows(),_nstep+1); A.setZero(K.rows(),_nstep+1);
    Eigen::VectorXd F = Eigen::VectorXd::Zero(K.rows());
    Eigen::VectorXd F2 = Eigen::VectorXd::Zero(K.rows());
    // Loop over time steps
    for (int istep=0; istep<_nstep; ++istep)
    {
        if (istep==_nstep-1)
            break;
        for (int i=0; i<_napp.rows(); ++i)
        {
            F(_napp(i)) = F1(istep);
            F2(_napp(i)) = F1(istep+1);
        }

        U.col(istep+1)= (1.0/(_dt*_dt*gam)*M+(1+alpha)*K).llt().solve((1+alpha)*F2-alpha*F+(1.0 /_dt/_dt/gam*M+alpha*K)*U.col(istep)+1.0/_dt/gam*M*V.col(istep)+(1.0/(2*gam)-1)*M*A.col(istep));
        A.col(istep+1) = 1.0/(_dt*_dt*gam)*(U.col(istep+1)-U.col(istep))-1.0/(_dt*gam)*V.col(istep)+(1-1.0/(2.0*gam))*A.col(istep);
        V.col(istep+1) = V.col(istep)+_dt*(del*A.col(istep+1)+(1-del)*A.col(istep));
    }
    return U;
}

Eigen::MatrixXd TimeIntegrator::GeneralisedAlpha(Eigen::MatrixXd &K, Eigen::MatrixXd &M, double &del, double &gam, double &alphaf, double &alpham)
{
    Eigen::MatrixXd U,V,A;
    U.setZero(K.rows(),_nstep+1);
    V.setZero(K.rows(),_nstep+1); A.setZero(K.rows(),_nstep+1);
    Eigen::VectorXd F = Eigen::VectorXd::Zero(K.rows());
    Eigen::VectorXd F2 = Eigen::VectorXd::Zero(K.rows());
    // Loop over time steps
    for (int istep=0; istep<_nstep; ++istep)
    {
        if (istep==_nstep-1)
            break;
        for (int i=0; i<_napp.rows(); ++i)
        {
            F(_napp(i)) = F1(istep);
            F2(_napp(i)) = F1(istep+1);
        }

        U.col(istep+1) = ((1-alpham)/_dt/_dt/gam*M+(1-alphaf)*K).llt().solve((1-alphaf)*F2+alphaf*F+((1-alpham)/_dt/_dt/gam*M-alphaf*K)*U.col(istep)+(1-alpham)/_dt/gam*M*V.col(istep)+((1-alpham)*(1.0/2.0/gam-1)-alpham)*M*A.col(istep));
        A.col(istep+1) = 1.0/(_dt*_dt*gam)*(U.col(istep+1)-U.col(istep))-1.0/(_dt*gam)*V.col(istep)+(1-1.0/(2.0*gam))*A.col(istep);
        V.col(istep+1) = V.col(istep)+_dt*(del*A.col(istep+1)+(1-del)*A.col(istep));
    }
    return U;
}

}  // end of namespace
