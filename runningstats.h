#ifndef RUNNINGSTATS_H
#define RUNNINGSTATS_H

#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

class RunningStats {

public:
    void clear();

    void push(const double value);

    double getMean();

    double getLogMean();

    double getVar();

    double getLogVar();

    double getStddev();

    double getLogStddev();

    void print(std::ostream& out);

    std::string print();

    void printLog(std::ostream& out);

    std::string printLog();

    std::string printBoth();

    double sum = 0;
    double squaresum = 0;
    double min = 0;
    double max = 0;
    size_t n = 0;

    bool calcLog = true;

    double log_sum = 0;
    double log_square_sum = 0;
    double log_min = 0;
    double log_max = 0;
    size_t log_n = 0;
};

class QuantileStats : public RunningStats {
public:
    void push(const double value);

    float getQuantile(const double quantile);

private:
    void sort();

    std::vector<float> values;
    bool sorted = true;
};

#endif // RUNNINGSTATS_H
