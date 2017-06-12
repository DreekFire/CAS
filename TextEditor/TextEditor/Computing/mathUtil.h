#pragma once
#include "Parsing/node.h"

static class mathUtil {
    int gcd(int a, int b);
    node factor(node a);
    node newtonMethod(node a);
    node solveFor(node left, node right);
};