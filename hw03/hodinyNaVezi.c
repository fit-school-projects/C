#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#endif /* __PROGTEST__ */

/**
 * @brief function to know if the year is Leap or not
 * 
 * @param year 
 * @return int return 0 if the year is not leap and 1 if the year is leap
 */
int isLeapYear(int year){
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
      if (year % 4000 == 0){
        return 0;
      }
      return 1;
    }
    return 0;
}

/**
 * @brief function that calculates the day of the week from the current date
 * (ZELLERS ALGORITHM)
 * @param year 
 * @param month 
 * @param day 
 * @return int if h is 1 due to Zellers algorithm day is sunday -> return 1 
 */
int zellersAlgorithm(int year, int month, int day)
{
    if (month < 3) {
      month += 12;
      year--;
    }
    int d = day;
    int m = month;
    int y = year;

    int n = d + (2 * m) + (3 * (m + 1) / 5) + y + (y / 4) - (y / 100) + (y / 400) - (y / 4000) + 2;
    int dayOfWeek = n % 7;
    // 1 equals when day is sunday
    return dayOfWeek;
}

/**
 * @brief Function to find the exact day of the year
 * 
 * @param year 
 * @param month 
 * @param day 
 * @return int returns the current day of the year
 */
int dayOfTheYear(int year, int month, int day)
{
    long long int currDayOfTheYear;
    int days[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
    int daysInMonth[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(year)) {
      daysInMonth[2] += 1;
    }
    if (daysInMonth[month] < day)
      return 0;
    currDayOfTheYear = days[month - 1] + day;
    if (isLeapYear(year) && month > 2)
      currDayOfTheYear ++;
    return currDayOfTheYear;
}
/**
 * @brief function that calculates the number of minutes of the current year
 * @param year 
 * @param month 
 * @param day 
 * @param hour 
 * @param minute 
 * @return int minutes of the input date
 */
int datetimeToMinutes(int year, int month, int day, int hour, int minute)
{
    int minutes = (dayOfTheYear( year, month, day ) - 1) * 24 * 60 + hour * 60 + minute;
    return minutes;
}
/**
 * @brief function to validate the dates on the stdin 
 * 
 * @return int 
 */
int validateDate( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2 )
{
    if (y1 < 1600 || y2 < 1600 || m1 < 1 || m1 > 12 || m2 < 1 || m2 > 12 || d1 < 1 || d2 < 1
        || dayOfTheYear(y1,m1,d1) == 0 || dayOfTheYear(y2,m2,d2) == 0 || h1 < 0 || h1 > 23 
        || h2 < 0 || h2 > 23 || i1 < 0 || i1 > 59 || i2 < 0 || i2 > 59 )
    {
        return 0;
    }
    if (y1 > y2 || (y1 == y2 && datetimeToMinutes(y1,m1,d1,h1,i1) > datetimeToMinutes(y2,m2,d2,h2,i2)))
    {
        return 0;
    }
    return 1;
}
/**
 * @brief function to calculate the bell rings on the second bell
 * 
 * @param hours1 
 * @param hours2 
 * @param b2 
 * @return int 
 */
void secondBellRings(int hours1, int hours2, long long * b2)
{
    for (int i = hours1; i <= hours2; i++)
    {
        if (i > 12)
            *b2 += i - 12;
        else {
            *b2 += i == 0 ? 12 : i; 
        }
    }
}

/**
 * @brief function that calculates the number of both bell rings in the current day period
 * 
 * @param hours1 
 * @param mins1 
 * @param hours2 
 * @param mins2 
 * @param b1 
 * @param b2 
 */
void calculateBellRingsFromTimeToTime ( int hours1, int mins1, int hours2, int mins2, long long int * b1, long long int * b2 )
{
    // B2
    if (mins1 == 0) {
        secondBellRings(hours1, hours2, b2);
    } else {
        secondBellRings(hours1+1, hours2, b2);
    }

    // B1
    if (hours1 == hours2)
    {
        for (int i = mins1; i <= mins2; i++)
        {
            if (i == 0)
                *b1 += 4;
            if (i == 15)
                *b1 += 1;
            if (i == 30)
                *b1 += 2;
            if (i == 45)
                *b1 += 3;
        }
    }
    else {
        *b1 += (hours2 - hours1 - 1) * 10;
        if (mins2 >= 0)
            *b1 += 4;
        if (mins2 >= 15)
            *b1 += 1;
        if (mins2 >= 30)
            *b1 += 2;
        if (mins2 >= 45)
            *b1 += 3;

        for (int i = mins1; i <= 45; i++)
        {
            if (i == 0){
                *b1 += 10;
                break;
            }
            if (i == 15){
                *b1 += 6;
                break;
            }
            if (i == 30){
                *b1 += 5;
                break;
            }
            if (i == 45)
                *b1 += 3;
        }
    }
    
}
long long int numOfSundays( long long int dayDiff, int year, int month, int day)
{
    long long int shiftDays = 0;
    long long int sundays = 0;
    for (long long int i = 1; i <= dayDiff; i++)
    {
      if (shiftDays >= dayDiff) break;
      if (dayOfTheYear(year, month, day + i) == 0)
      {
        day = 1;
        i = 0;
        month++;
      }
      if (zellersAlgorithm(year, month, day + i) != 1){
         shiftDays++;
      } else {
        sundays = 1;
        break;
      }
    }
    if (dayDiff < 7) {
      return sundays;
    }
    sundays = (dayDiff - shiftDays) / 7.0;
    if (((dayDiff - shiftDays) % 7) != 0) {
      sundays++;
    } 
    return sundays;
}
/**
 * @brief function to calculate the number of leapDays between two years
 * 
 * @param y1 
 * @param y2 
 * @return int returns the number of leapDays
 */
long long int leapDaysFast(int y1, int y2)
{
  long long int leapDays;
  long long int leapDaysYearOne = y1 / 4 - y1 / 100 + y1 / 400 - y1 / 4000;
  long long int leapDaysYearTwo = y2 / 4 - y2 / 100 + y2 / 400 - y2 / 4000;
  leapDays = leapDaysYearTwo - leapDaysYearOne;
  return leapDays;
}
/**
 * @brief function that calculates the number of bell rings from the dayDifference 
 * dayDifference can be from the start of the year to the end of the interval, from the start 
 * of the interval to the end of the year or from start to the end of the interval of the same year
 * we use day bell ring constants to fasten the count of the current period
 * 
 * @param y1 
 * @param m1 
 * @param d1 
 * @param h1 
 * @param i1 
 * @param y2 
 * @param m2 
 * @param d2 
 * @param h2 
 * @param i2 
 * @param b1 
 * @param b2 
 * @param dayDiff1 
 * @param dayDiff2 
 */
void countTheBothBellRings(int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2, long long int * b1, long long int * b2, 
            long long int dayDiff1, long long int dayDiff2)
{
    long long int dayBell1 = 240;
    long long int dayBell2 = 156;
    if ( zellersAlgorithm(y2,m2,d2) != 1) {
        calculateBellRingsFromTimeToTime(0,0,h2,i2,b1,b2);
    }
    if ( zellersAlgorithm(y1,m1,d1) != 1) {
        calculateBellRingsFromTimeToTime(h1,i1,23,59,b1,b2);
    }
    if (y1 == y2)
      dayDiff1 -= numOfSundays(dayDiff1, y1, m1, d1);
    else {
      dayDiff1 -= numOfSundays(dayDiff1, y1, m1, d1);
      dayDiff2 -= numOfSundays(dayDiff2, y2, 1, 0);
    }

    *b1 += dayDiff1 * dayBell1 + dayDiff2 * dayBell1;
    *b2 += dayDiff1 * dayBell2 + dayDiff2 * dayBell2;
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{
  if ( ! validateDate(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2) ) {
        return 0;
  }
  *b1 = 0;
  *b2 = 0;
 long long int dayDiff1, dayDiff2;
  /* CASE1: The same day */ 
  if (y1 == y2 && m1 == m2 && d1 == d2){
    if (zellersAlgorithm(y1,m1,d1) == 1){
        *b1 = 0;
        *b2 = 0;
        return 1;
    } else {
        calculateBellRingsFromTimeToTime(h1,i1,h2,i2,b1,b2);
        return 1;
    }
  }
  /* CASE 2: days are different, same year */
  else if(y1 == y2){
    long long int dayDiff = dayOfTheYear(y2,m2,d2) - dayOfTheYear(y1,m1,d1) - 1; // Full days
    countTheBothBellRings(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2,b1,b2,dayDiff,0);
  }
  /* CASE 3: Years are different */
  else {
      long long int leapDays = leapDaysFast(y1, y2 - 1);
      long long int firstSundayPosition = 0;

      for (int i = 1; i <= 7; i++)
      {
        if (zellersAlgorithm(y1 + 1, 1, i) != 1){
            firstSundayPosition++;
        } else {
          break;
        }
      }

      long long int yearDiff = y2 - y1 - 1;
      long long int yearsDays = yearDiff * 365 + leapDays;
      long long int sundays = (yearsDays - firstSundayPosition) / 7;
      if (((yearsDays - firstSundayPosition) % 7) != 0){
        sundays++;
      }
      long long int daysWithoutSundays = yearsDays - sundays;
      dayDiff1 = 365 - dayOfTheYear(y1,m1,d1) + isLeapYear(y1);
      dayDiff2 = dayOfTheYear(y2,m2,d2) - 1;
      countTheBothBellRings(y1,m1,d1,h1,i1,y2,m2,d2,h2,i2,b1,b2,dayDiff1, dayDiff2);
      /* full year */
      *b1 += (y2 - y1 - 1) == 0 ? 0 : (daysWithoutSundays * 240);
      *b2 += (y2 - y1 - 1) == 0 ? 0 : (daysWithoutSundays * 156);
    }
  return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;
  bells ( 1600, 1,  1, 0, 0,
                   INT_MAX, 12,  31, 0, 0, &b1, &b2 );
  printf("%lld %lld", b1, b2);
  assert ( bells ( 2022, 12,  30, 1, 29,
                   2023, 1,  2, 1, 31, &b1, &b2 ) == 1
           && b1 == 482
           && b2 == 312);
  assert ( bells ( 2004,  2, 28, 12,  1,
                   2004,  2, 28, 12,  0, &b1, &b2 ) == 0
           && b1 == 482
           && b2 == 312 );

  assert (bells ( 1966, 1, 1, 0, 0, 
                    2126, 12, 31, 23, 59, &b1, &b2 ) == 1
            && b1 == 12096720
            && b2 == 7862868);
  
  assert ( bells ( 2022, 1,  22, 23, 59,
                   2022, 1,  25, 0, 0, &b1, &b2 ) == 1
           && b1 == 244
           && b2 == 168);
  assert ( bells ( 2022, 1,  21, 23, 59,
                   2022, 1,  24, 0, 0, &b1, &b2 ) == 1
           && b1 == 244
           && b2 == 168);
  
  assert ( bells ( 2022, 10,  1, 0, 0,
                   2022, 10,  1, 23, 59, &b1, &b2 ) == 1
           && b1 == 240
           && b2 == 156 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );
  assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  2, 11, 20, &b1, &b2 ) == 1
           && b1 == 106
           && b2 == 65 );
  assert ( bells ( 2022, 10,  2, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 115
           && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022,  1,  1, 13, 15,
                   2022, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 56861
           && b2 == 36959 );
  assert ( bells ( 2019,  1,  1, 13, 15,
                   2019, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
    
  assert ( bells ( 2024,  1,  1, 13, 15,
                   2024, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57341
           && b2 == 37271 );
    
  assert ( bells ( 1900,  1,  1, 13, 15,
                   1900, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
    
  assert ( bells ( 2022, 10,  1,  0,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 124
           && b2 == 90 );
  assert ( bells ( 2022, 10,  1,  0, 15,
                   2022, 10,  1,  0, 25, &b1, &b2 ) == 1
           && b1 == 1
           && b2 == 0 );
  assert ( bells ( 2022, 10,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 11,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 10, 32, 12,  0,
                   2022, 11, 10, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2100,  2, 29, 12,  0,
                   2100,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2000,  2, 29, 12,  0,
                   2000,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2004,  2, 29, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 0
           && b2 == 0 );
  
  assert ( bells ( 2021, 1, 1, 0, 0,
                   2021, 12, 31, 23, 59, &b1, &b2 ) == 1
           && b1 == 75120
           && b2 == 48828 );
  assert ( bells ( 2022, 1, 1, 0, 0,
                   2022, 12, 31, 23, 59, &b1, &b2 ) == 1
           && b1 == 75120
           && b2 == 48828 );
  assert ( bells ( 2023, 1, 1, 0, 0,
                   2023, 12, 31, 23, 59, &b1, &b2 ) == 1
           && b1 == 74880
           && b2 == 48672 );
  assert ( bells ( 2020, 1, 1, 0, 0,
                   2020, 12, 31, 23, 59, &b1, &b2 ) == 1
           && b1 == 75360
           && b2 == 48984 );
  
  assert ( bells ( 2020, 1, 1, 0, 0,
                   2023, 12, 31, 23, 59, &b1, &b2 ) == 1
           && b1 == 300480
           && b2 == 195312 );
  
  assert ( bells ( 2020, 1, 7, 23,44,
                   2020, 1, 8, 0, 1, &b1, &b2 ) == 1
           && b1 == 7
           && b2 == 12 );
  assert ( bells ( 2020, 1, 5, 23,44,
                   2020, 1, 6, 0, 1, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert (bells ( 2006, 6, 14, 0, 20,
                  2006, 6, 14, 1, 10, &b1, &b2 ) == 1 
           && b1 == 9
           && b2 == 1 );
    assert (bells ( 2006, 6, 14, 17, 23,
                  2006, 6, 15, 17, 28, &b1, &b2 ) == 1 
           && b1 == 240
           && b2 == 156 );
    assert (bells ( 2006, 6, 14, 17, 23,
                  2006, 6, 15, 18, 38, &b1, &b2 ) == 1 
           && b1 == 252
           && b2 == 162 );
    assert (bells ( 2006, 6, 14, 23, 0,
                  2006, 6, 15, 0, 15, &b1, &b2 ) == 1 
           && b1 == 15
           && b2 == 23 );
    assert (bells ( 2006, 6, 14, 0, 0,
                  2006, 6, 14, 1, 0, &b1, &b2 ) == 1 
           && b1 == 14
           && b2 == 13 );
    assert (bells ( 2006, 6, 14, 5, 45,
                  2006, 6, 14, 7, 25, &b1, &b2 ) == 1 
           && b1 == 18
           && b2 == 13 );
    assert (bells ( 2006, 6, 14, 0, 1,
                  2006, 6, 14, 0, 10, &b1, &b2 ) == 1 
           && b1 == 0
           && b2 == 0 );
    
    assert (bells ( 2127, 1, 1, 0, 0, 
                    2127, 7, 26, 12, 19, &b1, &b2 ) == 1
            && b1 == 42605
            && b2 == 27702);
    
    assert (bells ( 1965, 11, 10, 7, 56, 
                    1965, 12, 31, 23, 59, &b1, &b2 ) == 1
            && b1 == 10720
            && b2 == 6980);
    
    assert (bells ( 1965, 11, 10, 7, 56, 
                    2127, 7, 26, 12, 19, &b1, &b2 ) == 1
            && b1 == 12150045
            && b2 == 7897550);
  
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
