#ifndef __NMODE_OBSERVABLE_H__
#define __NMODE_OBSERVABLE_H__

#include <nmode/Observer.h>
#include <nmode/ObservableMessage.h>

#include <list>

class Observable
{
    public:
       void addObserver(Observer* o)
       {
         observers.push_back(o);
       };

       void removeObserver(Observer* o)
       {
         observers.remove(o);
       };

       void notifyObservers(ObservableMessage *message)
       {
         for (std::list<Observer*>::iterator iterator = observers.begin();
              iterator != observers.end();
              iterator++ )
         {
           (*iterator)->notify(message);
         }
       };

    protected:
       std::list<Observer*> observers;

};

#endif // __OBSERVABLE_H__
