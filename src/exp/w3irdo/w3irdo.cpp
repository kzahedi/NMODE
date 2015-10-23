#include "nmode/Data.h"
#include "nmode/Population.h"
#include "nmode/Exporter.h"
#include "nmode/Random.h"
#include "nmode/RnnFromIndividual.h"

// #include "evo/Evaluate.h"
#include "exp/braitenberg/Evolve.h"

#include <glog/logging.h>

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

#include <boost/thread.hpp>


using namespace std;
namespace po = boost::program_options;
using namespace boost;


void convert(Individual *ind, string filename)
{

  stringstream sst;
  sst << filename.substr(0, filename.size()-4) << ".html";

  cout << "opening file " << sst.str() << endl;
  std::ofstream ofs;
  ofs.open (sst.str(), std::ofstream::out);
  sst.str("");
  sst << Exporter::toX3d(ind);
  ofs << sst.str();
  ofs.close();
}


int main(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0]);

  po::options_description desc("Options");
  po::options_description ioo("Input/Output Options");
  po::options_description cmdline_options;

  po::variables_map vm;

  string xml;
  int    index = 0;

  string logdir;
  desc.add_options()
    ("index,i",
     po::value<int>(&index)->implicit_value(0),
     "index of the individual [default is 0]")
    ("xml",
     po::value<string>(&xml),
     "xml files")
    ("verbosity,v",
     po::value<int>(),
     "set verbose logging level, defaults to 0")
    ("logstderr,l",
     "set verbose logging level, defaults to 0")
    ("logdir,L",
     po::value<string>(&logdir),
     "set verbose logging level, defaults to 0");

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

  cout << "XML file: " << xml << endl;

  Evolve *evo = new Evolve();
  evo->init(xml);

  cout << "done" << endl;

  return 0;
}
