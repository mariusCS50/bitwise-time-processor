#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timelib.h"

#define minToSec 60
#define hourToSec (60 * 60)
#define dayToSec (24 * 60 * 60)
#define yearToSec (365 * 24 * 60 * 60)
#define hourToDay 24
#define yearToDay 365
#define numMonths 12
#define evenMonth 30
#define oddMonth 31
#define feb 28
#define startYear 1970
#define hundred1 100
#define hundred4 400

TTime convertUnixTimestampToTime(unsigned int timestamp) {
    TTime result;
    result.sec = timestamp % minToSec;
    result.min = (timestamp / minToSec) % minToSec;
    result.hour = (timestamp / hourToSec) % hourToDay;
    return result;
    }

TDate convertUnixTimestampToDateWithoutLeapYears(unsigned int timestamp) {
    TDate result;

    timestamp /= dayToSec;
    result.year = startYear + (timestamp / yearToDay);
    timestamp -= (timestamp / yearToDay) * yearToDay;

    int daysEachMonth[numMonths] = {oddMonth, feb, oddMonth, evenMonth, oddMonth, evenMonth, oddMonth,
                                    oddMonth, evenMonth, oddMonth, evenMonth, oddMonth};
    int i = 0;
    while (timestamp > daysEachMonth[i]) {
        timestamp -= daysEachMonth[i++];
    }

    result.month = ++i;
    result.day = ++timestamp;
    return result;
}

int checkLeapYear(unsigned int year) {
    return (year % 4 == 0 && (year % hundred1 != 0 || year % hundred4 == 0));
}

TDate convertUnixTimestampToDate(unsigned int timestamp) {
    TDate result;
    result.year = startYear;
    timestamp /= dayToSec;

    while (1) {
        if (timestamp >= (yearToDay + checkLeapYear(result.year))) {
            timestamp -= (yearToDay + checkLeapYear(result.year));
        } else {
            break;
        }
        result.year += 1;
    }
    int daysEachMonth[numMonths] = {oddMonth, feb, oddMonth, evenMonth, oddMonth, evenMonth, oddMonth,
                                    oddMonth, evenMonth, oddMonth, evenMonth, oddMonth};
    int i = 0;
    while (timestamp >= daysEachMonth[i]) {
        if (checkLeapYear(result.year) && i == 1) {
            timestamp--;
        }
        timestamp -= daysEachMonth[i++];
    }
    result.month = ++i;
    result.day = ++timestamp;

    return result;
}

TDateTimeTZ convertUnixTimestampToDateTimeTZ(unsigned int timestamp, TTimezone *timezones, int timezone_index) {
    TDateTimeTZ result;
    timestamp += (hourToSec * timezones[timezone_index].utc_hour_difference);
    result.date = convertUnixTimestampToDate(timestamp);
    result.time = convertUnixTimestampToTime(timestamp);
    result.tz = (TTimezone*)malloc(sizeof(TTimezone));
    snprintf(result.tz->name, sizeof(result.tz->name), "%s", timezones[timezone_index].name);
    result.tz->utc_hour_difference = timezones[timezone_index].utc_hour_difference;
    return result;
}

unsigned int convertDateTimeTZToUnixTimestamp(TDateTimeTZ datetimetz) {
    unsigned int timestamp = 0;

    timestamp += datetimetz.time.sec;
    timestamp += minToSec * datetimetz.time.min;
    timestamp += hourToSec * datetimetz.time.hour;
    timestamp += dayToSec * (datetimetz.date.day - 1);

    int daysEachMonth[numMonths] = {oddMonth, feb, oddMonth, evenMonth, oddMonth, evenMonth, oddMonth,
                                    oddMonth, evenMonth, oddMonth, evenMonth, oddMonth};
    for (int i = 0; i < datetimetz.date.month - 1; i++) {
        timestamp += dayToSec * daysEachMonth[i];
    }

    if (datetimetz.date.month > 2 && checkLeapYear(datetimetz.date.year)) {
        timestamp += dayToSec;
    }

    for (int i = startYear; i < datetimetz.date.year; i++) {
        if (checkLeapYear(i)) {
            timestamp += dayToSec;
        }
        timestamp += yearToSec;
    }

    timestamp -= hourToSec * datetimetz.tz->utc_hour_difference;
    return timestamp;
}

void printDateTimeTZ(TDateTimeTZ datetimetz) {
    char* months[numMonths] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie", "iulie",
                      "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
    printf("%02d %s %d, %02d:%02d:%02d %s (UTC%+d)\n", datetimetz.date.day, months[datetimetz.date.month - 1],
            datetimetz.date.year, datetimetz.time.hour, datetimetz.time.min, datetimetz.time.sec,
            datetimetz.tz->name, datetimetz.tz->utc_hour_difference);
}
