#include "Convert.h"

#include "Data.h"
#include "Exporter.h"
#include "FileSystemOperations.h"

#include <sstream>

using namespace std;

void Convert::convertIndividual(Individual* individual)
{
  stringstream sst;
  string s = "out.html";

  std::ofstream ofs;
  ofs.open(s, std::ofstream::out);
  sst.str("");
  sst << Exporter::toX3d(individual);
  ofs << sst.str();
  ofs.close();
}


void Convert::convertLast(string directory)
{
  stringstream sst;
  sst << directory << "/" << "last_generation.xml";
  if(FileSystemOperations::doesFileExist(sst.str()))
  {
    convertXmlFile(0, sst.str());
  }
}

void Convert::convertXmlFile(int index, string filename)
{
  Data *data = Data::instance();
  data->read(filename);
  Population *pop = data->specification()->population();

  if(index >= 0)
  {
    if(index > pop->i_size())
    {
      exit(-1);
    }

    Individual *ind = pop->individual(index);
    convertIndividual(ind);
  }
  else
  {
    for(int i = 0; i < pop->i_size(); i++)
    {
      Individual *ind = pop->individual(i);
      convertIndividual(ind);
    }
  }
}


