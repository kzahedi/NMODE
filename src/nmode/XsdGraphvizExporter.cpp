#include <nmode/XsdGraphvizExporter.h>

#include <nmode/FileSystemOperations.h>

class Pair
{
  public:
    Pair(string p, string n, bool rl = true, int d = -1, string f = "")
    {
      parent   = p;
      name     = n;
      depth    = d;
      lr       = rl;
      if(f == "")
      {
        stringstream oss;
        oss << p << "_" << n;
        filename = oss.str();
      }
      else
      {
        filename = f;
      }
    }

    string parent;
    string name;
    string filename;
    int    depth;
    bool   lr;
};

void XsdGraphvizExporter::writeDotFile(string filetype)
{

  cout << "Exporting to ./" << filetype << endl;

  std::vector<Pair*> name;

  // name.push_back(new Pair( (char*)"nmode",         (char*)"simulator", true, 2));
  // name.push_back(new Pair( (char*)"nmode",         (char*)"mutation",  true, 2));
  name.push_back(new Pair( (char*)"mutation",      (char*)"edge"));
  // name.push_back(new Pair( (char*)"mutation",      (char*)"node",      true));
  // name.push_back(new Pair( (char*)"configuration", (char*)"node",      true));

  XsdGraphvizGenerator *xsd = new XsdGraphvizGenerator();

  stringstream dir;
  dir << "./" << filetype;
  fs::path dotDir = "./dot";
  fs::path exportDir = dir.str();


  if(!fs::exists(dotDir))    fs::create_directory(dotDir);
  if(!fs::exists(exportDir)) fs::create_directory(exportDir);

  ofstream myfile;

  stringstream filename;
  for(std::vector<Pair*>::iterator i = name.begin(); i != name.end(); i++)
  {
    filename.str("");
    if((*i)->filename.length() == 0) filename << "./dot/" << (*i)->name     << ".dot";
    else                             filename << "./dot/" << (*i)->filename << ".dot";
    xsd->generate((*i)->parent, (*i)->name, (*i)->lr, (*i)->depth);
    myfile.open(filename.str().c_str());
    myfile << (*xsd) << endl;
    myfile.close();
    cout << "writing " << filename.str() << endl;
  }

  if (FileSystemOperations::doesExecutableExist(filetype))
  {
    cout << "Found dot executable. Exporting dot -> " << filetype << endl;
    stringstream oss;
    for(std::vector<Pair*>::iterator i = name.begin(); i != name.end(); i++)
    {
      oss.str("");
      filename.str("");
      if((*i)->filename.length() == 0) filename << "./dot/" << (*i)->name     << ".dot";
      else                             filename << "./dot/" << (*i)->filename << ".dot";
      oss << "dot -T" << filetype << " " << filename.str() << " -o ";
      // oss << "twopi -T" << filetype << " " << filename.str() << " -o ";
      filename.str("");
      if((*i)->filename.length() == 0) filename << filetype << "/" << (*i)->name << "." << filetype;
      else                             filename << filetype << "/" << (*i)->filename << "." << filetype;
      oss << filename.str();
      system(oss.str().c_str());
      cout << oss. str() << endl;
    }
  }
  else
  {
    cout << "Cannot find dot executable." << endl;
  }

  cout << "done." << endl;
}
