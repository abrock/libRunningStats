#include <algorithm>
#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

#include "runningstats.h"

void RunningStats::clear() {
    sum = 0;
    squaresum = 0;
    n = 0;
}

void RunningStats::push(const double value) {
    if (n == 0) {
        min = value;
        max = value;
    }
    else {
        min = std::min(min, (double)value);
        max = std::max(max, (double)value);
    }
    sum += value;
    squaresum += value * value;
    n++;

    if (calcLog && value > 0) {
        double log_val = std::log(static_cast<double>(value)) / std::log(10);
        log_sum += log_val;
        log_square_sum += log_val * log_val;
        if (log_n == 0) {
            log_min = log_val;
            log_max = log_val;
        }
        else {
            log_min = std::min(log_min, log_val);
            log_max = std::max(log_max, log_val);
        }
        log_n++;
    }
}

double RunningStats::getMean() {
    if (n < 1) {
        return 0;
    }
    return sum / n;
}
double RunningStats::getLogMean() {
    if (log_n < 1) {
        return 0;
    }
    return log_sum / log_n;
}
double RunningStats::getVar() {
    if (n < 2) {
        return 0;
    }
    return 1.0/(n-1) * (squaresum - sum*sum / n);
}
double RunningStats::getLogVar() {
    if (log_n < 2) {
        return 0;
    }
    return 1.0/(log_n-1) * (log_square_sum - log_sum*log_sum / log_n);
}
double RunningStats::getStddev() {
    return std::sqrt(getVar());
}
double RunningStats::getLogStddev() {
    return std::sqrt(getLogVar());
}
void RunningStats::print(std::ostream& out) {
    out << getMean() << " +- " << getStddev() << ", " << n << " Samples, range: [" << min << ", " << max << "]";
}

std::string RunningStats::print() {
    std::stringstream out;
    print(out);
    return out.str();
}

void RunningStats::printLog(std::ostream& out) {
    out << getLogMean() << " +- " << getLogStddev() << ", " << n << " Samples, range: [" << log_min << ", " << log_max << "]";
}

std::string RunningStats::printLog() {
    std::stringstream out;
    printLog(out);
    return out.str();
}

std::string RunningStats::printBoth() {
    return print() + "\nLogarithmic: " + printLog();
}

void QuantileStats::push(const double value){
    sorted = false;
    values.push_back(value);
    RunningStats::push(value);
}

float QuantileStats::getQuantile(const double quantile) {
    if (quantile <= 0) {
        return min;
    }
    if (quantile >= 1) {
        return max;
    }
    if (values.size() == 0) {
        return 0;
    }
    if (values.size() == 1) {
        return values[0];
    }
    sort();
    return values[(size_t)(quantile * (values.size()-1))];
}

void QuantileStats::sort() {
    if (!sorted) {
        std::sort(values.begin(), values.end());
        sorted = true;
    }
}
