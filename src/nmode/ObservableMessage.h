#ifndef __OBSERVABLE_MESSAGE_H__
#define __OBSERVABLE_MESSAGE_H__

#include <string>

# define __M_NEXT_GENERATION 10001
# define __M_QUIT            10002

class ObservableMessage
{
  public:
    ObservableMessage(std::string string, int type, int argument = 0)
    {
      _string = string;
      _type = type;
      _argument = argument;
    };

    std::string string()
    {
      return _string;
    };

    int type()
    {
      return _type;
    };

    int argument()
    {
      return _argument;
    };

    void setArgument(int argument)
    {
      _argument = argument;
    }

    static void deleteAllMessage()
    {
      // TODO
    };

  private:
    std::string _string;
    int _type;
    int _argument;
};

static ObservableMessage *_m_next_generation = new ObservableMessage("next generation", __M_NEXT_GENERATION);
static ObservableMessage *_m_quit            = new ObservableMessage("quit", __M_QUIT);

#endif // __OBSERVABLE_MESSAGE_H__
