#include "base/Configuration.h"
#include "base/xsd/generator/YarsXSDGenerator.h"

#include <string>
#include <iostream>
#include <fstream>

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <glog/logging.h>

using namespace std;

namespace po = boost::program_options;

Configuration::Configuration(int argc, char* argv[], bool io)
{
  po::options_description desc("Options");
  po::options_description ioo("Input/Output Options");
  po::options_description cmdline_options;
  
  po::variables_map vm;

  string logdir;
  desc.add_options()
    ("help",                                    "print help message")
    ("verbosity,v", po::value<int>(),           "set verbose logging level, defaults to 0")
    ("logstderr,l",                             "set verbose logging level, defaults to 0")
    ("logdir,L",    po::value<string>(&logdir), "set verbose logging level, defaults to 0")
    ("xsd",                                     "export the XSD and quit.")
    ("cfg",         po::value<string>(&_cfg),   "cfg file");

  ioo.add_options()
    ("input",  po::value<string>(&_input),  "input module")
    ("output", po::value<string>(&_output), "output module");

  po::positional_options_description positional;
  positional.add("cfg", -1);

  cmdline_options.add(desc);
  if(io == true) cmdline_options.add(ioo);

  po::store(po::command_line_parser(argc, argv).
            options(cmdline_options).
            positional(positional).
            allow_unregistered().
            run(), vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << desc << "\n";
    if(io) cout << ioo << "\n";
    exit(0);
  }

  if(vm.count("xsd"))
  {
    YarsXSDGenerator *xsd = new YarsXSDGenerator();
    // cout << (*xsd) << endl;
    ofstream myfile;
    stringstream filename;
    filename << "enp.xsd";
    myfile.open(filename.str().c_str());
    myfile << (*xsd) << endl;
    myfile.close();
    cout << filename.str() << " written to current directory." << endl;
    delete xsd;
    exit(0);
  }

  if(vm.count("cfg") == 0)
  {
    cerr << "Please give a configuration file. See "
         << argv[0]
         << " --help for more information." << endl;
    exit(-1);
  };

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
}

string Configuration::input()
{
  return _input;
}

string Configuration::output()
{
  return _output;
}

string Configuration::cfg()
{
  return _cfg;
}
