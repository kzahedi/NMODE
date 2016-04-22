#ifndef __XSD_PARSE_NODE_H__
#define __XSD_PARSE_NODE_H__

#include <nmode/ParseElement.h>
#include <nmode/specification.h>

#include <string>
#include <ostream>
#include <iostream>

using namespace std;

/**
 * @brief Basic class for all objects that store XML data.
 */
class XsdParseNode
{
  public:

    /**
     * @brief Default constructor. Takes parent node as parameter
     *
     * @param parent
     */
    XsdParseNode(XsdParseNode *parent);

    /**
     * @brief Destructor, does nothing
     */
    ~XsdParseNode();

    /**
     * @brief This function must be implemented by every data storing class. It
     * takes a ParseElement and should decide if the contained data is
     * either stored, passed on to a child, or if the current node is set to the
     * parent.
     *
     * @param ParseElement
     * @sa ParseElement
     */
    virtual void add(ParseElement* ) = 0;

  protected:
    XsdParseNode        *parent;
    static XsdParseNode *current;
};

#endif // __XSD_NODE_H__
