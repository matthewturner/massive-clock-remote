#include "main.h"

void setup()
{
  Serial.begin(115200);

  pinMode(RECEIVE_PIN, INPUT);
  pinMode(TRANSMIT_PIN, OUTPUT);
  bluetoothSerial.begin(115200);

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

  Serial.println("Setup complete. Continuing...");
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
  Serial.println("Sleeping...");
  Serial.flush();
  LowPower.idle(SLEEP_8S, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_OFF, TWI_OFF);
  return true;
}

void setState(byte newState)
{
  Serial.print("Setting state: ");
  switch (newState)
  {
  case PENDING:
    Serial.println("PENDING");
    break;
  case IN_PROGRESS:
    Serial.println("IN_PROGRESS");
    break;
  case IDLE:
    Serial.println("IDLE");
    break;
  }
  state = newState;
}

bool showTemporarily()
{
  Serial.println("Showing temporarily...");
  setState(IN_PROGRESS);

  bluetoothSerial.println(">show!");

  returnToNormalListener->enable();

  return true;
}

bool returnToNormal()
{
  Serial.println("Returning to normal...");
  returnToNormalListener->disable();

  setState(IDLE);

  return true;
}
