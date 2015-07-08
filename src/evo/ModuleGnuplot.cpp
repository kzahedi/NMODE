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



#include "ModuleGnuplot.h"


ModuleGnuplot::ModuleGnuplot()
  : gp()
{
  gp << "set terminal wxt\n";
  gp << "unset border\n";
  gp << "unset xtics\n";
  gp << "unset ytics\n";
  gp << "unset ztics\n";
  gp << "set hidden3d\n";
}

void ModuleGnuplot::plot(Module *m)
{
  gp << "clear\n";
  gp << "splot '-' u 1:2:3:4 with linespoints lc palette lw 3 pointsize 4 pointtype 7 notitle\n";

  for(int i = 0; i < m->n_size(); i++)
  {
    P3D p = m->node(i)->position();
    gp << p.x << " " << p.y << " " << p.z << " " << i << "\n\n\n";
  }
  
  for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
  {
    P3D s = (*e)->source()->position();
    P3D d = (*e)->destination()->position();
    double color = ((*e)->weight() < 0.0)?6:7;
    gp << s.x << " " << s.y << " " << s.z << " " << color << "\n";
    gp << d.x << " " << d.y << " " << d.z << " " << color << "\n\n\n";
  }
  gp << "e\n";
}
