#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SECONDS_PER_DAY 86400
#define VERSION "1.0.0"
#define DATE_STR_SIZE 11 // YYYY-MM-DD\0
#define TIME_STR_SIZE 9  // HH:MM:SS\0

// Get UNIX day from raw time
long long get_unix_day(time_t t) {
    return t / SECONDS_PER_DAY;
}

// Convert UNIX day to formatted date
char* unix_day_to_date(long long ud) {
    time_t rawtime = ud * SECONDS_PER_DAY;
    struct tm* timeinfo;
    char* buffer = (char*)malloc(DATE_STR_SIZE);

    if (!buffer) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    timeinfo = gmtime(&rawtime);
    strftime(buffer, DATE_STR_SIZE, "%Y-%m-%d", timeinfo);

    return buffer;
}

// Convert date string to UNIX day
long long date_string_to_unix_day(char* date_string) {
    struct tm tm = {0};
    char* success;

    success = strptime(date_string, "%Y-%m-%d", &tm) ? "%Y-%m-%d"
            : strptime(date_string, "%d.%m.%Y", &tm) ? "%d.%m.%Y"
            : strptime(date_string, "%m/%d/%Y", &tm) ? "%m/%d/%Y"
            : NULL;

    if (success) {
        tm.tm_hour = 0;
        tm.tm_min = 0;
        tm.tm_sec = 0; // Ensure the time is 00:00:00
        time_t t = timegm(&tm); // interpret the input as UTC, not local time
        return get_unix_day(t);
    }

    return -1;
}

// Print usage information
void print_usage(char* program_name) {
    printf("Usage: %s [UNIX_day|date] [--help] [--version]\n", program_name);
    printf("Date can be in 'YYYY-MM-DD', 'DD.MM.YYYY', or 'MM/DD/YYYY' format.\n");
}

// Print version information
void print_version() {
    printf("Version: %s\n", VERSION);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--help") == 0) {
            print_usage(argv[0]);
            return EXIT_SUCCESS;
        }
        if (strcmp(argv[1], "--version") == 0) {
            print_version();
            return EXIT_SUCCESS;
        }

        char* end;
        long long date_flag = strtoll(argv[1], &end, 10);

        if (*end == '\0') { // The argument was a UNIX day number
            char* date = unix_day_to_date(date_flag);
            printf("%s\n", date);
            free(date);
        } else { // The argument was a date string
            long long unix_day = date_string_to_unix_day(argv[1]);
            if (unix_day == -1) {
                fprintf(stderr, "Invalid date or unknown argument: %s\n", argv[1]);
                print_usage(argv[0]);
                return EXIT_FAILURE;
            }
            printf("%lld\n", unix_day);
        }
    } else {
        printf("%lld\n", get_unix_day(time(NULL)));
    }

    return EXIT_SUCCESS;
}
