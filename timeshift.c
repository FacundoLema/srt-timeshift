#include <stdio.h>
#include <stdlib.h>

const int TIMESTAMP = 30;
const char numbers[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

int main (int argc, char** argv) {

    // Quit if less than 2 arguments are provided
    if (argc < 4) {fprintf(stderr, "Insufficient arguments!\n"); return 1;}

    char *oldfile = argv[1], *newfile = argv[2];
    int offset = atoi(argv[3]);

    // Try to open file
    FILE *file = fopen(oldfile, "r");
    if (!file) {perror("Failed to load"); return 1;}

    // Get file length
    fseek (file, 0, SEEK_END);
    long int file_length = ftell(file);
    fseek (file, 0, SEEK_SET);

    // Load file
    char* buffer = malloc(sizeof(char) * file_length);
    fread(buffer, file_length, 1, file);

    char time[TIMESTAMP];

    // Look for timestamps
    for (int i = 0; i < file_length; i++) {
        if (*(buffer + i) == '0' && *(buffer + i - 1) == '\n') {

            int updated_start, updated_end;
            char updatedtime[TIMESTAMP];

            // Save timestamps to array
            for (int j = 0; j < TIMESTAMP; j++) {time[j] = *(buffer + i + j);}
            time[TIMESTAMP - 1] = '\0';

            // Extract starting time
            char start_hr[3] = {time[0], time[1], '\0'};
            char start_min[3] = {time[3], time[4], '\0'};
            char start_sec[3] = {time[6], time[7], '\0'};
            // Transform hh:mm:ss into seconds
            int start_time = atoi(start_sec) + (atoi(start_min)*60) + (atoi(start_hr)*3600);
            // Fix offset if offset < 0 for time < |offset|
            if (offset < 0 && start_time < (offset*-1)) {updated_start = 0;}
            else {updated_start = start_time + offset;}
            // Format updated time
            int u_start_sec = updated_start % 60;
            int u_start_min = updated_start / 60;
            int u_start_hr = updated_start / 3600;
            if (u_start_min >= 60) {u_start_min -= 60;}
            
            // Extract ending time
            char end_hr[3] = {time[17], time[18], '\0'};
            char end_min[3] = {time[20], time[21], '\0'};
            char end_sec[3] = {time[23], time[24], '\0'};
            // Transform hh:mm:ss into seconds
            int end_time = atoi(end_sec) + (atoi(end_min)*60) + (atoi(end_hr)*3600);
            // Fix offset if offset < 0 for time < |offset|
            if (offset < 0 && end_time < (offset*-1)) {updated_end = 0;}
            else {updated_end = end_time + offset;}
            // Format updated time
            int u_end_sec = updated_end % 60;
            int u_end_min = updated_end / 60;
            int u_end_hr = updated_end / 3600; 
            if (u_end_min >= 60) {u_end_min -= 60;}

            char start[13] = {  numbers[u_start_hr/10],
                                numbers[u_start_hr%10], ':',
                                numbers[u_start_min/10],
                                numbers[u_start_min%10], ':',
                                numbers[u_start_sec/10],
                                numbers[u_start_sec%10], ',',
                                time[9], time[10], time[11]
                            };

            char end[13] = {    numbers[u_end_hr/10],
                                numbers[u_end_hr%10], ':',
                                numbers[u_end_min/10],
                                numbers[u_end_min%10], ':',
                                numbers[u_end_sec/10],
                                numbers[u_end_sec%10], ',',
                                time[26], time[27], time[28]
                            };

            // Save updated time to buffer
            sprintf(updatedtime, "%s --> %s", start, end);
            for (int j = 0; j < TIMESTAMP; j++) 
                *(buffer + i + j) = updatedtime[j];
            }
        }

    // Create new file
    FILE *nfile = fopen(newfile, "w"); 
    if (!nfile) {fprintf(stderr, "Failed to create file!\n"); return 2;}

    // Print buffer to new file
    fprintf(nfile, "%s", buffer);

    // Clean up
    fclose(file); fclose(nfile); free(buffer);
}