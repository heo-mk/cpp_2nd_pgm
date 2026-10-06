#pragma once
#include "Filter.h"

class ThresholdFilter : public Filter {
public:
    explicit ThresholdFilter(unsigned char threshold = 128) : threshold_(threshold) {}
    void apply(unsigned char* pixels, int width, int height);

private:
    unsigned char threshold_;
};
