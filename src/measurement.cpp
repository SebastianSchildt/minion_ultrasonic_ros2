


#include "measurement.hpp"
#include <iostream>
#include <boost/chrono.hpp>
#include <wiringPi.h>


USSMeasurement::USSMeasurement(uint32_t trig_pin, int32_t echo_pin) :  _trig_pin(trig_pin), _echo_pin(echo_pin) {
    std::cout << "Constructed" << std::endl;
    wiringPiSetup();
    pinMode(this->_echo_pin, INPUT);    
    pinMode(this->_trig_pin, OUTPUT);
    running=true;
    this->t = new boost::thread(&USSMeasurement::sampleThread,this);
}

USSMeasurement::~USSMeasurement() {
    this->running=false;
    this->t->join();
}


void USSMeasurement::sample() {
      boost::this_thread::sleep_for(boost::chrono::milliseconds{300});

	
    /** Do the pulse */
	digitalWrite(this->_trig_pin, LOW); //make sure pin is low
	delayMicroseconds(2);
	digitalWrite(this->_trig_pin, HIGH);       //Input a high level of at least 10 US to the Trig pin
	delayMicroseconds(15);
	digitalWrite(this->_trig_pin, LOW);
    

    //Wait for echo pulse, todo timeout
    while( digitalRead(this->_echo_pin) == 0) { //Do not hog CPU, accept slightly less precise results
          boost::this_thread::sleep_for(boost::chrono::microseconds{1});
    }
    //high pulse coming back
    auto t1=boost::chrono::steady_clock::now();
    //

    // wait pulse to go low
	while( digitalRead(this->_echo_pin) == 1) { //Do not hog CPU, accept slightly less precise results
          boost::this_thread::sleep_for(boost::chrono::microseconds{1});
    }

    auto t2=boost::chrono::steady_clock::now();
    int64_t f = boost::chrono::duration_cast<boost::chrono::microseconds>(t2-t1).count();
    //std::cout << "Delay is " << f << "us " << std::endl;

    if ( f < 0) { //Delay < zero is an error measurement
        this->value_us=0;
    }
    

   this->mutex.lock();
   this->value_us = double(f);
   this->mutex.unlock();
}



void USSMeasurement::sampleThread() {
  while (this->running)
  {
    this->sample();
  }
  std::cout << "Thread Done" << std::endl;
}

//return distance in meters
float USSMeasurement::getDistance() {
    float distance;
    this->mutex.lock();
    distance=this->value_us/1e6*343.0;
    if (distance > 1.0) { //Measurement < 1m not reliable
        //std::cout << "Distance: " << distance << "m. Nothing in range" << std::endl;
        distance=-1;
    }
    this->mutex.unlock();
    return distance;
}