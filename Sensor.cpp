#include "Sensor.h"

// constructor/initialization of class
Sensor::Sensor(String sensorName, int trigpin, int echopin, int motorpin){
    _sensorName = sensorName;
    _trigpin = trigpin;
    _echopin = echopin;
    _motorpin = motorpin;
    _distance = 0;
    _range_modulo = -1;
	_range_audio = -1;
	pinMode(_trigpin, OUTPUT);
	pinMode(_echopin, INPUT);
	pinMode(_motorpin, OUTPUT);
}

// overloading of constructor
Sensor::Sensor(String sensorName, int trigpin, int echopin){
    _sensorName = sensorName;
    _trigpin = trigpin;
    _echopin = echopin;
    _motorpin = -1;
    _distance = 0;
    _range_modulo = -1;
	_range_audio = -1;
	pinMode(_trigpin, OUTPUT);
	pinMode(_echopin, INPUT);
}

//prints certain attributes, for troubleshooting
void Sensor::show(){
	Serial.print(_sensorName);
	Serial.print(" ");
    Serial.print(_distance);
	Serial.print(" ");
	Serial.print(_range_modulo);
	Serial.println();
}

//pings sensors, activates the trigger and echo pins to determine distance
void Sensor::toggle(){
	float temp_dist = _distance;
	float new_dist = 0;

	digitalWrite(_trigpin, LOW);
	digitalWrite(_trigpin, HIGH);
	digitalWrite(_trigpin, LOW);
	new_dist = pulseIn(_echopin, HIGH) / 28.26585 / 2;

	// filters transient events such as open space detections
	if (!((temp_dist > 1500) && (new_dist < 50))){
        	_distance = new_dist;
	}

	_range_modulo = _distance / 100;
	_range_audio = _distance / 50;
}

// activates vibration motors
void Sensor::run_motor (int intensity) {
    switch (_range_modulo){
    case 0:
        analogWrite(_motorpin, intensity);
        break;
    case 1:
        analogWrite(_motorpin, intensity);
        delay(250);
        analogWrite(_motorpin, 0);
        delay(125);
        break;
    case 2:
        analogWrite(_motorpin, intensity);
        delay(50);
        analogWrite(_motorpin, intensity);
        delay(50);
        analogWrite(_motorpin, 0);
        delay(125);
        break;
    default:
        analogWrite(_motorpin, 0);
    }
}