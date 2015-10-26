#ifndef __NMODE_ERROR_HANDLER_H__
#define __NMODE_ERROR_HANDLER_H__

#include <string>
#include <sstream>

using namespace std;

class NMODEErrorHandler : public stringstream
{
  public:
    static NMODEErrorHandler* instance();

    static void push();
    static void push(const char *string, ...);
    static void push(string message);

    string message();

  private:
    NMODEErrorHandler();

    static NMODEErrorHandler *_me;

};
#endif // __NMODE_ERROR_HANDLER_H__
