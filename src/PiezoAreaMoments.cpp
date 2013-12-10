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

#include"PiezoAreaMoments.h"


namespace FEAPB {

Moments PiezoAreaMoments(double &x1, double &x2, std::string &NInt)
{
    // Get integration points/weights
    Eigen::MatrixXd zw;
    const int dumC=3;
    if (boost::iequals(boost::trim_copy(NInt),"GaussLobatto")||boost::iequals(boost::trim_copy(NInt),"Gauss Lobatto")||
            boost::iequals(boost::trim_copy(NInt),"Gauss_Lobatto"))
    {
        zw = NumInt::GuassLobattoQaudrature(dumC);
    }

    else
    {
        double a=-1.0; double b=1.0;
        zw = NumInt::GuassQaudrature(dumC,a,b);
    }

    Eigen::VectorXd z = zw.col(0); Eigen::VectorXd w = zw.col(1);

    // Area
    double area=0;
    for (int i=0; i<zw.rows(); i++)
    {
        for (int j=0; j<zw.rows(); j++)
        {
            area +=w(i)*w(j);
        }
    }
    area = x1/2*x2/2*area;


    // First moment of area
    double S1=0; double S2=0;
    for (int i=0; i<zw.rows(); i++)
    {
        for (int j=0; j<zw.rows(); j++)
        {
            S1+=x1/2*z(j)*w(i)*w(j);
            S2+=x2/2*z(j)*w(i)*w(j);
        }
    }
    S1 = x1/2*x2/2*S1;
    S2 = x1/2*x2/2*S2;


    // Second moment of area
    double I22 =0; double I11=0; double I12 = 0;
    for (int i=0; i<zw.rows(); i++)
    {
        for (int j=0; j<zw.rows(); j++)
        {
            I11+=pow(x1,2)/4*pow(z(j),2)*w(i)*w(j);
            I22+=pow(x2,2)/4*pow(z(j),2)*w(i)*w(j);
            I12+=x1*x2/4*z(j)*z(i)*w(i)*w(j);
        }
    }
    I11 = x1/2*x2/2*I11;
    I22 = x1/2*x2/2*I22;
    I12 = x1/2*x2/2*I12;

    // Third moment of area
    double G111=0; double G222=0; double G112=0; double G221=0;
    for (int i=0; i<zw.rows(); i++)
    {
        for (int j=0; j<zw.rows(); j++)
        {
            G111+=pow(x1,3)/8*pow(z(j),3)*w(i)*w(j);
            G222+=pow(x2,3)/8*pow(z(j),3)*w(i)*w(j);
            G221+=pow(x2,2)*x1/8*pow(z(j),2)*z(i)*w(i)*w(j);
            G112+=pow(x1,2)*x2/8*pow(z(j),2)*z(i)*w(i)*w(j);
        }
    }
    G111 = x1/2*x2/2*G111;
    G222 = x1/2*x2/2*G222;
    G112 = x1/2*x2/2*G112;
    G221 = x1/2*x2/2*G221;


    // 4th moment of area
    double J1111=0; double J2222=0; double J1122=0;
    for (int i=0; i<zw.rows(); i++)
    {
        for (int j=0; j<zw.rows(); j++)
        {
            J1111+=pow(x1,4)/16*pow(z(j),4)*w(i)*w(j);
            J2222+=pow(x2,4)/16*pow(z(j),4)*w(i)*w(j);
            J1122+=pow(x2,2)*pow(x1,2)/16*pow(z(j),2)*pow(z(i),2)*w(i)*w(j);
        }
    }
    J1111 = x1/2*x2/2*J1111;
    J2222 = x1/2*x2/2*J2222;
    J1122 = x1/2*x2/2*J1122;


    Moments AreaMoments;
    AreaMoments.Area = area;
    AreaMoments.fiArea << S1,S2;
    AreaMoments.sArea << I11, I22, I12;
    AreaMoments.tArea << G111, G222, G112, G221;
    AreaMoments.foArea << J1111, J2222, J1122;
    return AreaMoments;
}


void PiezoAreaMomentsTensors(Eigen::Vector2d &IsoElast, double &rho, Eigen::Matrix<double,6,6> &Elast,
                                       Eigen::Matrix<double,3,9> &Piezo, Eigen::Matrix<double,3,3> &Die,double &shfac,
                                       double &x1, double &x2, std::string &NInt,std::string &AIso,int &Analysis,
                                        Eigen::Matrix<double,15,15> &H, Eigen::Matrix<double,6,6> &HD)
{
    // Integrate along area directions
    Moments AreaMoments;
    AreaMoments = PiezoAreaMoments(x1,x2,NInt);
    double Area = AreaMoments.Area;
    double S1 = AreaMoments.fiArea(0);     double S2 = AreaMoments.fiArea(1);
    double I11= AreaMoments.sArea(0);   double I22= AreaMoments.sArea(1);   double I12= AreaMoments.sArea(2);
    double G111=AreaMoments.tArea(0);   double G222=AreaMoments.tArea(1);
    double G112=AreaMoments.tArea(2); double G221=AreaMoments.tArea(3);
    double J1111=AreaMoments.foArea(0); double J2222=AreaMoments.foArea(1); double J1122=AreaMoments.foArea(2);

    // Build Tensors
    double meu = IsoElast(0); double lam=IsoElast(1);

    pTensors ptensors;
    if (boost::iequals(boost::trim_copy(AIso),"Isotropic"))
    {
        Eigen::Vector3d dum1; dum1 << meu*Area*shfac, meu*Area*shfac, (2*meu+lam)*Area;
        ptensors.A = dum1.asDiagonal(); //Eigen::DiagonalWrapper
        ptensors.S << 0, 0, -meu*S2,    0, 0, meu*S1,    (2*meu+lam)*S2, -(2*meu+lam)*S1, 0;
        Eigen::Vector3d dum2; dum2 << (2*meu+lam)*I22, (2*meu+lam)*I11, meu*(I11+I22);
        ptensors.I = dum2.asDiagonal();
        ptensors.I(0,1)= -(2*meu+lam)*I12; ptensors.I(1,0) = ptensors.I(0,1);
    }
    else
    {
        ptensors.A << Elast(4,4), Elast(3,4), Elast(2,4),
                Elast(3,4), Elast(3,3), Elast(2,3),
                Elast(2,4), Elast(2,3), Elast(2,2)/shfac;
        ptensors.A *=Area*shfac; // is safe from aliasing
        ptensors.S << Elast(2,4)*S2, -Elast(2,4)*S1,  Elast(3,4)*S1-Elast(4,4)*S2,
                Elast(2,3)*S2, -Elast(2,3)*S1, Elast(3,3)*S1-Elast(3,4)*S2,
                Elast(2,2)*S2, -Elast(2,2)*S1, Elast(2,3)*S1-Elast(2,4)*S2;
        ptensors.I << Elast(2,2)*I22, -Elast(2,2)*I12, Elast(2,3)*I12-Elast(2,4)*I22,
                -Elast(2,2)*I12, Elast(2,2)*I11, -Elast(2,3)*I11+Elast(2,4)*I12,
                Elast(2,3)*I12-Elast(2,4)*I22, -Elast(2,3)*I11+Elast(2,4)*I12, Elast(3,3)*I11-2*Elast(3,4)*I12+Elast(4,4)*I22;
    }

    if (Analysis!=1)
    {
        Eigen::Vector3d dum3 =Eigen::Vector3d::Constant(Area*rho);
        ptensors.AD = dum3.asDiagonal();
        ptensors.SD << 0, 0, -rho*S2,    0, 0, rho*S1,   rho*S2, -rho*S1, 0;
        Eigen::Vector3d dum4; dum4 << rho*I22, rho*I11, rho*(I11+I22);
        ptensors.ID = dum4.asDiagonal();
        ptensors.ID(0,1) = -rho*I12; ptensors.ID(1,0) = ptensors.ID(0,1);
    }

    ptensors.A1 << Piezo(0,4), Piezo(1,4), Piezo(2,4),
            Piezo(0,3), Piezo(1,3), Piezo(2,3),
            Piezo(0,2), Piezo(1,2), Piezo(2,2);
    ptensors.A1 = Area*ptensors.A1;

    ptensors.A2 = Area*Die;


    ptensors.S1 << S1*Piezo(2,4), S2*Piezo(2,4), 0,
            S1*Piezo(2,3), S2*Piezo(2,3), 0,
            S1*Piezo(2,2), S2*Piezo(2,2), 0;

    ptensors.S2 << S1*Piezo(0,4), S2*Piezo(1,4), 0,
            S1*Piezo(0,3), S2*Piezo(1,3), 0,
            S1*Piezo(0,2), S2*Piezo(1,2), 0;

    ptensors.S3.row(0) = (Piezo.col(2)*S1);
    ptensors.S3.row(1) = (-Piezo.col(2)*S2);
    ptensors.S3.row(2) = (Piezo.col(3)*S1)-(Piezo.col(4)*S2);

    Eigen::Matrix<double,3,1> pax,e3; pax<< S1,S2,0; e3 << 0,0,1;
    ptensors.S4 = Die*(e3*pax.transpose());

    Eigen::Matrix<double,3,3> dum5; dum5 << S1, 0, 0,    0, S2, 0,   0, 0, 0;
    ptensors.S5 = Die*dum5;


    ptensors.I1 << I11*Piezo(2,4)*0.5, I22*Piezo(2,4)*0.5, 0,
            I11*Piezo(2,3)*0.5, I22*Piezo(2,3)*0.5, 0,
            I11*Piezo(2,2)*0.5, I22*Piezo(2,2)*0.5, 0;

    ptensors.I2 << I12*Piezo(2,2), I22*Piezo(2,2), 0,
            -I11*Piezo(2,2), -I12*Piezo(2,2), 0,
            I11*Piezo(2,3)-I12*Piezo(2,4), I12*Piezo(2,3)-I22*Piezo(2,4), 0;

    ptensors.I3 << I12*Piezo(0,2), I22*Piezo(1,2), 0,
            -I11*Piezo(0,2), -I12*Piezo(1,2), 0,
            I11*Piezo(0,3)-I12*Piezo(0,4), I12*Piezo(1,3)-I22*Piezo(1,4), 0;

    Eigen::Matrix<double,3,3> dum6 = Eigen::Matrix<double,3,3>::Zero(); dum6(2,0)=0.5*I11; dum6(2,1)=0.5*I22;
    ptensors.I4 = Die*dum6;

    Eigen::Matrix<double,2,2> dum7;  dum7 << I11, I12, I12, I22;
//    ptensors.I5 = Eigen::Matrix<double,3,3>::Zero();
    ptensors.I5.block<2,2>(0,0) = Die(2,2)*dum7;

//    ptensors.I6 = Eigen::Matrix<double,3,3>::Zero();
    ptensors.I6.block<2,2>(0,0) = dum7;
    ptensors.I6.col(0) *=Die(2,0); ptensors.I6.col(1) *=Die(2,1);

    ptensors.I7 << I11*Die(0,0), I12*Die(0,1), 0,
            I12*Die(1,0), I22*Die(1,1), 0,
            0, 0, 0;


    ptensors.G1 << G112*Piezo(2,2)*0.5, G222*Piezo(2,2)*0.5, 0,
            -G111*Piezo(2,2)*0.5, -G221*Piezo(2,2)*0.5, 0,
            G111*Piezo(2,3)*0.5-G221*Piezo(2,4)*0.5, G221*Piezo(2,3)*0.5-G222*Piezo(2,4)*0.5, 0;

    Eigen::Matrix<double,2,2> dum8;  dum8 << G111, G112, G221, G222;
//    ptensors.G2 = Eigen::Matrix<double,3,3>::Zero();
    ptensors.G2.block<2,2>(0,0) = 0.5*Die(2,2)*dum8;

//    ptensors.G3 = Eigen::Matrix<double,3,3>::Zero();
    ptensors.G3.block<2,2>(0,0) = dum8;
    ptensors.G3.row(0) *=0.5*Die(0,2);  ptensors.G3.row(1) *=0.5*Die(1,2);


    Eigen::Matrix<double,2,2> dum9;  dum9 << J1111, J1122, J1122, J2222;
//    ptensors.J = Eigen::Matrix<double,3,3>::Zero();
    ptensors.J.block<2,2>(0,0) = 0.25*Die(2,2)*dum9;



    // Build constitutive matrix H
//    Eigen::Matrix<double,15,15> H = Eigen::Matrix<double,15,15>::Zero();
    H = Eigen::Matrix<double,15,15>::Zero();
    H << ptensors.A, ptensors.S, ptensors.A1, ptensors.S1.block<3,2>(0,0), ptensors.S2.block<3,2>(0,0), ptensors.I1.block<3,2>(0,0),
            ptensors.S.transpose(), ptensors.I, ptensors.S3, ptensors.I2.block<3,2>(0,0), ptensors.I3.block<3,2>(0,0), ptensors.G1.block<3,2>(0,0),
            ptensors.A1.transpose(), ptensors.S3.transpose(), ptensors.A2, ptensors.S4.block<3,2>(0,0), ptensors.S5.block<3,2>(0,0), ptensors.I4.block<3,2>(0,0),
            ptensors.S1.transpose().block<2,3>(0,0), ptensors.I2.transpose().block<2,3>(0,0), ptensors.S4.transpose().block<2,3>(0,0), ptensors.I5.block<2,2>(0,0),
            ptensors.I6.block<2,2>(0,0), ptensors.G2.block<2,2>(0,0),
            ptensors.S2.transpose().block<2,3>(0,0), ptensors.I3.transpose().block<2,3>(0,0), ptensors.S5.transpose().block<2,3>(0,0), ptensors.I6.transpose().block<2,2>(0,0),
            ptensors.I7.block<2,2>(0,0), ptensors.G3.transpose().block<2,2>(0,0),
            ptensors.I1.transpose().block<2,3>(0,0), ptensors.G1.transpose().block<2,3>(0,0), ptensors.I4.transpose().block<2,3>(0,0), ptensors.G2.transpose().block<2,2>(0,0),
            ptensors.G3.block<2,2>(0,0), ptensors.J.block<2,2>(0,0);

    H.block<9,9>(6,6) *=-1;

//    Eigen::Matrix<double,6,6> HD = Eigen::Matrix<double,6,6>::Zero();
    HD = Eigen::Matrix<double,6,6>::Zero();
    if (Analysis!=1)
    {
        HD << ptensors.AD, ptensors.SD,
                ptensors.SD.transpose(), ptensors.ID;
    }
}


} // end of namespace

