#ifndef __MODULE_GNUPLOT_H__
#define __MODULE_GNUPLOT_H__

#include "Module.h"

#define GNUPLOT_DEPRECATE_WARN
#include "ext/gnuplot-iostream.h"

class ModuleGnuplot
{
  public:
    ModuleGnuplot();
    // ~ModuleGnuplot();

    //ModuleGnuplot(const ModuleGnuplot);
    //ModuleGnuplot operator=(const ModuleGnuplot);

    void plot(Module *m);

  private:
    Gnuplot gp;
};


#endif // __MODULE_GNUPLOT_H__
