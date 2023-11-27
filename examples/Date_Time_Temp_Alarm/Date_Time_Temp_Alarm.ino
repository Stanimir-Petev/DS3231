#include "DS3231.h"

DS3231 RTC;
int Century=20;

void setup()
{
  Serial.begin (115200);
  // Setup date, time, and 2 alarms to
  // 1999/12/31 (FRIDAY) 23:59:50
  //           YY  MM  DD   DOTW
  RTC.SetDate(99, 12, 31, FRIDAY);
  //           HH  MM  SS
  RTC.SetTime(23, 59, 50);
  //             HH  MM  SS     DD          Setting
  RTC.SetAlarm1( 0,  0,  5, SATURDAY, ALARM_EVERY_DOTW);
  //             HH  MM, DD,     Setting
  RTC.SetAlarm2( 0,  0,  1, ALARM_EVERY_DATE);
}

char OutputMessage[64];
void loop()
{
  RTC.UpdateData();

  if (RTC.CheckCentury())
  {
    Century++;
    printf ("New century!\r\n");
  }

  if (RTC.CheckAlarm1())
    printf ("Alarm 1 triggered!\r\n");

  if (RTC.CheckAlarm2())
    printf ("Alarm 2 triggered!\r\n");

  Serial.printf ("%2d/%2d/%2d (%s) %02d:%02d:%02d;  Temperature = ",
    (Century-1)*100+RTC.Year, RTC.Month, RTC.Date, DaysOfTheWeek[RTC.Day], RTC.Hours, RTC.Minutes, RTC.Seconds, RTC.Hours, RTC.Minutes);
  Serial.println (RTC.Temp);
  delay (1000);
}
