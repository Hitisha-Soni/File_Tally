#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int dir_count = 0;
int file_count = 0;

void inside(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
       // perror("opendir failed");
        return; // Unable to open directory
    }

    while ((entry = readdir(dp)) != NULL) {
        // Skip the current and parent directory entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s\\%s", path, entry->d_name); // Use backslash for Windows

        struct stat statbuf;
        if (stat(full_path, &statbuf) == 0) {
            if (S_ISREG(statbuf.st_mode)) {
                // It's a file
                file_count++;
            } else if (S_ISDIR(statbuf.st_mode)) {
                // It's a directory
                dir_count++;
                inside(full_path); // Recursively count inside the directory
            }
        } else {
            //perror("stat failed");
        }
    }

    closedir(dp);
}

int main() {
    // Check both C: and D: drives
    const char *drives[] = {"C:\\", "D:\\"};
printf(" _______ ___ ___     _______   _______ _______ ___     ___      __   __   \n");
printf("|       |   |   |   |       | |       |   _   |   |   |   |    |  | |  |  \n");
printf("|    ___|   |   |   |    ___| |_     _|  |_|  |   |   |   |    |  |_|  |  \n");
printf("|   |___|   |   |   |   |___    |   | |       |   |   |   |    |       |  \n");
printf("|    ___|   |   |___|    ___|   |   | |       |   |___|   |__  |_     _|  \n");
printf("|   |   |   |       |   |___    |   | |   _   |       |       |  |   |    \n");
printf("|___|   |___|_______|_______|   |___| |__| |__|_______|_______|  |___|    \n");


printf("\n\n File and Folder Counting System,\n Please wait till the program enumerate all the directories...... \n\n");
        


    for (int i = 0; i < 2; i++) {
        printf("Scanning drive %s...\n", drives[i]);
        // Check if the drive exists
        if (opendir(drives[i]) == NULL) {
            perror("Drive not accessible");
            continue; // Skip to the next drive
        }

        inside(drives[i]);
    }

    printf("The total number of files is: %d\n", file_count);
    printf("The total number of folders is: %d\n", dir_count);

    return 0;
}