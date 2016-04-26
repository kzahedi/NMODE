#ifndef __NMODE_EVALUATION_PARAMETER_MAP_H__
#define __NMODE_EVALUATION_PARAMETER_MAP_H__

#include <map>
#include <string>
#include <vector>
#include <cstdlib>
#include <string.h>

using namespace std;

class EvaluationParameterMap : public map<string,string>
{
  public:
    bool exists(const string &key)
    {
      map<string,string>::iterator iter = find(key);

      if( iter != end() )
      {
        return true;
      }
      else
      {
        return false;
      }
    };

    void add(string name, string value)
    {
      insert(std::make_pair(name, value));
    }

    void get(string name, string *value)
    {
      map<string,string>::iterator iter;
      iter = find(name);

      if( iter != end() )
      {
        *value = iter->second;
      }
      else
      {
        *value = "";
      }
    }

    int intValue(string name)
    {
      string s;
      get(name, &s);
      return atoi(s.c_str());
    }

    vector<int> intList(string name)
    {
      vector<int> lst;
      string s;
      get(name, &s);
      char *str = (char*)s.c_str();
      char *pch = strtok (str," ,.-");
      while (pch != NULL)
      {
        lst.push_back(atoi(pch));
        pch = strtok (NULL, " ,.-");
      }
      return lst;
    }

    vector<double> doubleList(string name)
    {
      vector<double> lst;
      string s;
      get(name, &s);
      char *str = (char*)s.c_str();
      char *pch = strtok (str," ,.-");
      while (pch != NULL)
      {
        lst.push_back(atof(pch));
        pch = strtok (NULL, " ,.-");
      }
      return lst;
    }

    double doubleValue(string name)
    {
      string s;
      get(name, &s);
      return atof(s.c_str());
    }

    string stringValue(string name)
    {
      string s;
      get(name, &s);
      return s;
    }

    bool boolValue(string name)
    {
      string s;
      get(name, &s);
      return (s == "true");
    }

    std::vector<string> names()
    {
      std::vector<string> names;
      for(EvaluationParameterMap::const_iterator i = begin(); i != end(); i++)
      {
        names.push_back(i->first);
      }
      return names;
    }

    void set(string name, double &value, double def)
    {
      if(exists(name)) value = doubleValue(name);
      else             value = def;
    }

    void set(string name, bool &value, bool def)
    {
      if(exists(name)) value = boolValue(name);
      else             value = def;
    }

    void set(string name, int &value, int def)
    {
      if(exists(name)) value = intValue(name);
      else             value = def;
    }

    void set(string name, string &value, string def)
    {
      if(exists(name)) value = stringValue(name);
      else             value = def;
    }

    friend std::ostream& operator<<(std::ostream& str, const EvaluationParameterMap& p)
    {
      str << "Robot Controller Parameter given: " << endl;
      for(EvaluationParameterMap::const_iterator i = p.begin(); i != p.end(); i++)
      {
        str << "  " << i->first << " = " << i->second << endl;
      }
      return str;
    };


};

#endif // __EVALUATION_PARAMETER_MAP_H__


