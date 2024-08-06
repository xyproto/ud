#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <err.h>

const int SECONDS_PER_DAY = 86400;
const char VERSION[] = "1.0.1";
const size_t DATE_STR_SIZE = 11; // YYYY-MM-DD\0

// Convert UNIX day to formatted date
char* unix_day_to_date(int64_t ud)
{
    time_t rawtime = ud * SECONDS_PER_DAY;
    struct tm* timeinfo;
    char* buffer = (char*)malloc(DATE_STR_SIZE);

    if (!buffer) {
        err(EXIT_FAILURE, "Memory allocation failed.\n");
    }

    timeinfo = gmtime(&rawtime);
    strftime(buffer, DATE_STR_SIZE, "%Y-%m-%d", timeinfo);

    return buffer;
}

// Convert date string to UNIX day
int date_string_to_unix_day(int64_t* unix_day, char* date_string)
{
    struct tm tm = { 0 };

    if (!strptime(date_string, "%Y-%m-%d", &tm) &&
    	!strptime(date_string, "%d.%m.%Y", &tm) &&
    	!strptime(date_string, "%m/%d/%Y", &tm)) {
        return -1; // Error
    }

    tm.tm_hour = 0;
    tm.tm_min = 0;
    tm.tm_sec = 0; // Ensure the time is 00:00:00
    time_t t = timegm(&tm); // interpret the input as UTC, not local time
    *unix_day = t/SECONDS_PER_DAY;
    return 0; // Success
}

// Print usage information
void print_usage(char* program_name)
{
    printf("Usage: %s [UNIX_day|date] [--help] [--version]\n", program_name);
    printf("Date can be in 'YYYY-MM-DD', 'DD.MM.YYYY', or 'MM/DD/YYYY' format.\n");
}

// Print version information
void print_version()
{
    printf("Version: %s\n", VERSION);
}

int main(int argc, char* argv[])
{
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
        int64_t date_flag = strtoull(argv[1], &end, 10);

        if (*end == '\0') { // The argument was a UNIX day number
            char* date = unix_day_to_date(date_flag);
            puts(date);
            free(date);
        } else { // The argument was a date string
            int64_t unix_day;
            int error = date_string_to_unix_day(&unix_day, argv[1]);
            if (error == -1) {
                fprintf(stderr, "Invalid date or unknown argument: %s\n", argv[1]);
                print_usage(argv[0]);
                return EXIT_FAILURE;
            }
            printf("%" PRIi64 "\n", unix_day);
        }
    } else {
        printf("%" PRIi64 "\n", time(NULL)/SECONDS_PER_DAY);
    }

    return EXIT_SUCCESS;
}
