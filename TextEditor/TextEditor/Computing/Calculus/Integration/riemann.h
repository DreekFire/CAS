#pragma once
#include <vector>
#include "Parsing/node.h"

static class riemann {
    enum Method {Left, Right, Mid, Trap, Simpson};
    double riemannSum(node expression, double start, double end, int numIntervals, int method);
    double riemannSum(node expression, std::vector<double> intervals, int method);
    //uneven intervals not yet supported for simpsons
};