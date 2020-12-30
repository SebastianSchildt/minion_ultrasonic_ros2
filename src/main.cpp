
#include <boost/chrono.hpp>
#include <iostream>

#include "measurement.hpp"

//Definition of Pin

int EchoPin = 30;             //Define the EchoPin connect to wiringPi port 30 of Raspberry pi 
int TrigPin = 31;             //Define the TrigPin connect to wiringPi port 31 of Raspberry pi 

USSMeasurement *sensor;

/** Ultrasonic test */
int main()
{

  sensor=new USSMeasurement(TrigPin,EchoPin);
  

  std::cout << "Ultrasonic test" << std::endl;
  while(1)
  {

  float d=sensor->getDistance();
  if (d == -1.0) {
    std::cout << "Out of range" << std::endl;
  }
  else {
    std::cout << "Thread Distance is " << sensor->getDistance()*100.0 << "cm " << std::endl;
  }

    boost::this_thread::sleep_for(boost::chrono::milliseconds{500});

  }
 return 0;
}

