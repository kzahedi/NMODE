#ifndef __OBSERVER_H__
#define __OBSERVER_H__

#include "ObservableMessage.h"

class Observer
{
  public:
    virtual void notify(ObservableMessage *message) = 0;

};
#endif // __OBSERVER_H__
