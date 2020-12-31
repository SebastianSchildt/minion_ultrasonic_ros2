

#ifndef __MEASUREMENT_HPP__
#define __MEASUREMENT_HPP__

#include <boost/thread.hpp>
#include <stdint.h>
 

class USSMeasurement {
    public:
        USSMeasurement(uint32_t trig_pin, int32_t echo_pin);
        ~USSMeasurement();

        float getDistance();
    private:
        boost::thread *t;
        boost::mutex mutex;
        int64_t value_us; //Measurement in microseconds
        void sample(void);
        void sampleThread(void);
        bool running;
        uint32_t _trig_pin, _echo_pin;
};

#endif