/*************************************************************************
 *                                                                       *
 * This file is part of Yet Another Robot Simulator (YARS).              *
 * Copyright (C) 2003-2015 Keyan Ghazi-Zahedi.                           *
 * All rights reserved.                                                  *
 * Email: keyan.zahedi@googlemail.com                                    *
 * Web: https://github.com/kzahedi/YARS                                  *
 *                                                                       *
 * For a list of contributors see the file AUTHORS.                      *
 *                                                                       *
 * YARS is free software; you can redistribute it and/or modify it under *
 * the terms of the GNU General Public License as published by the Free  *
 * Software Foundation; either version 2 of the License, or (at your     *
 * option) any later version.                                            *
 *                                                                       *
 * YARS is distributed in the hope that it will be useful, but WITHOUT   *
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or *
 * FITNESS FOR A PARTICULAR PURPOSE.                                     *
 *                                                                       *
 * You should have received a copy of the GNU General Public License     *
 * along with YARS in the file COPYING; if not, write to the Free        *
 * Software Foundation, Inc., 51 Franklin St, Fifth Floor,               *
 * Boston, MA 02110-1301, USA                                            *
 *                                                                       *
 *************************************************************************/


#include "Random.h"

#include <stdlib.h>

#ifdef _MSC_VER
#  include <time.h>
#else
#  include <sys/time.h>
#  include <time.h>
#endif

#include <iostream>

void Random::initialise()
{
#ifdef __APPLE__
  sranddev();
#else
  timespec time;
  clock_gettime(CLOCK_REALTIME, &time);
  srand(time.tv_nsec);
#endif // __APPLE__
}

double Random::unit()
{
  return ((double)random()) /
         ((double)RAND_MAX);
}

void Random::initialise(int seed)
{
  srand(seed);
}


int Random::rand(int min, int max)
{
  return min + int(unit() * (double)max + 0.5);
}

double Random::rand(double min, double max)
{
  return min + (unit() * max);
}
