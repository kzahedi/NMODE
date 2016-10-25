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

  int nr_of_individuals = Random::randi(10,30);
  for(int l = 0; l < nr_of_individuals; l++)
  {
    Individual* individual = new Individual();
    int nr_of_modules = Random::randi(10,100);
    population->addIndividual(individual);

    stringstream sst;

    for(int i = 0; i < nr_of_modules; i++)
    {
      Module* m = new Module();
      individual->addModule(m);
      int nr_of_neurons  = Random::randi(10,100);
      for(int j = 0; j < nr_of_neurons; j++)
      {
        Node* node = new Node();

        // type
        int type = Random::randi(0,2);
        node->setType(types[type]);

        // label
        sst.str("");
        sst << "node " << i << " " << j;
        node->setLabel(sst.str());

        // position
        P3D p(Random::unit(), Random::unit(), Random::unit());
        node->setPosition(p);

        // transfer function
        int tf = Random::randi(0,2);
        node->setTransferfunction(transferfunctions[tf]);

        // bias
        double bias = Random::unit();
        node->setBias(bias);

        m->addNode(node);
      }

      int nr_of_synapses = Random::randi(5,10);
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
      }
      individual->addModule(m);
    }
  }

  string xml = data->xml();
  ofstream output;
  output.open("io_test.xml");
  output << xml << endl;
  output.close();

  data->read("io_test.xml");
  int index = 0;

  for(int i = 0; i < nr_of_individuals; i++)
  {
    Individual* individual      = population->individual(i);
    Individual* read_individual = data->specification()->population()->individual(i);
    CPPUNIT_ASSERT(read_individual->equal(individual));
  }

  xml = data->xml();
  output.open("io_test_2.xml");
  output << xml << endl;
  output.close();

  ifstream first("io_test.xml");
  stringstream firstsst;
  firstsst << first.rdbuf();

  ifstream second("io_test_2.xml");
  stringstream secondsst;
  secondsst << second.rdbuf();

  CPPUNIT_ASSERT_EQUAL(firstsst.str(), secondsst.str());
}

void ioTest::testAgain1() { testIOModulesAndNeurons(); }
void ioTest::testAgain2() { testIOModulesAndNeurons(); }
void ioTest::testAgain3() { testIOModulesAndNeurons(); }
void ioTest::testAgain4() { testIOModulesAndNeurons(); }
void ioTest::testAgain5() { testIOModulesAndNeurons(); }
void ioTest::testAgain6() { testIOModulesAndNeurons(); }
void ioTest::testAgain7() { testIOModulesAndNeurons(); }
void ioTest::testAgain8() { testIOModulesAndNeurons(); }
void ioTest::testAgain9() { testIOModulesAndNeurons(); }

void ioTest::tearDown()
{
  remove("io_test.xml");
  remove("io_test_2.xml");
}
