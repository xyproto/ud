#include <err.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const int SECONDS_PER_DAY = 86400;
const char VERSION[] = "1.1.0";
const size_t DATE_STR_SIZE = 16; // YYYY[YYYYY]-MM-DD\0

// Convert UNIX day to formatted date
char* unix_day_to_date(int64_t ud)
{
    time_t rawtime = ud * SECONDS_PER_DAY;
    struct tm* timeinfo = gmtime(&rawtime);
    char* buffer = (char*)malloc(DATE_STR_SIZE);

    if (!buffer || !timeinfo) {
        err(EXIT_FAILURE, "Date conversion failed");
    }

    strftime(buffer, DATE_STR_SIZE, "%Y-%m-%d", timeinfo);

    return buffer;
}

// Print usage information
void print_usage(char* program_name)
{
    printf("Usage: %s [UNIX_day|date] [--help] [--version]\n", program_name);
    printf("Date can be in 'YYYY-MM-DD', 'DD.MM.YYYY', or 'MM/DD/YYYY' format.\n");
}

// Convert date string to UNIX day
int64_t date_string_to_unix_day(char* date_string, char* program_name)
{
    struct tm tm = { 0 };

    if (!strptime(date_string, "%Y-%m-%d", &tm) && !strptime(date_string, "%d.%m.%Y", &tm) && !strptime(date_string, "%m/%d/%Y", &tm)) {
        fprintf(stderr, "Invalid date or unknown argument: %s\n", date_string);
        print_usage(program_name);
        exit(EXIT_FAILURE);
    }

    tm.tm_hour = tm.tm_min = tm.tm_sec = 0; // Ensure the time is 00:00:00
    time_t t = timegm(&tm); // interpret the input as UTC, not local time
    return t / SECONDS_PER_DAY;
}

int main(int argc, char* argv[])
{
    if (argc == 1) {
        printf("%" PRIi64 "\n", time(NULL) / SECONDS_PER_DAY);
        return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "--help") == 0) {
        print_usage(argv[0]);
        return EXIT_SUCCESS;
    }
    if (strcmp(argv[1], "--version") == 0) {
        printf("Version: %s\n", VERSION);
        return EXIT_SUCCESS;
    }

    char* end;
    int64_t date_flag = strtoll(argv[1], &end, 10);

    if (*end == '\0') { // The argument was a UNIX day number
        char* date = unix_day_to_date(date_flag);
        puts(date);
        free(date);
    } else { // The argument was a date string
        int64_t unix_day = date_string_to_unix_day(argv[1], argv[0]);
        printf("%" PRIi64 "\n", unix_day);
    }
}
