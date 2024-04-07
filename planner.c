#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "timelib.h"

#define ui unsigned int
#define hourToSec (60 * 60)
#define kNameSize 10
#define kTypeSize 5
#define kEventMaxTime 100

typedef struct {
    ui start;
    ui end;
} Interval;

typedef struct {
    char name[kNameSize];
    int canParticipate, numIntervals;
    Interval *intervals;
    TDateTimeTZ dataPacks;
} Person;

void sortPersonsInAlphabeticalOrder(Person *persons, int numPersons) {
    for (int i = 0; i < numPersons; i++) {
        for (int j = 0; j < numPersons - i - 1; j++) {
            if (strcmp(persons[j].name, persons[j + 1].name) > 0) {
                Person temp = persons[j];
                persons[j] = persons[j + 1];
                persons[j + 1] = temp;
            }
        }
    }
}

signed char getTimezoneDiff(TTimezone *timezones, int timezones_number, char personTZ[]) {
    for (int idx = 0; idx < timezones_number; idx++) {
        if (strcmp(timezones[idx].name, personTZ) == 0) {
            return timezones[idx].utc_hour_difference;
        }
    }
    return 0;
}

ui findEventDate(Person *persons, int numPersons, ui minDate, ui maxDate, int minFreePersons, int window) {
    for (ui timestamp = minDate; timestamp <= maxDate - window; timestamp++) {
        int freePersonsCount = 0;
        for (int idx = 0; idx < numPersons; idx++) {
            persons[idx].canParticipate = 0;

            int hours[kEventMaxTime] = {0};
            for (int i = 0; i < persons[idx].numIntervals; i++) {
                for (ui currInt = persons[idx].intervals[i].start; currInt < persons[idx].intervals[i].end; currInt++) {
                    if ((currInt - timestamp >= 0) && (currInt - timestamp < window)) {
                        hours[currInt - timestamp] = 1;
                    }
                }
            }

            int coverAllEvent = 1;
            for (int check = 0; check < window; check++) {
                coverAllEvent *= hours[check];
            }
            if (coverAllEvent) {
                freePersonsCount++;
                persons[idx].canParticipate = 1;
            }
        }
        if (freePersonsCount >= minFreePersons) {
            return timestamp * hourToSec;
        }
    }
    return 0;
}

int main() {
    int numTimezones = 0;
    scanf("%d", &numTimezones);

    TTimezone *timezones = (TTimezone*)calloc(numTimezones, sizeof(TTimezone));
    for (int i = 0; i < numTimezones; i++) {
        scanf("%s %hhd", timezones[i].name, &timezones[i].utc_hour_difference);
    }

    int numPersons = 0;
    scanf("%d", &numPersons);

    Person *persons = (Person*)calloc(numPersons, sizeof(Person));
    ui minDate = UINT_MAX, maxDate = 0;

    for (int idx = 0; idx < numPersons; idx++) {
        persons[idx].canParticipate = 0;

        char personTZ[kTypeSize];
        scanf("%s %s %d", persons[idx].name, personTZ, &persons[idx].numIntervals);

        persons[idx].intervals = (Interval*)calloc(persons[idx].numIntervals, sizeof(Interval));
        persons[idx].dataPacks.tz = (TTimezone*)calloc(1, sizeof(TTimezone));
        for (int i = 0, interval_len = 0; i < persons[idx].numIntervals; i++) {
            scanf("%d %hhu %hhu %hhu %d", &persons[idx].dataPacks.date.year, &persons[idx].dataPacks.date.month,
                            &persons[idx].dataPacks.date.day, &persons[idx].dataPacks.time.hour, &interval_len);

            snprintf(persons[idx].dataPacks.tz->name, sizeof(personTZ), "%s", personTZ);
            persons[idx].dataPacks.tz->utc_hour_difference = getTimezoneDiff(timezones, numTimezones, personTZ);

            ui timestamp = convertDateTimeTZToUnixTimestamp(persons[idx].dataPacks);
            persons[idx].intervals[i].start = timestamp / hourToSec;
            persons[idx].intervals[i].end = timestamp / hourToSec + interval_len;

            minDate = (persons[idx].intervals[i].start < minDate ? persons[idx].intervals[i].start : minDate);
            maxDate = (persons[idx].intervals[i].end > maxDate ? persons[idx].intervals[i].end : maxDate);
        }
    }

    int minFreePersons = 0, minEventRequiredTime = 0;
    scanf("%d %d", &minFreePersons, &minEventRequiredTime);

    ui eventStartDate = findEventDate(persons, numPersons, minDate, maxDate, minFreePersons, minEventRequiredTime);

    if (eventStartDate != 0) {
        sortPersonsInAlphabeticalOrder(persons, numPersons);

        for (int idx = 0; idx < numPersons; idx++) {
            printf("%s: ", persons[idx].name);
            if (persons[idx].canParticipate) {
                TDateTimeTZ date = convertUnixTimestampToDateTimeTZ(eventStartDate, persons[idx].dataPacks.tz, 0);
                printDateTimeTZ(date);
                free(date.tz);
            } else {
                printf("invalid\n");
            }
        }
    } else {
        printf("imposibil\n");
    }

    for (int i = 0; i < numPersons; i++) {
        free(persons[i].dataPacks.tz);
        free(persons[i].intervals);
    }
    free(persons);
    free(timezones);

    return 0;
}
