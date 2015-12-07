#include <nmode/Data.h>
#include <nmode/Population.h>
#include <nmode/Exporter.h>
#include <nmode/Random.h>
#include <nmode/Evolve.h>
#include <nmode/RnnFromIndividual.h>

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


void convert(int index, Individual* individual, string filename)
{
  stringstream sst;
  string s = "out.html";

  cout << "opening file " << s << endl;
  std::ofstream ofs;
  ofs.open (s, std::ofstream::out);
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

  string xml;
  string continueDir;
  int    individual_index;

  string logdir;
  desc.add_options()
    ("xml",
     po::value<string>(&xml),
     "xml files")
    ("convert,c",
     "convert file to X3D")
    ("individual,i",
     po::value<int>(&individual_index)->implicit_value(0),
     "set the individual index")
    ("verbosity,v",
     po::value<int>(),
     "set verbose logging level, defaults to 0")
    ("logstderr,l",
     "set verbose logging level, defaults to 0")
    ("continue",
     po::value<string>(&continueDir),
     "read and continue from directory")
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

  if(vm.count("convert"))
  {
    if(vm.count("xml") > 0)
    {
      convert(individual_index, xml);
    };
    cerr << "please five xml filename" << endl;
    return 0;
  }

  Evolve *evo = new Evolve();

  if(xml != "")
  {
    cout << endl << "XML file: " << xml << endl;
    evo->init(xml, true);
  }
  if(continueDir != "") 
  {
    cout << endl << "Configuration directory: " << continueDir << endl;
    evo->initFromDir(continueDir);
  }

  cout << "done" << endl;

  return 0;
}
