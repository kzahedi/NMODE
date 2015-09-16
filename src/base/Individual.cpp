#include "Individual.h"

#include "glog/logging.h"

#include "base/macros.h"

#define TAG_ID        (char*)"id"
#define TAG_FITNESS   (char*)"fitness"
#define TAG_OFFSPRING (char*)"offspring"
#define TAG_CONNECTOR (char*)"connector"

Individual::Individual(XsdParseNode *parent)
  : XsdParseNode(parent)
{
  _id        = 1;
  _fitness   = 0.0;
  _offspring = 0;
}

void Individual::add(DataParseElement *element)
{
  VLOG(100) << "parsing " << element->name();

  if(element->closing(TAG_INDIVIDUAL))
  {
    // __linkConnectorNodes();
    VLOG(100) << "closing " << element->name();
    current = parent;
  }

  if(element->opening(TAG_INDIVIDUAL))
  {
    element->set(TAG_ID,        _id);
    element->set(TAG_FITNESS,   _fitness);
    element->set(TAG_OFFSPRING, _offspring);
    VLOG(100) << "setting id = " << _id << " fitness = " << _fitness << " offspring = " << _offspring;
  }

  if(element->opening(TAG_MODULE))
  {
    Module *dpm = new Module(this);
    _modules.push_back(dpm);
    current = dpm;
    current->add(element);
  }
}

void Individual::createXsd(XsdSpecification *spec)
{
  XsdSequence *_root = new XsdSequence(TAG_INDIVIDUAL_DEFINITION);
  _root->add(NA(TAG_ID,        TAG_POSITIVE_INTEGER,  false));
  _root->add(NA(TAG_FITNESS,   TAG_XSD_DECIMAL,       false));
  _root->add(NA(TAG_OFFSPRING, TAG_POSITIVE_INTEGER,  false));
  _root->add(NE(TAG_MODULE,    TAG_MODULE_DEFINITION, 1, TAG_XSD_UNBOUNDED));
  spec->add(_root);

  Module::createXsd(spec);
}

int Individual::id()
{
  return _id;
}

double Individual::fitness()
{
  return _fitness;
}

int Individual::offspring()
{
  return _offspring;
}

Modules::iterator Individual::m_begin()
{
  return _modules.begin();
}

Modules::iterator Individual::m_end()
{
  return _modules.end();
}

int Individual::m_size()
{
  return _modules.size();
}

Modules Individual::modules()
{
  return _modules;
}

void Individual::setFitness(double f)
{
  _fitness = f;
}
void Individual::setId(int id)
{
  _id = id;
}



// void Individual::__linkConnectorNodes()
// {
//   VLOG(100) << "  __linkConnectorNodes called with " << _modules.size() << " modules";
//   FORC(Modules, a, _modules)
//   {
//     VLOG(100) << "working on module " << (*a)->name() << " with " << (*a)->n_size() << " nodes";
//     FORC(ModuleNodes, an, (*a)->nodes())
//     {
//       VLOG(100) << " node " << (*an);
//       VLOG(100) << " node type is " << (*an)->type() << " vs. " << TAG_CONNECTOR;
//       if((*an)->type() == TAG_CONNECTOR)
//       {
//         string label          = (*an)->label();
//         string::size_type pos = label.find('/');
//         string module_name    = label.substr(0, pos);
//         string node_name      = label.substr(pos+1, label.size()-1);
//         FORC(Modules, b, _modules)
//         {
//           if((*b)->name() == module_name)
//           {
//             FORC(ModuleNodes, bn, (*b)->nodes())
//             {
//               if((*bn)->type() != TAG_CONNECTOR && (*bn)->label() == node_name)
//               {
//                 VLOG(100) << "setting position of " << (*an)->label() << " to "
//                           << (*an)->position() << " from " << (*bn)->label()
//                           << " which has " << (*bn)->position();
//                 VLOG(100) << "setting transferfunction of " << (*an)->label()
//                           << " to " << (*an)->transferfunction() << " from "
//                           << (*bn)->label() << " which has " << (*bn)->position();
//                 (*an)->setPosition((*bn)->position());
//                 (*an)->setTransferfunction((*bn)->transferfunction());
//               }
//             }
//           }
//         }
//       }
//     }
//   }
// }