#ifndef __FITNESS_H__
#define __FITNESS_H__

# define TAG_FITNESS            (char*)"fitness"
# define TAG_FITNESS_DEFINITION (char*)"fitness_definition"

#include "XsdParseNode.h"
#include "FitnessParameter.h"

#include <map>
#include <vector>
#include <string>

using namespace std;

class Fitness : public XsdParseNode, public std::vector<FitnessParameter*>
{
  public:
    Fitness(XsdParseNode *parent);
    virtual ~Fitness() { };

    static void createXsd(XsdSpecification *spec);
    void add(ParseElement *element);

    string module();
    string name();
    void setModule(string module);
    Fitness* copy();

    void resetTo(const Fitness *other);

    int frequency();
    void applySimulatorFrequency(int simFreq);

  protected:
    string _module;
    string _name;
};

#endif // __FITNESS_H__
