#include "DataENP.h"

#include <iostream>

using namespace std;


DataENP::DataENP(DataNode *parent)
  : DataNode(parent)
{
}

DataENP::~DataENP()
{
  // nothing to be done
}


void DataENP::add(DataParseElement *element)
{
  cout << "hier " << endl;
  // if(element->opening(YARS_STRING_SIMULATOR))
  // {
    // element->set(YARS_STRING_FREQUENCY, _simulatorFrequency);
  // }
}



