#include "riemann.h"

double riemann::riemannSum(node expression, double start, double end, int numIntervals, int method) {
    double currentX = start;
    double dx = (end - start) / numIntervals;
    double value = 0;
    if (method < Method::Mid) {
        for (int i = 0; i < numIntervals; i++) {
            value += expression.evaluate(start + (i+method)*dx);
        }
    }
    else if (method == Method::Mid) {
        value = riemannSum(expression, start + 0.5, end + 0.5, numIntervals, Method::Left);
    }
    else if (method == Method::Trap) {
        value = (riemannSum(expression, start, end, numIntervals, Method::Left) + riemannSum(expression, start, end, numIntervals, Method::Right))/2;
    }
    else if (method == Method::Simpson) {
        for (int i = 0; i < numIntervals / 2; i++) {
            value += (dx / 6)*(expression.evaluate(start + 2 * i * dx) + (4 * expression.evaluate(start + (2 * i + 1) * dx)) + expression.evaluate(start + (2 * i + 2) * dx));
        }
    }
    return value;
}

double riemann::riemannSum(node expression, std::vector<double> intervals, int method) {
    double currentX = intervals.at(0);
    double value = 0;
    if (method < Method::Mid) {
        for (int i = 0; i < (int)intervals.size()-1; i++) {
            value += expression.evaluate(intervals.at(i + method));
        }
    }
    else if (method == Method::Mid) {
        for (int i = 0; i < (int)intervals.size()-1; i++) {
            value += expression.evaluate((intervals.at(i)+intervals.at(i+1))/2);
        }
    }
    else if (method == Method::Trap) {
        for (int i = 0; i < (int)intervals.size()-1; i++) {
            value += (expression.evaluate(intervals.at(i)) + expression.evaluate(intervals.at(i+1)))/2;
        }
    }
    /*else if (method == Method::Simpson) {
        for (int i = 0; i < (int)intervals.size() / 2; i++) {
            value += (dx / 6)*(expression.evaluate(start + 2 * i * dx) + (4 * expression.evaluate(start + (2 * i + 1) * dx)) + expression.evaluate(start + (2 * i + 2) * dx));
        }
    }*/
    return value;
}