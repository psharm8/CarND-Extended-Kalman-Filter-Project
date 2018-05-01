#include <iostream>
#include "tools.h"

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
  /**
  TODO:
    * Calculate the RMSE here.
  */

    VectorXd rmse(4);
    rmse << 0,0,0,0;
    if(estimations.size()!=ground_truth.size() || estimations.size()==0){
        return rmse;
    }
    //accumulate squared residuals
    for(unsigned int i=0; i < estimations.size(); ++i){
        VectorXd residuals = estimations[i] - ground_truth[i];
        residuals = residuals.array() * residuals.array();
        rmse += residuals;
    }

    //calculate the mean
    rmse = rmse / estimations.size();

    //calculate the squared root
    rmse = sqrt(rmse.array());
    if(rmse[3]>1){
       std::cout<<"RMSE fail: "<<rmse<<std::endl;
    }
    //return the result
    return rmse;
}

MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
  /**
  TODO:
    * Calculate a Jacobian here.
  */
    MatrixXd Hj(3, 4);
    //recover state parameters
    float px = x_state(0);
    float py = x_state(1);
    float vx = x_state(2);
    float vy = x_state(3);

    //pre-compute a set of terms to avoid repeated calculation
    float c1 = px*px + py*py;

    //check division by zero
    if (c1 < 0.00001){
        std::cout<<"Jacobian div by zero"<<std::endl;
        px += .001;
        py += .001;
        c1 = px * px + py * py;
    }

    float c2 = sqrt(c1);
    float c3 = (c1*c2);

    //compute the Jacobian matrix
    Hj << (px / c2), (py / c2), 0, 0,
            -(py / c1), (px / c1), 0, 0,
            (py*(vx*py - vy*px)) / c3, (px*(px*vy - py*vx)) / c3, px / c2, py / c2;

    return Hj;
}
