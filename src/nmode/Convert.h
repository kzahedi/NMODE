#ifndef __CONVERT_H__
#define __CONVERT_H__

#include "Individual.h"

class Convert
{
  public:

    static void convertIndividual(Individual* individual);
    static void convertXmlFile(int index, string filename);
    static void convertLast(string directory);

  private:
};


#endif // __CONVERT_H__
