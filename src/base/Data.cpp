#include "Data.h"

#include "YarsXSDSaxParser.h"
#include "XmlChangeLog.h"

#include <glog/logging.h>

Data* Data::_me = NULL;

Data* Data::instance()
{
  if(_me == NULL)
  {
    _me = new Data();
  }
  return _me;
}

Data::Data()
{
  _root = new ENP(NULL);
}

Data::~Data()
{
  delete _root;
}

ENP* Data::specification()
{
  return _root;
}

void Data::clear()
{
}

void Data::close()
{
  // if(_me != NULL) delete _me;
}

void Data::read(string xmlFile)
{
  YarsXSDSaxParser *parser = new YarsXSDSaxParser();
  parser->read(xmlFile);
  if(parser->errors() > 0)
  {
    for(std::vector<string>::iterator i = parser->w_begin(); i != parser->w_end(); i++) cout << "WARNING: " << *i << endl;
    for(std::vector<string>::iterator i = parser->e_begin(); i != parser->e_end(); i++) cout << "ERROR: " << *i << endl;
    for(std::vector<string>::iterator i = parser->f_begin(); i != parser->f_end(); i++) cout << "FATAL: " << *i << endl;
    delete parser;
    exit(-1);
  }
  delete parser;

  if(_root->population() == NULL)
  {
    _root->initialiseFirstPopulationFromConfiguration();
  }
}

XsdSpecification* Data::xsd()
{
  XsdSpecification *spec = new XsdSpecification();
  ENP::createXsd(spec);
  return spec;
}

string Data::header()
{
  stringstream sst;

#define SIM  _root->simulator()
#define EVON _root->evolution()->node()
#define EVOE _root->evolution()->edge()

  sst << "<?xml version=\"1.0\"?>" << endl << endl;
  sst << "<enp version=\""     << XmlChangeLog::version() << "\">" << endl;
  sst << "  <simulator wd=\""  << SIM->workingDirectory() <<  "\"" << endl;
  sst << "             xml=\"" << SIM->xml() << "\"" << endl;
  sst << "             nr=\""  << SIM->nr() << "\"/>" << endl;

  sst << "  <evolution>" << endl;
  sst << "    <node cost=\"" << EVON->cost() << "\">" << endl;
  sst << "      <modify probability=\"" << EVON->modifyProbability() << "\" "
    << "maximum=\"" << EVON->modifyMaxValue() << "\" "
    << "delta=\""   << EVON->modifyDelta() << "\"/>" << endl;
  sst << "      <add    probability=\"" << EVON->addProbability() << "\" "
    << "maximum=\"" << EVON->addMaxValue() << "\"/>" << endl;
  sst << "      <delete probability=\"" << EVON->delProbability() << "\"/>" << endl;
  sst << "    </node>" << endl;
  sst << "    <edge cost=\"" << EVOE->cost() << "\">" << endl;
  sst << "      <modify probability=\"" << EVON->modifyProbability() << "\" "
    << "maximum=\"" << EVOE->modifyMaxValue() << "\" "
    << "delta=\""   << EVOE->modifyDelta() << "\"/>" << endl;
  sst << "      <add    probability=\"" << EVOE->addProbability() << "\" "
    << "maximum=\"" << EVOE->addMaxValue() << "\"/>" << endl;
  sst << "      <delete probability=\"" << EVOE->delProbability() << "\"/>" << endl;
  sst << "    </edge>" << endl;
  sst << "  </evolution>" << endl;

  sst << "  <configuration>" << endl;

  for(Modules::iterator
      m = _root->configuration()->m_begin();
      m != _root->configuration()->m_end();
      m++)
  {

    sst << "    <module name=\"" << (*m)->name() << "\">" << endl;

    for(Nodes::iterator n = (*m)->n_begin(); n != (*m)->n_end(); n++)
    {
      sst << "      <node type=\"" << (*n)->type() << "\" label=\"" << (*n)->label() << "\">" << endl;
      sst << "        <position x=\"" << (*n)->position().x
        << "\" y=\"" << (*n)->position().y << "\" z=\"" << (*n)->position().z << "\"/>" << endl;
      sst << "        <transferfunction name=\"" << (*n)->transferfunction() << "\"/>" << endl;
      sst << "      </node>" << endl;
    }
    sst << "    </module>" << endl;
  }
  sst << "  </configuration>" << endl;
  return sst.str();
}

string Data::footer()
{
  stringstream sst;
  sst << "</enp>" << endl;
  return sst.str();
}
