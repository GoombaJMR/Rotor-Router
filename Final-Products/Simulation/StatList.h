//-----------------------------------------------//
//  RotorRouterMechanism Final Version A --------//
//  StatList.h    -------------------------------//
//  Created by Julian M. Rice | August 2018 -----//
//-----------------------------------------------//

#ifndef STATLIST_H
#define STATLIST_H

#include <stdio.h>

//Custom class made to store info about the
//Stabilization period
class StatList {
public:
    StatList();
    void setSum(double newSum) { m_sum = newSum; }
    void setMax(double newMax) { m_max = newMax; }
    void setMin(double newMin) { m_min = newMin; }
    void setAvg(double sum, double tests) { m_avg = sum/tests; }
    double getSum()            { return m_sum; }
    double getMax()            { return m_max; }
    double getMin()            { return m_min; }
    double getAvg()            { return m_avg; }
private:
    double m_sum;   //Sum of all periods
    double m_max;   //Maximum stabilization period
    double m_min;   //Minimum stabilization period
    double m_avg;   //Average stabilization period
};

#endif
