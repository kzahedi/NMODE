#include "base/Data.h"
#include "base/Population.h"
#include "evo/MutateModuleOperator.h"
#include "evo/Exporter.h"
#include "base/Random.h"

#include <glog/logging.h>

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

using namespace std;

namespace po = boost::program_options;

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void convert(int index, Individual* individual, string filename)
{
  stringstream sst;
  sst << "individual_" << index << "_" << filename.substr(0, filename.size()-4) << ".html";

  cout << "opening file " << sst.str() << endl;
  std::ofstream ofs;
  ofs.open (sst.str(), std::ofstream::out);
  sst.str("");
  sst << Exporter::toX3d(individual);
  ofs << sst.str();
  ofs.close();
}

void convert(int index, string filename)
{
  Data *data = Data::instance();
  data->read(filename);
  Population *pop = data->specification()->population();

  if(index >= 0)
  {
    if(index > pop->i_size())
    {
      cout << "Individual index out of range [0, " << (pop->i_size() - 1) << "]" << endl;
      exit(-1);
    }

    Individual *ind = pop->individual(index);
    convert(index, ind, filename);
  }
  else
  {
    for(int i = 0; i < pop->i_size(); i++)
    {
      Individual *ind = pop->individual(i);
      convert(i, ind, filename);
    }
  }
}


int main(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0]);

  po::options_description desc("Options");
  po::options_description ioo("Input/Output Options");
  po::options_description cmdline_options;

  po::variables_map vm;

  vector<string> xml;
  int index = 0;

  string logdir;
  desc.add_options()
    ("index,i", po::value<int>(&index)->implicit_value(0), "index of the individual [default is 0]")
    ("xml",     po::value<vector<string> >(&xml), "xml files")
    ("verbosity,v", po::value<int>(),           "set verbose logging level, defaults to 0")
    ("logstderr,l",                             "set verbose logging level, defaults to 0")
    ("logdir,L",    po::value<string>(&logdir), "set verbose logging level, defaults to 0");

  po::positional_options_description positional;
  positional.add("xml", -1);

  cmdline_options.add(desc);

  po::store(po::command_line_parser(argc, argv).
            options(cmdline_options).
            positional(positional).
            allow_unregistered().
            run(), vm);
  po::notify(vm);

  if(vm.count("index") > 0)
  {
    cout << "Individual index: " << index << endl;
  }

  if (vm.count("verbosity"))
  {
    FLAGS_v = vm["verbosity"].as<int>();
  }
  else
  {
    FLAGS_v = 0;
  }

  if (vm.count("logstderr"))
  {
    FLAGS_alsologtostderr = 1;
  }
  else
  {
    FLAGS_alsologtostderr = 0;
  }

  if (vm.count("logdir"))
  {
    FLAGS_log_dir = logdir.c_str();
  }
  else
  {
    FLAGS_log_dir = ".";
  }

  if(vm.count("xml") > 0)
  {
    cout << "will work on the following xml files:";
    for(vector<string>::iterator s = xml.begin(); s != xml.end(); s++)
    {
      cout << " " << *s;
    }
    cout << endl;
  };


  for(vector<string>::iterator s = xml.begin(); s != xml.end(); s++)
  {
    cout << "XML file: " << *s << endl;
    convert(index, *s);
  }

  return 0;
}
