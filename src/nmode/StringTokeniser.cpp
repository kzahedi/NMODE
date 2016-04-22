#include <nmode/StringTokeniser.h>

using namespace std;

// taken from http://www.digitalpeer.com/id/simple
std::vector<string> StringTokeniser::tokenise(const string& str, const string& delimiters)
{
  std::vector<string> tokens;
  string::size_type delimPos = 0, tokenPos = 0, pos = 0;

  if(str.length()<1)  return tokens;
  while(1){
    delimPos = str.find_first_of(delimiters, pos);
    tokenPos = str.find_first_not_of(delimiters, pos);

    if(string::npos != delimPos){
      if(string::npos != tokenPos){
        if(tokenPos<delimPos){
          tokens.push_back(str.substr(pos,delimPos-pos));
        }else{
          tokens.push_back("");
        }
      }else{
        tokens.push_back("");
      }
      pos = delimPos+1;
    } else {
      if(string::npos != tokenPos){
        tokens.push_back(str.substr(pos));
      } else {
        tokens.push_back("");
      }
      break;
    }
  }
  return tokens;
}

