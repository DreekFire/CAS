#pragma once
#include "Parsing/node.h"
#include "Parsing/token.h"

static class derivative {
    public: 
        static double numDeriv(node express, double x);
        static node* deriv(node& express);
};