#include "observer.hpp"

int main()
{
  Person* justin  = new Person("Justin");
  Person* brandon = new Person("Brandon");
  Person* sonny   = new Person("Sonny");
  Person* sophine = new Person("Sophine");

  Alarm alarm;
  alarm.AddObserver(justin);
  alarm.AddObserver(brandon);
  alarm.AddObserver(sonny);
  alarm.AddObserver(sophine);

  alarm.Fire();

  delete justin,
         brandon,
         sonny,
         sophine;

  return 0;
}
