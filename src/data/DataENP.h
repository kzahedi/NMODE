#ifndef __DATA_ENP_H__
#define __DATA_ENP_H__

#include "DataNode.h"

# define ENP                "enp"
# define TAG_ENP            (char*)ENP
# define TAG_ENP_DEFINITION (char*)ENP DIVIDER DEFINITION

class DataENP : public DataNode
{
  public:

    /**
     * @brief Constructor.
     *
     * @param parent
     */
    DataENP(DataNode *parent);

    /**
     * @brief Destructor.
     */
    virtual ~DataENP();

    void add(DataParseElement *element);

    static void createXsd(XsdSpecification *spec);

  private:

};

#endif // ___DATA_ENP_H__


