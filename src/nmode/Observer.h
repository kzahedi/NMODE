#ifndef __NMODE_OBSERVER_H__
#define __NMODE_OBSERVER_H__

#include <nmode/ObservableMessage.h>

class Observer
{
  public:
    virtual void notify(ObservableMessage *message) = 0;

};
#endif // __OBSERVER_H__
