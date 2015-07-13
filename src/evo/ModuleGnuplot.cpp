#include "ModuleGnuplot.h"

#include <stringstream>

using namespace std;

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

string ModuleGnuplot::convert(Module *m)
{
  stringstream sst;
  sst << "set terminal wxt\n";
  sst << "unset border\n";
  sst << "unset xtics\n";
  sst << "unset ytics\n";
  sst << "unset ztics\n";
  sst << "set hidden3d\n";
  sst << "splot '-' u 1:2:3:4 with linespoints lc palette lw 3 pointsize 4 pointtype 7 notitle\n";

  for(int i = 0; i < m->n_size(); i++)
  {
    P3D p = m->node(i)->position();
    sst << p.x << " " << p.y << " " << p.z << " " << i << "\n\n\n";
  }
  
  for(Edges::iterator e = m->e_begin(); e != m->e_end(); e++)
  {
    P3D s = (*e)->source()->position();
    P3D d = (*e)->destination()->position();
    double color = ((*e)->weight() < 0.0)?6:7;
    sst << s.x << " " << s.y << " " << s.z << " " << color << "\n";
    sst << d.x << " " << d.y << " " << d.z << " " << color << "\n\n\n";
  }
  sst << "e\n";
  return sst.str();
}
