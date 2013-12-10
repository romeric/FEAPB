#ifndef PIEZOAREAMOMENTS_H
#define PIEZOAREAMOMENTS_H


#ifndef READDATAFILE_H
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include<math.h>
#endif

#include <string>
#include"NumInt.h"


namespace FEAPB {

struct Moments {
    double Area;
    Eigen::Matrix<double,2,1> fiArea;
    Eigen::Matrix<double,3,1> sArea;
    Eigen::Matrix<double,4,1> tArea;
    Eigen::Matrix<double,3,1> foArea;
};

struct pTensors {
    Eigen::Matrix<double,3,3> A = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> S = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> AD = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> SD = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> ID = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> A1 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> A2 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> S1 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> S2 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> S3 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> S4 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> S5 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I1 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I2 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I3 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I4 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I5 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I6 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> I7 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> G1 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> G2 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> G3 = Eigen::Matrix<double,3,3>::Zero();
    Eigen::Matrix<double,3,3> J = Eigen::Matrix<double,3,3>::Zero();
};

Moments PiezoAreaMoments(double &x1, double &x2, std::string &NInt);
void PiezoAreaMomentsTensors(Eigen::Vector2d &IsoElast, double &rho, Eigen::Matrix<double,6,6> &Elast,
                                       Eigen::Matrix<double,3,9> &Piezo, Eigen::Matrix<double,3,3> &Die,double &shfac,
                                       double &x1, double &x2, std::string &NInt,std::string &AIso,int &Analysis,
                                        Eigen::Matrix<double,15,15> &H, Eigen::Matrix<double,6,6> &HD);


} // end of namespace

#endif // PIEZOAREAMOMENTS_H
