#include "Exporter.h"

#include <sstream>
#include <math.h>

#include "base/macros.h"


string Exporter::toXml(Module *m)
{
  stringstream sst;
  sst << "      <module name=\"" << m->name() << "\">" << endl;
  for(Nodes::const_iterator n = m->n_begin(); n != m->n_end(); n++)
  {
    sst << "        <node type=\"" << (*n)->stype()
      << "\" label=\"" << (*n)->label() << "\">" << endl;
    sst << "          <position x=\"" << (*n)->position().x
      << "\" y=\"" << (*n)->position().y
      << "\" z=\"" << (*n)->position().z
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

string Exporter::__x3dHeader()
{
  stringstream sst;
  sst << endl;
  sst << "<html> " << endl;
  sst << "  <head> " << endl;
  sst << "    <title>My first X3DOM page</title>      " << endl;
  sst << "    <script type='text/javascript' src='http://www.x3dom.org/download/x3dom.js'> </script> " << endl;
  sst << "    <link rel='stylesheet' type='text/css' href='http://www.x3dom.org/download/x3dom.css'></link> " << endl;
  sst << "  </head> " << endl;
  sst << "  <body> " << endl;
  sst << "    <center>" << endl;
  return sst.str();
}

string Exporter::__x3dFooter()
{
  stringstream sst;
  sst << "      </x3d> " << endl;
  sst << "    </center>" << endl;
  sst << "  </body> " << endl;
  sst << "</html>    " << endl;
  return sst.str();
}

string Exporter::toX3d(Individual *i)
{
  stringstream sst;
  sst << __x3dHeader();
  sst << "      <p> " << endl;
  sst << "        Individual " << i->id() << " with fitness " << i->fitness() << endl;
  sst << "      </p> " << endl;
  sst << "      <x3d width='1000px' height='800px'> " << endl;
  sst << "      <scene> " << endl;

  for(Modules::const_iterator m = i->m_begin(); m != i->m_end(); m++) sst << toX3d(*m);

  sst << "      </scene> " << endl;
  sst << __x3dFooter();
  return sst.str();
}

string Exporter::toX3d(Module *m)
{
  stringstream sst;
  for(Nodes::const_iterator n = m->n_begin(); n != m->n_end(); n++) sst << toX3d(*n);
  for(Edges::const_iterator e = m->e_begin(); e != m->e_end(); e++) sst << toX3d(*e);
  // for(Edges::const_iterator e = m->e_begin(); e != m->e_end(); e++)
  // {
    // sst << "        <edge source=\"" << (*e)->source()->label()
      // << "\" destination=\"" << (*e)->destination()->label() << "\" weight=\""
      // << (*e)->weight()<< "\"/>" << endl;
  // }
  // sst << "      </module>" << endl;
  return sst.str();
}

string Exporter::toX3d(Node *n)
{
  stringstream sst;

  sst << "    <transform translation='"
    << n->position().x << " "
    << n->position().y << " "
    << n->position().z << "'>" << endl;
  sst << "    <shape> " << endl;
  sst << "        <appearance> " << endl;
  switch(n->type())
  {
    case NODE_TYPE_SENSOR:
      sst << "        <material diffuseColor='1 0 0'></material> " << endl;
      break;
    case NODE_TYPE_ACTUATOR:
      sst << "        <material diffuseColor='0 1 0'></material> " << endl;
      break;
    case NODE_TYPE_HIDDEN:
      sst << "        <material diffuseColor='0 0 1'></material> " << endl;
      break;
    case NODE_TYPE_INPUT:
      sst << "        <material diffuseColor='0.98 0.81 0'></material> " << endl;
      break;
    case NODE_TYPE_OUTPUT:
      sst << "        <material diffuseColor='0.98 0.41 0'></material> " << endl;
      break;
    default:
      throw ENPException("unkown node type in Exporter::toPov(Node *node, ...");
  }

  sst << "        </appearance> " << endl;
  sst << "        <sphere radius='0.1'></sphere> " << endl;
  sst << "    </shape> " << endl;
  sst << "    </transform> " << endl;

  // sst << "    <transform translation='"
    // << n->position().x << " "
    // << n->position().y << " "
    // << n->position().z << "'>" << endl;
  // sst << "    <shape> " << endl;
  // sst << "        <appearance> " << endl;
  // sst << "          <material diffuseColor='1 0 0'></material> " << endl;
  // sst << "        </appearance> " << endl;
  // sst << "      <cylinder radius='0.01' height='0.5'></cylinder> " << endl;
  // sst << "    </shape> " << endl;
  // sst << "    </transform> " << endl;

  // sst << "    <transform translation='"
    // << n->position().x << " "
    // << n->position().y << " "
    // << n->position().z << "'>" << endl;
  // sst << "    <transform rotation='0 0 1 1.5'>" << endl;
  // sst << "    <shape> " << endl;
  // sst << "        <appearance> " << endl;
  // sst << "          <material diffuseColor='1 0 0'></material> " << endl;
  // sst << "        </appearance> " << endl;
  // sst << "      <cylinder radius='0.01' height='0.5'></cylinder> " << endl;
  // sst << "    </shape> " << endl;
  // sst << "    </transform> " << endl;
  // sst << "    </transform> " << endl;

  return sst.str();
}

string Exporter::toX3d(Edge *e)
{
  stringstream sst;

  Node *src     = e->source();
  Node *dst     = e->destination();

  P3D psrc      = src->position();
  P3D pdst      = dst->position();

  P3D dir       = pdst - psrc;
  double length = DIST(psrc, pdst) - 0.2;

  // TODO: self connection
  if(dir.length() < 0.00001) return "";

  P3D v(0.0, 1.0, 0.0);
  P3D cross  = v * dir;
  double dot = v.dot(dir);
  double angle = acos(dot / (v.length() * dir.length()));

  P3D centre = (psrc + pdst) * 0.5;

  sst << "    <transform translation='" << centre.x << " " << centre.y << " " << centre.z << "'>"
      << endl;
  sst << "      <transform rotation='" << cross.x << " " << cross.y << " " << cross.z << " "
      << angle << "'>" << endl;
  sst << "        <shape> " << endl;
  sst << "            <appearance> " << endl;
  if(e->weight() < 0.0)
  {
    sst << "              <material diffuseColor='1 0 0'></material> " << endl;
  }
  else
  {
    sst << "              <material diffuseColor='0 0 1'></material> " << endl;
  }

  sst << "            </appearance> " << endl;
  sst << "          <cylinder radius='0.0125' height='" << length << "'></cylinder> " << endl;
  sst << "        <shape> " << endl;
  sst << "      </transform>" << endl;
  sst << "    </transform>" << endl;


  // switch(n->type())
  // {
    // case NODE_TYPE_SENSOR:
      // sst << "        <material diffuseColor='1 0 0'></material> " << endl;
      // break;
    // case NODE_TYPE_ACTUATOR:
      // sst << "        <material diffuseColor='0 1 0'></material> " << endl;
      // break;
    // case NODE_TYPE_HIDDEN:
      // sst << "        <material diffuseColor='0 0 1'></material> " << endl;
      // break;
    // case NODE_TYPE_INPUT:
      // sst << "        <material diffuseColor='0.98 0.81 0'></material> " << endl;
      // break;
    // case NODE_TYPE_OUTPUT:
      // sst << "        <material diffuseColor='0.98 0.41 0'></material> " << endl;
      // break;
    // default:
      // throw ENPException("unkown node type in Exporter::toPov(Node *node, ...");
  // }

  // sst << "        </appearance> " << endl;
  // sst << "        <sphere radius='0.1'></sphere> " << endl;
  // sst << "    </shape> " << endl;
  // sst << "    </transform> " << endl;
  return sst.str();

}