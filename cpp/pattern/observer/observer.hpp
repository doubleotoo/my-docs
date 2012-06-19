#ifndef OBSERVER_HPP___
#define OBSERVER_HPP___

#include <assert.h>

#include <iostream>
#include <list>
#include <string>

struct EventData
{
  std::string name;
};

class Observer
{
  public:
    Observer() {}
    virtual void Respond(const EventData& event) = 0;
};

class Event
{
  public:
    explicit Event(std::string name)
      : name_(name)
    {}

    explicit Event(const char* name)
    {
      assert(name != NULL);
      name_.assign(name);
    }

    virtual ~Event() {}

    virtual void Fire()
    {
      std::cout << "[" << name_ << "] firing event!" << std::endl;

      EventData event;
      event.name = name_;

      ObserverList::iterator it = observers_.begin();
      for ( ; it != observers_.end(); ++it)
      {
        (*it)->Respond(event);
      }
    }

    void AddObserver(Observer* observer)
    {
      observers_.push_back(observer);
    }

  protected:
    typedef std::list<Observer*> ObserverList;
    std::list<Observer*> observers_;

  private:
    std::string name_;
};

class Alarm : public Event
{
  public:
    Alarm()
      : Event("Alarm")
    {}
    virtual ~Alarm() {}
};

class Person : public Observer
{
  public:
    explicit Person(std::string& name)
      : name_(name)
    {}

    explicit Person(const char* name)
    {
      assert(name != NULL);
      name_.assign(name);
    }

    virtual void Respond(const EventData& event)
    {
      std::cout
        << "[Person] [" << name_ << "] "
        << "responding to " << event.name << " event!"
        << std::endl;
    }
  private:
    std::string name_;
};

#endif // OBSERVER_HPP___
