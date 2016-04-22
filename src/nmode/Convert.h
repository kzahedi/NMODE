#ifndef __NMODE_CONVERT_H__
#define __NMODE_CONVERT_H__

#include  <nmode/Individual.h>

class Convert
{
  public:

    static void convertIndividual(Individual* individual);
    static void convertXmlFile(int index, string filename);
    static void convertLast(string directory);

  private:
};


#endif // __CONVERT_H__
