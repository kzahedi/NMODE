#include "PopulationExporter.h"

#include <sstream>



string PopulationExporter::__moduleToXml(Module *m)
{
  stringstream sst;
  sst << "      <module name=\"" << m->name() << "\">" << endl;
  for(Nodes::const_iterator n = m->n_begin(); n != m->n_end(); n++)
  {
    sst << "        <node type=\"" << (*n)->type()
      << "\" label=\"" << (*n)->label() << "\">" << endl;
    sst << "          <position x=\"" << (*n)->position().x
      << "\" y=\"" << (*n)->position().x
      << "\" z=\"" << (*n)->position().x
      << "\"/>" << endl;
    sst << "          <transferfunction name=\"" << (*n)->transferfunction()
      << "\"/>" << endl;
    sst << "          <bias value=\"" << (*n)->bias() << "\"/>" << endl;
    sst << "        </node>" << endl;
  }
  for(Edges::const_iterator e = m->e_begin(); e != m->e_end(); e++)
  {
    sst << "        <edge source=\"" << (*e)->source()->label()
      << "\" destination=\"" << (*e)->destination()->label() << "\" weight=\""
      << (*e)->weight()<< "\"/>" << endl;
  }
  sst << "      </module>" << endl;
  return sst.str();
}

string PopulationExporter::__individualToXml(Individual *i)
{
  stringstream sst;
  sst << "    <individual"
    << " id=\""      << i->id()      << "\""
    << " fitness=\"" << i->fitness() << "\""
    << ">" << endl;

  for(Modules::const_iterator m = i->m_begin(); m != i->m_end(); m++)
  {
    sst << __moduleToXml(*m);
  }
  sst << "    </individual>" << endl;
  return sst.str();
}

string PopulationExporter::toXml(Population *pop)
{
  stringstream sst;
  sst <<"  <population generation=\"" << pop->generation() << "\">" << endl;

  for(Individuals::const_iterator i  = pop->i_begin(); i != pop->i_end(); i++)
  {
    sst << __individualToXml(*i);
  }
  sst <<"  </population>" << endl;

  return sst.str();
}
