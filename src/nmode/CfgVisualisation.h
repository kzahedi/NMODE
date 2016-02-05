#ifndef __VISUALISATION_H__
#define __VISUALISATION_H__

#include <nmode/XsdParseNode.h>

#include <string>

using namespace std;

# define TAG_VISUALISATION            (char*)"visualisation"
# define TAG_VISUALISATION_DEFINITION (char*)"visualisation_definition"

class CfgVisualisation : public XsdParseNode
{
  public:
    CfgVisualisation(XsdParseNode *parent);
    ~CfgVisualisation();

    void add(ParseElement *element);

    static void createXsd(XsdSpecification *spec);

    int offset();

  private:
    int _offset;
};


#endif // __VISUALISATION_H__
