#pragma once

inline int mapDoubleToInt(double x, double in_min, double in_max, int out_min, int out_max)
{
    return (int)((x - in_min) * (double)(out_max - out_min) / (in_max - in_min) + (double)out_min);
};

inline double mapIntToDouble(int x, int in_min, int in_max, double out_min, double out_max) {
    return (double)((x - in_min) * (out_max - out_min) / (double)(in_max - in_min) + out_min);
};