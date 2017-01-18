#include <nmode/Data.h>
#include <nmode/Population.h>
#include <nmode/Exporter.h>
#include <nmode/Random.h>
#include <nmode/Evolve.h>
#include <nmode/Replay.h>
#include <nmode/ReplayEvolution.h>
#include <nmode/Convert.h>
#include <nmode/RnnFromIndividual.h>
#include <nmode/YarsXSDGenerator.h>
#include <nmode/XsdGraphvizExporter.h>

#include <glog/logging.h>

#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>

#include <boost/thread.hpp>

using namespace std;
namespace po = boost::program_options;
using namespace boost;
namespace fs = boost::filesystem;

int main(int argc, char** argv)
{
  google::InitGoogleLogging(argv[0]);

  po::options_description desc("Options");
  po::options_description ioo("Input/Output Options");
  po::options_description cmdline_options;

  po::variables_map vm;

  string xml;
  string log;
  string continueDir;
  int    individual_index;
  string replayDir;
  bool   useCapture = false;

  string logdir;
  desc.add_options()
    ("xml",
     po::value<string>(&xml),
     "xml files")
    ("xsd",
     "export the XSD gammar")
    ("pdf",
     "export the XSD gammar as PDF files")
    ("log",
     po::value<string>(&log),
     "nmode-log")
    ("convert,c",
     "convert file to X3D")
    ("capture",
     "video capture YARS")
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
    ("replayFile",
     po::value<string>(&replayDir),
     "read and continue from directory")
    ("replay",
     po::value<string>(&replayDir),
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

  if(vm.count("capture"))
  {
    useCapture = true;
  }

  if(vm.count("pdf"))
  {
    XsdGraphvizExporter::writeDotFile("pdf");
  }

  if(vm.count("xsd"))
  {
    YarsXSDGenerator *xsd = new YarsXSDGenerator();
    // cout << (*xsd) << endl;
    ofstream myfile;
    stringstream filename;
    filename << "nmode.xsd";
    myfile.open(filename.str().c_str());
    myfile << (*xsd) << endl;
    myfile.close();
    cout << "nmode.xsd written to current directory." << endl;
    delete xsd;
  }

  if (vm.count("replayFile"))
  {
    cout << "Replay directory:  " << replayDir << endl;
    Replay *r = new Replay();
    fs::path path(replayDir);
    if(fs::is_directory(path))
    {
      r->initFromDir(replayDir);
    }
    else
    {
      r->init(replayDir);
    }


    exit(0);
  }

  if (vm.count("replay"))
  {
    cout << "Replay directory:  " << replayDir << endl;
    ReplayEvolution *r = new ReplayEvolution();
    r->setUseCapture(useCapture);
    fs::path path(replayDir);
    r->replayEvolution(replayDir);
    exit(0);
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
      Convert::convertXmlFile(individual_index, xml);
    };
    cerr << "please five xml filename" << endl;
    return 0;
  }

  Evolve *evo = new Evolve();

  if(xml != "")
  {
    cout << endl << "XML file: " << xml << endl;
    evo->init(xml, true, log);
  }
  if(continueDir != "") 
  {
    cout << endl << "Configuration directory: " << continueDir << endl;
    evo->initFromDir(continueDir);
  }

  cout << "done" << endl;

  return 0;
}
