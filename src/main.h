#ifndef main_h
#define main_h

#include <Arduino.h>
#include <Eventually.h>
#include <LowPower.h>
#include <SoftwareSerial.h>

const short SHOW_TEMPORARILY_DURATION = 3000;
const byte TRANSMIT_PIN = 5;
const byte RECEIVE_PIN = 6;

const byte SHOW_PIN = 2;

const byte IDLE = 0;
const byte SENDING = 1;

EvtManager mgr;
StateMachineListener stateMachine;
SoftwareSerial bluetoothSerial(RECEIVE_PIN, TRANSMIT_PIN);

void onInterrupt();
bool idle();
bool sending();

#endif