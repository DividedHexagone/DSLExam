#include <Arduino.h>
#include "LiquidCrystal_I2C.h"

LiquidCrystal_I2C LCD(0x27, 20, 4);
uint8_t LastChannel = 1;
uint8_t RSSI = 0;
uint8_t RSSI_UPDATE = 0;

bool Channels[8][4] =
{
    {1, 0, 0, 0}, // 1080
    {1, 0, 0, 1}, // 1120
    {1, 0, 1, 0}, // 1160
    {1, 0, 1, 1}, // 1200
    {1, 1, 0, 0}, // 1240
    {1, 1, 0, 1}, // 1280
    {1, 1, 1, 0}, // 1320
    {1, 1, 1, 1}, // 1360
};

String ChannelNames[8] = 
{
  "1G2-1080",
  "1G2-1120",
  "1G2-1160",
  "1G2-1200",
  "1G2-1240",
  "1G2-1280",
  "1G2-1320",
  "1G2-1360",
};

void update_channel()
{
  for(uint8_t i = 0; i < 4; ++i)
  {
    //Exam A - Solve the problem
  }
}

void update_rssi() 
{
    int rssiAccumulator = 0;
    for(uint8_t i = 0; i < 8; ++i) rssiAccumulator += analogRead(A2);
    rssiAccumulator /= 8;

    RSSI = (log(rssiAccumulator + 1) / log(930 + 1)) * 100.0;
}

void setup()
{
  LCD.init();
  LCD.backlight();

  for(uint8_t i = 0; i < 4; ++i)
  {
    pinMode(2+i, OUTPUT);
  }

  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
}

void loop()
{
  uint8_t channel = map(analogRead(A0), 0, 1024, 0, 8);

  if(channel != LastChannel)
  {
    LastChannel = channel;
    update_channel();

    LCD.clear();
    LCD.setCursor(0,0);
    LCD.print("CHANNEL:"+ChannelNames[LastChannel]);
  }

  if(RSSI_UPDATE == 0) update_rssi();
  RSSI_UPDATE = (RSSI_UPDATE+1)%60;

  LCD.setCursor(0,1);
  LCD.print("RSSI:"+String(RSSI)+"%   ");
}