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
const byte PENDING = 1;
const byte IN_PROGRESS = 2;

volatile byte state = IDLE;
volatile byte *pState = &state;

EvtManager mgr;
SoftwareSerial bluetoothSerial(RECEIVE_PIN, TRANSMIT_PIN);

EvtByteListener *showTemporarilyListener;
EvtTimeListener *returnToNormalListener;
EvtByteListener *sleepListener;

void setState(byte state);
void wakeup();
bool sleep();
bool showTemporarily();
bool returnToNormal();

#endif