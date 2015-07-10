#ifndef __ENP_ERROR_HANDLER_H__
#define __ENP_ERROR_HANDLER_H__

#include <string>
#include <sstream>

using namespace std;

class ENPErrorHandler : public stringstream
{
  public:
    static ENPErrorHandler* instance();

    static void push();
    static void push(const char *string, ...);
    static void push(string message);

    string message();

  private:
    ENPErrorHandler();

    static ENPErrorHandler *_me;

};
#endif // __ENP_ERROR_HANDLER_H__
