/* search.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <dirent.h>

/**
 * Recursively search through the provided root directory
 * @param   root        Path to directory
 * @param   settings    Settings structure
 * @return  Whether or not the search was successful.
 */
int search(const char *root, const Settings *settings) {
    struct dirent *dir;
    char path[BUFSIZ];
    DIR *d = opendir(root);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (streq(dir->d_name, ".") || (streq(dir->d_name, ".."))){
                continue;
            }
            sprintf(path, "%s/%s", root, dir->d_name);
            if (!filter(path, settings)) {
                execute(path, settings);
            }
            if (dir->d_type == DT_DIR){
                search(path, settings);
            }
        }
        closedir(d);
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
