#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <string>

using namespace std;

class Configuration
{
  public:
    Configuration(int argc, char* argv[], bool io = false);
    // ~Configuration();

    //Configuration(const Configuration);
    //Configuration operator=(const Configuration);

    string input();
    string output();
    string cfg();

  private:
    string _input;
    string _output;
    string _cfg;
    
};

#endif // __CONFIGURATION_H__
