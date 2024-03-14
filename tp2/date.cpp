/*  AUTEUR(S):
    1) Bouargan Zakariae BOUZ90340206
*/
#include "date.h"
#include <cstdio>
#include <iomanip>
#include <assert.h>
#include <ctime>

//Date sans argument: initialise une date avec les donn�es de la date actuelle
Date::Date() {
    int year,month,day;
    time_t now = time(0);
    tm* dt = localtime(&now);
    year = 1900 + dt->tm_year;
    month = 1 + dt->tm_mon;
    day = dt->tm_mday;
    this->day = day;
    this->month = month;
    this->year = year;
}


bool Date::operator<(const Date& d) const {
    if (year != d.year) {
        return year < d.year;
    } else if (month != d.month) {
        return month < d.month;
    } else {
        return day < d.day;
    }
}

// Utility function to check if a year is a leap year
bool isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

// Function to count total days up to the given date
// Accounts for leap years and correct days in each month
int countDays(int year, int month, int day) {
    // Array to store the days in each month
    int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Count the total number of days before the current year
    int totalDays = year * 365 + day;
    for (int y = 1; y < year; ++y) {
        if (isLeapYear(y)) {
            totalDays++; // Add an extra day for each leap year
        }
    }

    // Add days for the months passed in the current year
    for (int m = 0; m < month - 1; ++m) {
        totalDays += monthDays[m];
    }

    // Add an extra day if the current year is a leap year and the date is after February
    if (month > 2 && isLeapYear(year)) {
        totalDays++;
    }

    return totalDays;
}

int Date::operator-(const Date& date) const {
    // Calculate the total number of days for both dates
    int days1 = countDays(year, month, day);
    int days2 = countDays(date.year, date.month, date.day);

    // Return the difference between the two day counts
    return days1 - days2;
}


std::ostream& operator<<(std::ostream& os, const Date& d) {
    char chaine[40];
    sprintf(chaine, "%04d-%02d-%02d", d.year, d.month, d.day);
    os << chaine;
    return os;
}


std::istream& operator>>(std::istream& is, Date& d) {
    int a, m, j;
    char t1, t2;
    is >> a >> t1 >> m >> t2 >> j;
    assert(t1 == '-');
    assert(t2 == '-');
    if ((a > 0) && (m > 0 && m <= 12) && (j > 0 && j <= 31)) { // Basic validation
        d.year = a;
        d.month = m;
        d.day = j;
    }
    return is;
}




