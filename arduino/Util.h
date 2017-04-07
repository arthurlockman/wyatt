inline int mapDoubleToInt(double x, double in_min, double in_max, int out_min, int out_max)
{
    return (int)((x - in_min) * (double)(out_max - out_min) / (in_max - in_min) + (double)out_min);
}