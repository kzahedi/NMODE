#include "Exporter.h"

#include <sstream>



string Exporter::toXml(Module *m)
{
  stringstream sst;
  sst << "      <module name=\"" << m->name() << "\">" << endl;
  for(Nodes::const_iterator n = m->n_begin(); n != m->n_end(); n++)
  {
    sst << "        <node type=\"" << (*n)->stype()
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

string Exporter::toXml(Individual *i)
{
  stringstream sst;
  sst << "    <individual"
    << " id=\""      << i->id()      << "\""
    << " fitness=\"" << i->fitness() << "\""
    << ">" << endl;

  for(Modules::const_iterator m = i->m_begin(); m != i->m_end(); m++)
  {
    sst << toXml(*m);
  }
  sst << "    </individual>" << endl;
  return sst.str();
}

string Exporter::toXml(Population *pop)
{
  stringstream sst;
  sst <<"  <population generation=\"" << pop->generation() << "\">" << endl;

  for(Individuals::const_iterator i  = pop->i_begin(); i != pop->i_end(); i++)
  {
    sst << toXml(*i);
  }
  sst <<"  </population>" << endl;

  return sst.str();
}

string Exporter::__povHeader()
{
  stringstream sst;
  sst << "global_settings {" << endl;
  sst << "  adc_bailout 0.00392157" << endl;
  sst << "  assumed_gamma 1.5" << endl;
  sst << "  noise_generator 2" << endl;
  sst << "}" << endl;
  sst << endl;
  sst << "light_source {" << endl;
  sst << "  <0, 0, -10>, rgb <1, 1, 1>" << endl;
  sst << "  shadowless" << endl;
  sst << "  parallel" << endl;
  sst << "}" << endl;
  sst << endl;
  sst << "sky_sphere {" << endl;
  sst << "  pigment {" << endl;
  sst << "    color rgb <1, 1, 1>" << endl;
  sst << "  }" << endl;
  sst << "}" << endl;
  sst << endl;
  sst << "camera {" << endl;
  sst << "  orthographic" << endl;
  sst << "  location <0, 0, -10>" << endl;
  sst << "  sky <0, 1, 0>" << endl;
  sst << "  direction <0, 0, 1>" << endl;
  sst << "  right <10, 0, 0>" << endl;
  sst << "  up <0, 10.59, 0>" << endl;
  sst << "  look_at <0, 0, 0>" << endl;
  sst << "  translate z*(-10)" << endl;
  sst << "}" << endl;
  sst << endl;
  return sst.str();
}

string Exporter::toPov(Individual *i, bool useHeader)
{
  stringstream sst;
  if(useHeader) sst << __povHeader();
  for(Modules::iterator m = i->m_end(); m != i->m_end(); m++) toPov(*m);
  return sst.str();
}

string Exporter::toPov(Module *m, bool useHeader)
{
  stringstream sst;
  if(useHeader) sst << __povHeader();

  for(Nodes::iterator n = m->n_end(); n != m->n_end(); n++) toPov(*n);
  // for(Edges::iterator e = m->e_end(); e != m->e_end(); e++) toPov(*e);

  return sst.str();
}

string Exporter::toPov(Node *node, bool useHeader)
{
  stringstream sst;
  if(useHeader) sst << __povHeader();
  sst << "sphere {" << endl;
  sst << "      <" << node->position() << ">, 0.9" << endl;
  sst << "      " << endl;
  sst << "      pigment {" << endl;
  switch(node->type())
  {
    case NODE_TYPE_SENSOR:
      sst << "         color rgb <1, 0, 0>" << endl;
      break;
    case NODE_TYPE_ACTUATOR:
      sst << "         color rgb <0, 1, 0>" << endl;
      break;
    case NODE_TYPE_HIDDEN:
      sst << "         color rgb <0, 0, 1>" << endl;
      break;
    case NODE_TYPE_INPUT:
      sst << "         color rgb <0.98, 0.81, 0>" << endl;
      break;
    case NODE_TYPE_OUTPUT:
      sst << "         color rgb <0.98, 0.41, 0>" << endl;
      break;
    default:
      throw ENPException("unkown node type in Exporter::toPov(Node *node, ...");
  }
  sst << "      }" << endl;
  sst << "      scale 1" << endl;
  sst << "      rotate <0, 0, 0>" << endl;
  sst << "      translate <0, 0, 0>" << endl;
  sst << "   }" << endl;
  return sst.str();
}

// string Exporter::toPov(Edge *edge, bool useHeader)
// {
  // stringstream sst;
  // if(useHeader) sst << __povHeader();
  // return sst.str();

// }

