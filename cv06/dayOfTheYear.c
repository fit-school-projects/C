#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */

/**
 * @brief function to check if the current year is leap
 * 
 * @param year year of the date
 * @return int 1 if the year is leap
 */
int isLeapYear(int year)
{
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
      if (year % 4000 == 0){
        return 0;
      }
      return 1;
    }
    return 0;
}
/**
 * @brief function to validate the date
 * 
 * @param d 
 * @param m 
 * @param y 
 * @return int 0 if the date is wrong 
 */
int validateDate(int d, int m, int y)
{
    if ((!isLeapYear(y) && d == 29 && m == 2) ||
        d < 1 ||
        d > 31 ||
        m < 1 ||
        m > 12 ||
        y < 2000 )
    {
        return 0;
    }
    return 1;
}
/**
 * @brief function to find the day of the current year
 * 
 * @param day 
 * @param month 
 * @param year 
 * @param idx 
 * @return int 1 if the date is valid and we find the output param index
 */
int dateToIndex(int day, int month, int year, int *idx) {
    if ( !validateDate(day, month, year) )
        return 0;
    int d = 0;
    switch ( month )
    {
    case 1:
        d = day; // 31
        break;
    case 2:
        if (isLeapYear(year) && day > 29) return 0;
        d = day + 31; // 28
        break;
    case 3:
        d = day + 59; // 31
        break;
    case 4:
        if (day > 30) return 0;
        d = day + 90; // 30 
        break;
    case 5:
        d = day + 120; // 31
        break;
    case 6:
        if (day > 30) return 0;
        d = day + 151; // 30 
        break;
    case 7:
        d = day + 181; // 31
        break;
    case 8:
        d = day + 212; // 31
        break;
    case 9:
        if (day > 30) return 0;
        d = day + 243; // 30
        break;
    case 10:
        d = day + 273; // 31
        break;
    case 11:
        if (day > 30) return 0;
        d = day + 304; // 30
        break;
    case 12:
        d = day + 334; // 31
        break;
    default:
        break;
    }
    if (isLeapYear(year) && month > 2)
    {
        d += 1;
    } 
    *idx = d;
    return 1;
}

#ifndef __PROGTEST__
int main (int argc, char * argv []) {
    int idx;
    assert(dateToIndex(29, 3, 320000, &idx) == 1 && idx == 88);
    assert(dateToIndex( 1,  1, 1999, &idx) == 0);
    assert(dateToIndex( 1,  1, 2000, &idx) == 1 && idx == 1);
    assert(dateToIndex( 1,  2, 2000, &idx) == 1 && idx == 32);
    assert(dateToIndex(29,  2, 2000, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 2001, &idx) == 0);
    assert(dateToIndex( 1, 12, 2000, &idx) == 1 && idx == 336);
    assert(dateToIndex(31, 12, 2000, &idx) == 1 && idx == 366);
    assert(dateToIndex( 6,  7, 3600, &idx) == 1 && idx == 188);
    assert(dateToIndex(29,  2, 3600, &idx) == 1 && idx == 60);
    assert(dateToIndex(29,  2, 4000, &idx) == 0);
    
    return 0;
}
#endif /* __PROGTEST__ */

