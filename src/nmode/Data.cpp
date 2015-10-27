#include "Data.h"

#include "YarsXSDSaxParser.h"
#include "XmlChangeLog.h"
#include "macros.h"
#include "Population.h"

#include <glog/logging.h>
#include <unistd.h>

// #include "Data.h"

#define XML_BOOL(a) (a?"true":"false")
#define ZERO(a)     ((fabs(a)<0.0000000000001)?0:a)

#define _SIM  _root->simulator()
#define _EVA  _root->evaluation()
#define _REP  _root->reproduction()
#define _EVON _root->evolution()->node()
#define _EVOE _root->evolution()->edge()


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
  _root = new NMODE(NULL);
  _initialisationCompleted = false;
}

Data::~Data()
{
  delete _root;
}

NMODE* Data::specification()
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
  if(_xml.size() == 0)
  {
    _xml = xmlFile;
    if(xmlFile[0] != '/')
    {
      char buf[1024];
      getcwd(buf, 1024);
      stringstream sst;
      sst << buf << "/" << xmlFile;
      _xml = sst.str();
    }
  }
  cout << "reading xml file: " << _xml << endl;
  YarsXSDSaxParser *parser = new YarsXSDSaxParser();
  parser->read(xmlFile);
  if(parser->errors() > 0)
  {
    FORF(vector<string>, i, parser, w_begin(), w_end()) cout << "WARNING: " << *i << endl;
    FORF(vector<string>, i, parser, e_begin(), e_end()) cout << "ERROR:   " << *i << endl;
    FORF(vector<string>, i, parser, f_begin(), f_end()) cout << "FATAL:   " << *i << endl;
    delete parser;
    exit(-1);
  }
  delete parser;

  if(_initialisationCompleted == false)
  {
    if(_root->population() == NULL)
    {
      _root->initialiseFirstPopulationFromConfiguration();
    }
    _root->population()->addObserver(this);
    _initialisationCompleted = true;
  }
}

XsdSpecification* Data::xsd()
{
  XsdSpecification *spec = new XsdSpecification();
  NMODE::createXsd(spec);
  return spec;
}

string Data::__simulator()
{
  stringstream sst; 
  sst << "  <simulator wd=\""  << _SIM->workingDirectory() <<  "\"" << endl;
  sst << "             xml=\"" << _SIM->xml() << "\"" << endl;
  sst << "             nr=\""  << _SIM->nr() << "\"/>" << endl;
  return sst.str();
}

string Data::__evaluator()
{
  stringstream sst; 
  sst << "  <evaluation>" << endl;
  sst << "    <lifetime iterations=\"" << _EVA->lifeTime() << "\"/>" << endl;
  sst << "    <cost node=\"" << _EVA->nodeCost() << "\" edge=\"" << _EVA->nodeCost() << "\"/>" << endl;
  sst << "  </evaluation>" << endl;
  return sst.str();
}

string Data::__reproduction()
{
  stringstream sst; 
  sst << "  <reproduction>" << endl;
  sst << "    <population size=\"" << _REP->populationSize() << "\"/>" << endl;
  sst << "    <selection    pressure=\"" << _REP->selectionPressure() << "\"/>" << endl;
  sst << "    <reproduction pressure=\"" << _REP->reproductionPressure() << "\"/>" << endl;
  sst << "  </reproduction>" << endl;
  return sst.str();
}

string Data::__evolution()
{
  stringstream sst; 
  sst << "  <evolution>" << endl;
  sst << "    <node>" << endl;
  sst << "      <modify probability=\"" << _EVON->modifyProbability() << "\" "
    << "maximum=\"" << _EVON->modifyMaxValue() << "\" "
    << "delta=\""   << _EVON->modifyDelta() << "\"/>" << endl;
  sst << "      <add    probability=\"" << _EVON->addProbability() << "\" "
    << "maximum=\"" << _EVON->addMaxValue() << "\"/>" << endl;
  sst << "      <delete probability=\"" << _EVON->delProbability() << "\"/>" << endl;
  sst << "    </node>" << endl;
  sst << "    <edge>" << endl;
  sst << "      <modify probability=\"" << _EVON->modifyProbability() << "\" "
    << "maximum=\"" << _EVOE->modifyMaxValue() << "\" "
    << "delta=\""   << _EVOE->modifyDelta() << "\"/>" << endl;
  sst << "      <add    probability=\"" << _EVOE->addProbability() << "\" "
    << "maximum=\"" << _EVOE->addMaxValue() << "\"/>" << endl;
  sst << "      <delete probability=\"" << _EVOE->delProbability() << "\"/>" << endl;
  sst << "    </edge>" << endl;
  sst << "  </evolution>" << endl;
  return sst.str();
}

string Data::__configuration()
{
  stringstream sst; 

  sst << "  <configuration>" << endl;

  for(Modules::iterator
      m = _root->configuration()->m_begin();
      m != _root->configuration()->m_end();
      m++)
  {
    sst << __toXml(*m);
  }
  sst << "  </configuration>" << endl;
  return sst.str();
}

string Data::__population()
{
  stringstream sst; 
  sst << __toXml(_root->population());
  return sst.str();
}

string Data::xml()
{
  stringstream sst;

  sst << "<?xml version=\"1.0\"?>" << endl << endl;
  sst << "<nmode version=\""     << XmlChangeLog::version() << "\">" << endl;
  sst << __simulator() << endl;
  sst << __evaluator() << endl;
  sst << __reproduction() << endl;
  sst << __evolution() << endl;
  sst << __configuration() << endl;
  sst << __population() << endl;
  sst << "</nmode>" << endl;
  return sst.str();
}

string Data::__toXml(Module *m)
{
  stringstream sst;
  sst << "      <module name=\"" << m->name() << "\">" << endl;
  if(m->isCopy())
  {
    sst << "        <copy      name=\"" << m->ref() << "\"/>" << endl;
    MirrorAxes ma = m->mirrorAxes();
    Quaternion q = m->rotation();
    P3D        r;
    r << q;
    P3D        p = m->translation();
    sst << "        <mirror    x=\"" << XML_BOOL(ma.x)
                     << "\" y=\"" << XML_BOOL(ma.y)
                     << "\" z=\"" << XML_BOOL(ma.z)
                     << "\"/>" << endl;
    sst << "        <rotate    x=\"" << RAD_TO_DEG(r.x)
                     << "\" y=\"" << RAD_TO_DEG(r.y)
                     << "\" z=\"" << RAD_TO_DEG(r.z)
                     << "\"/>" << endl;
    sst << "        <translate x=\"" << p.x
                        << "\" y=\"" << p.y
                        << "\" z=\"" << p.z
                        << "\"/>" << endl;
  }
  else
  {
    for(Nodes::const_iterator n = m->n_begin(); n != m->n_end(); n++)
    {
      sst << "        <node type=\"" << (*n)->type()
        << "\" label=\"" << (*n)->label() << "\">" << endl;
      sst << "          <position x=\"" << (*n)->position().x
        << "\" y=\"" << (*n)->position().y
        << "\" z=\"" << (*n)->position().z
        << "\"/>" << endl;
      sst << "          <transferfunction name=\"" << (*n)->transferfunction()
        << "\"/>" << endl;
      sst << "          <bias value=\"" << ZERO((*n)->bias()) << "\"/>" << endl;
      sst << "        </node>" << endl;
    }
    for(Edges::const_iterator e = m->e_begin(); e != m->e_end(); e++)
    {
      sst << "        <edge source=\"" << (*e)->sourceNode()->label()
        << "\" destination=\"" << (*e)->destinationNode()->label() << "\" weight=\""
        << (*e)->weight()<< "\"/>" << endl;
    }
  }
  sst << "      </module>" << endl;
  return sst.str();
}

string Data::__toXml(Individual *i)
{
  stringstream sst;
  sst << "    <individual"
    << " id=\""      << i->id()      << "\""
    << " fitness=\"" << i->fitness() << "\""
    << ">" << endl;

  for(Modules::const_iterator m = i->m_begin(); m != i->m_end(); m++)
  {
    sst << __toXml(*m);
  }
  sst << "    </individual>" << endl;
  return sst.str();
}

string Data::__toXml(Population *pop)
{
  stringstream sst;
  sst <<"  <population generation=\"" << pop->generation() << "\">" << endl;

  for(Individuals::const_iterator i  = pop->i_begin(); i != pop->i_end(); i++)
  {
    sst << __toXml(*i);
  }
  sst <<"  </population>" << endl;

  return sst.str();
}

void Data::notify(ObservableMessage *message)
{
  switch(message->type())
  {
    case __M_NEXT_GENERATION:
      read(_xml);
      break;
  }
}
