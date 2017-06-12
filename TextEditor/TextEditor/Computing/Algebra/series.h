#pragma once
#include "Parsing/node.h"

class series {
    series();
    ~series();
    int start, end;
    bool integralTest();
    bool ratioTest();
    bool pTest();
    bool altTest();
    bool geoTest();
    bool nthTest();
};