
#include "DataNode.h"
#include "base/P3D.h"

#include <vector>

using namespace std;

# define TAG_EDGE            (char*)"edge"
# define TAG_EDGE_DEFINITION (char*)"population_module_edge_definition"

class DataPopulationModuleEdge : public DataNode
{
  public:
    DataPopulationModuleEdge(DataNode *parent);
    // ~DataPopulationModuleEdge();

    //DataPopulationModuleEdge(const DataPopulationModuleEdge);
    //DataPopulationModuleEdge operator=(const DataPopulationModuleEdge);

    void add(DataParseElement *element);
    static void createXsd(XsdSpecification *spec);

    string source();
    string destination();
    double weight();

  private:
    string _source;
    string _destination;
    double _weight;
};

typedef vector<DataPopulationModuleEdge*> DataPopulationModuleEdges;

#endif // __DATA__EDGE_H__
