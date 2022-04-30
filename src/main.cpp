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

  stateMachine.transition(IDLE);

  stateMachine.when(IDLE, (EvtAction)idle);
  stateMachine.when(SENDING, (EvtAction)sending, IDLE);

  stateMachine.whenInterrupted(IDLE, SENDING);

  mgr.addListener(&stateMachine);

  attachInterrupt(digitalPinToInterrupt(SHOW_PIN), onInterrupt, FALLING);

  Serial.println(F("Setup complete. Continuing..."));
}

bool idle()
{
  Serial.println(F("Sleeping..."));
  Serial.flush();
  LowPower.idle(SLEEP_FOREVER, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF,
                SPI_OFF, USART0_OFF, TWI_OFF);
  return true;
}

bool sending()
{
  Serial.println(F("Sending command..."));

  bluetoothSerial.println(F(">show!"));

  return true;
}

void loop()
{
  mgr.loopIteration();
}

void onInterrupt()
{
  stateMachine.onInterrupt();
}