#include "io_test.h"

#include <nmode/RNN.h>
#include <nmode/NMODEException.h>
#include <nmode/Random.h>
#include <nmode/Data.h>

#include <iostream>

using namespace std;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( ioTest );

string types[]             = {"input", "output", "hidden"};
string transferfunctions[] = {"id", "sigm", "tanh"};


void ioTest::testIOModulesAndNeurons()
{

  Random::initialise();

  Data* data = Data::instance();

  Simulator*        simulator     = new Simulator(data->specification());
  CfgMutation*      mutation      = new CfgMutation(data->specification());
  CfgMutationNode*  node          = new CfgMutationNode(mutation);
  CfgMutationEdge*  edge          = new CfgMutationEdge(mutation);

  CfgEvaluation*    evaluation    = new CfgEvaluation(data->specification());
  Configuration*    configuration = new Configuration(data->specification());
  Population*       population    = new Population(data->specification());
  CfgReproduction*  reproduction  = new CfgReproduction(data->specification());
  CfgVisualisation* visualisation = new CfgVisualisation(data->specification());

  mutation->setNode(node);
  mutation->setEdge(edge);
  evaluation->setLifeTime(100);

  data->specification()->setSimulator(simulator);
  data->specification()->setCfgMutation(mutation);
  data->specification()->setCfgEvaluation(evaluation);
  data->specification()->setCfgVisualisation(visualisation);
  data->specification()->setPopulation(population);
  data->specification()->setCfgReproduction(reproduction);
  data->specification()->setConfiguration(configuration);


  vector<int> nr_of_modules_per_individial;

  vector<int>    nr_of_neurons_per_module;
  vector<string> neuron_types;
  vector<string> neuron_labels;
  vector<string> neuron_transferfunctions;
  vector<double> neuron_biasses;
  vector<P3D>    neuron_position;

  vector<int>    nr_of_synapses_per_module;
  vector<double> synapses_weights;
  vector<Node*>  synapses_srcs;
  vector<Node*>  synapses_dsts;

  Individual* individual = new Individual();
  int nr_of_modules = Random::randi(10,100);
  nr_of_modules_per_individial.push_back(nr_of_modules);

  stringstream sst;

  for(int i = 0; i < nr_of_modules; i++)
  {
    Module* m = new Module();
    individual->addModule(m);
    int nr_of_neurons  = Random::randi(10,100);
    for(int j = 0; j < nr_of_neurons; j++)
    {
      nr_of_neurons_per_module.push_back(nr_of_neurons);
      Node* node = new Node();

      // type
      int type = Random::randi(0,2);
      neuron_types.push_back(types[type]);
      node->setType(types[type]);

      // label
      sst.str("");
      sst << "node " << i << " " << j;
      neuron_labels.push_back(sst.str());
      node->setLabel(sst.str());

      // position
      P3D p(Random::unit(), Random::unit(), Random::unit());
      neuron_position.push_back(p);
      node->setPosition(p);

      // transfer function
      int tf = Random::randi(0,2);
      neuron_transferfunctions.push_back(transferfunctions[tf]);
      node->setTransferfunction(transferfunctions[tf]);

      // bias
      double bias = Random::unit();
      neuron_biasses.push_back(bias);
      node->setBias(bias);

      m->addNode(node);
    }


    int nr_of_synapses = Random::randi(5,10);
    nr_of_synapses_per_module.push_back(nr_of_synapses);
    for(int j = 0; j < nr_of_synapses; j++)
    {
      bool ok       = false;
      int src_index = -1;
      int dst_index = -1;
      Node* src     = NULL;
      Node* dst     = NULL;

      while(ok == false)
      {
        src_index = Random::randi(0, nr_of_neurons-1);
        src = m->node(src_index);

        dst_index = Random::randi(0, nr_of_neurons-1);
        dst = m->node(dst_index);

        if(m->edgeExists(src, dst)) ok = false;
        else                        ok = true;
      }
      double  w = Random::unit();
      m->addEdge(src, dst, w);
      synapses_srcs.push_back(src);
      synapses_dsts.push_back(dst);
      synapses_weights.push_back(w);
    }
    individual->addModule(m);
  }

  population->addIndividual(individual);

  string xml = data->xml();
  ofstream output;
  output.open("io_test.xml");
  output << xml << endl;
  output.close();

  data->read("io_test.xml");
  int index = 0;

  Individual* read_individual = data->specification()->population()->individual(0);

  CPPUNIT_ASSERT(read_individual->equal(individual));

}
