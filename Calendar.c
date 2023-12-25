#include <stdio.h>
#include <time.h>

int main() {
    int month, year, daysInMonth, startingDay;
    
    // Get current date
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentDay = tm.tm_mday;
    int currentMonth = tm.tm_mon + 1;
    int currentYear = tm.tm_year + 1900;
    
    // Get input from the user
    printf("Enter the month (1-12): ");
    scanf("%d", &month);
    
    printf("Enter the year: ");
    scanf("%d", &year);
    
    // Determine the number of days in the given month
    if (month == 2) {
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
            daysInMonth = 29;
        } else {
            daysInMonth = 28;
        }
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        daysInMonth = 30;
    } else {
        daysInMonth = 31;
    }
    
    // Determine the starting day of the month (Sunday is 0, Monday is 1, etc.)
    int a = (14 - month) / 12;
    int y = year - a;
    int m = month + 12 * a - 2;
    startingDay = (1 + y + y/4 - y/100 + y/400 + (31*m)/12) % 7;
    
    // Print the calendar header
    printf("\n-----------------------------\n");
    printf("   %d/%d\n", month, year);
    printf("-----------------------------\n");
    printf(" Sun Mon Tue Wed Thu Fri Sat\n");
    
    // Print the calendar body
    int i, day;
    for (i = 0; i < startingDay; i++) {
        printf("    ");
    }
    for (day = 1; day <= daysInMonth; day++) {
        if (day == currentDay && month == currentMonth && year == currentYear) {
            printf("\033[1;31m"); // Highlight today's date
        }
        printf("%4d", day);
        if ((day + startingDay) % 7 == 0) {
            printf("\n");
        }
        printf("\033[0m"); // Reset text color
    }
    
    printf("\n\n");
    
    return 0;
}
