#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"

#define dateMask 32767
#define numMonths 12
#define startYear 1970
#define dayMask 31
#define monthMask 15
#define yearMask 63
#define monthShift 5
#define yearShift 9
#define bitLimit 31
#define dateSize 15
#define flag1 14
#define flag2 29
#define task7 7
#define task8 8

int comparator(const void* a, const void* b) {
    return (*(unsigned int*)a > *(unsigned int*)b) - (*(unsigned int*)a < *(unsigned int*)b);
}

void SortAndPrintDates(unsigned int date[], unsigned int N) {
    qsort(date, N, sizeof(unsigned int), comparator);
    for (int index = 0; index < N; index++) {
        if (date[index] != 0) {
            unsigned int day = date[index] & dayMask;
            unsigned int month = (date[index] >> monthShift) & monthMask;
            unsigned int year = (date[index] >> yearShift) & yearMask;
            char* months[numMonths] = {"ianuarie", "februarie", "martie", "aprilie", "mai", "iunie", "iulie",
                                "august", "septembrie", "octombrie", "noiembrie", "decembrie"};
            printf("%d %s %d\n", day, months[month - 1], startYear + year);
        }
    }
}

void BasicNetworkPacking() {
    unsigned int N = 0;
    scanf("%d", &N);

    unsigned int date[N];
    for (int i = 0; i < N; i++) {
        scanf("%u", &date[i]);
        date[i] &= dateMask;
    }

    SortAndPrintDates(date, N);
}

void ComplexNetworkPacking() {
    unsigned int N = 0;
    scanf("%d", &N);

    unsigned int date[N], control_bit[N];
    unsigned int input_id = 0, currentDataPack = 0, currentBit = 0, count = 0;

    scanf("%u", &currentDataPack);

    for (int index = 0; index < N; index++) {
        date[index] = 0;
        for (int i = 0; i < dateSize; i++, currentBit++) {
            if (currentBit > bitLimit) {
                scanf("%u", &currentDataPack);
                control_bit[input_id++] = count % 2;
                count = 0;
                currentBit = 0;
            }
            if (currentDataPack & (1 << currentBit)) {
                date[index] += 1 << i;
                count++;
            }
        }
    }

    while (currentBit <= bitLimit) {
        if (currentDataPack & (1 << currentBit)) {
            count++;
        }
        currentBit++;
    }
    control_bit[input_id] = count % 2;

    for (int id = 0, index = 0; id <= input_id; id++) {
        if (id % (bitLimit + 1) == 0) {
            scanf("%u", &currentDataPack);
        }
        if (control_bit[id] != (currentDataPack & 1)) {
            date[index] = 0;
            date[index + 1] = 0;
            date[index + 2] = 0;

            if (index % (bitLimit + 1) == flag1) {
                date[index + 3] = 0;
            }
        }

        if (index % (bitLimit + 1) == flag1 || index % (bitLimit + 1) == flag2) {
            index++;
        }

        index += 2;
        currentDataPack >>= 1;
    }

    SortAndPrintDates(date, N);
}

int main() {
    int taskNumber = 0;
    scanf("%d", &taskNumber);

    if (taskNumber == task7) {
        BasicNetworkPacking();
    } else if (taskNumber == task8) {
        ComplexNetworkPacking();
    }
    return 0;
}

