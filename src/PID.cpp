#include "PID.h"

#include <numeric>
#include <cmath>

using namespace std;

/**
 * TODO: Complete the PID class. You may add any additional desired functions.
 */

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {
  /**
   * TODO: Initialize PID coefficients (and errors, if needed)
   */
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  p_error = 1.0;
  i_error = 1.0;
  d_error = 1.0;
}

void PID::UpdateError(double cte) {
  /**
   * TODO: Update PID errors based on cte.
   */

}

double PID::TotalError() {
  double err = 0;
  for (int i = 0; i < ctes.size(); i++)
  {
    err += pow(ctes[i], 2);
  }

  return err / ctes.size();
}

double PID::CalcSteer(double curr_cte)
{
  double prev_cte = ctes.size() > 0 ? ctes.back() : curr_cte;
  double cte_d = curr_cte - prev_cte;

  ctes.push_back(curr_cte);
  double cte_i = accumulate(ctes.begin(), ctes.end(), 0);

  double steer = -Kp * curr_cte - Kd * cte_d - Ki * cte_i;
  return steer;
}