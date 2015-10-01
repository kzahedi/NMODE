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

#include <iostream>

using namespace std;

void Random::initialise()
{
  time_t t;
  time(&t);
  srand48(t);

  // cout << "random initialised:";
  // for(int i = 0; i < 10; i++)
  // {
    // cout << " " << rand(0, 100);
  // }
  // cout << endl;
  // cout << "random initialised:";
  // for(int i = 0; i < 10; i++)
  // {
    // cout << " " << unit();
  // }
  // cout << endl;

}

double Random::unit()
{
  return drand48();
}

void Random::initialise(int seed)
{
  cout << "using Random::initialise(" << seed << ")" << endl;
  srand(seed);
}

int Random::randi(int min, int max)
{
  return min + int(drand48() * (double)(max-min) + 0.5);
}


double Random::rand(double min, double max)
{
  double d = drand48();
  cout << d << " " << min << " " << max << " = " << min + d * (double)(max - min) << endl;
  return min + d * (double)(max - min);
  // return min + drand48() * (double)(max - min);
}
