#include "main.h"

void setup()
{
  Serial.begin(115200);

  pinMode(RECEIVE_PIN, INPUT);
  pinMode(TRANSMIT_PIN, OUTPUT);
  bluetoothSerial.begin(9600);

  pinMode(SHOW_PIN, INPUT_PULLUP);

  while (!Serial)
    ;

  sleepListener = new EvtByteListener(pState, IDLE, (EvtAction)sleep);
  mgr.addListener(sleepListener);

  showTemporarilyListener = new EvtByteListener(pState, PENDING, (EvtAction)showTemporarily);
  mgr.addListener(showTemporarilyListener);

  returnToNormalListener = new EvtTimeListener(SHOW_TEMPORARILY_DURATION, true, (EvtAction)returnToNormal);
  returnToNormalListener->disable();
  mgr.addListener(returnToNormalListener);

  attachInterrupt(digitalPinToInterrupt(SHOW_PIN), wakeup, LOW);

  Serial.println(F("Setup complete. Continuing..."));
}

void loop()
{
  mgr.loopIteration();
}

void wakeup()
{
  if (state == IDLE)
  {
    setState(PENDING);
  }
}

bool sleep()
{
  Serial.println(F("Sleeping..."));
  Serial.flush();
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_OFF, TWI_OFF);
  return true;
}

void setState(byte newState)
{
  Serial.print(F("Setting state: "));
  switch (newState)
  {
  case PENDING:
    Serial.println(F("PENDING"));
    break;
  case IN_PROGRESS:
    Serial.println(F("IN_PROGRESS"));
    break;
  case IDLE:
    Serial.println(F("IDLE"));
    break;
  }
  state = newState;
}

bool showTemporarily()
{
  Serial.println(F("Showing temporarily..."));
  setState(IN_PROGRESS);

  bluetoothSerial.println(F(">show!"));

  returnToNormalListener->enable();

  return true;
}

bool returnToNormal()
{
  Serial.println(F("Returning to normal..."));
  returnToNormalListener->disable();

  setState(IDLE);

  return true;
}
