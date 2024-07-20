#include <time_keeper.h>

void TimeKeeper::moveForward(int days) {}

void TimeKeeper::moveBackward(int days) {}

String TimeKeeper::getFormattedDate() {
  m5::rtc_date_t date;
  M5.Rtc.getDate(&date);
  String year = String(date.year);
  String month = String(date.month);
  String day = String(date.date);
  return " < " + year + "." + month + "." + day + " >";
}

String TimeKeeper::getFormattedTime() { return ""; }

TimeKeeper timeKeeper;
