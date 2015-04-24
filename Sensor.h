/* Ultrasonic sensor - vibration motor class
	consult accompanying implementation for comment details
*/
#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>

class Sensor
{
    private:
        String _sensorName;
        int _trigpin, _echopin, _motorpin;
        float _distance;
        int _range_modulo;
	int _range_audio;

    public:
	Sensor (String sensorName, int trigpin, int echopin, int motorpin);
        Sensor (String sensorName, int trigpin, int echopin);

        //helpers
        void show();
        void toggle();
        void run_motor(int intensity);

        //getters
        String Get_sensorName() { return _sensorName; }
        int Get_trigpin() { return _trigpin; }
        int Get_echopin() { return _echopin; }
        int Get_motorpin() { return _motorpin; }
        float Get_distance() { return _distance; }
        int Get_range_modulo() { return _range_modulo; }
	int Get_range_audio() { return _range_audio; }
};

#endif // SENSOR_H
