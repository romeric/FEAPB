#ifndef TIMEINTEGRATION_H
#define TIMEINTEGRATION_H

#ifndef DEFINEPROBLEM_H
#include<Eigen/Dense>
#include<fstream>
#include<iterator>
#endif

namespace FEAPB {

class TimeIntegrator {
public:
    TimeIntegrator(Eigen::VectorXd &napp);
    TimeIntegrator(Eigen::VectorXd &napp, std::ifstream &dyn_id, double &mass);
    Eigen::MatrixXd Newmark(Eigen::MatrixXd &K, Eigen::MatrixXd &M, double &del, double &gam);
    Eigen::MatrixXd Alpha(Eigen::MatrixXd &K, Eigen::MatrixXd &M, double &del, double &gam, double &alpha);
    Eigen::MatrixXd GeneralisedAlpha(Eigen::MatrixXd &K, Eigen::MatrixXd &M, double &del, double &gam, double &alphaf, double &alpham);
private:
    int _nstep;
    double _dt;
    Eigen::VectorXd _napp;
    Eigen::VectorXd F1;
};


}


#endif // TIMEINTEGRATION_H
