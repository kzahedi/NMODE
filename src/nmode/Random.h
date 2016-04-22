#ifndef __NMODE_RANDOM_H__
#define __NMODE_RANDOM_H__

class Random
{
  public:
    static void   initialise();
    static void   initialise(int seed);
    static int    randi(int min, int max);
    static double rand(double min, double max);
    static double unit();
};

#endif // __RANDOM_H__
