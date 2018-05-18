/* utilities.c */

#include "search.h"

#include <errno.h>
#include <string.h>
#include <time.h>

#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

/**
 * Test whether or not a directory is empty.
 * @param   path        Path to directory.
 * @return  Whether or not a directory is empty.
 */
bool is_directory_empty(const char *path) {
    DIR *dir;
    int n = 0;
    if ((dir = opendir(path))) {
        struct dirent *d;
        while ((d = readdir(dir)) != NULL) {    
            if(++n > 2) break;
        }
        closedir(dir);
    } else {
        return false;
    }
    if (n <= 2) return true;
    return false;
}

/**
 * Retrieve the modification time of the given file.
 * @param   path        Path to file of directory.
 * @return  The modification time of the given file.
 */
time_t get_mtime(const char *path) {
    struct stat buf;
    lstat(path, &buf);
    time_t newer = buf.st_mtime;
    return newer;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
