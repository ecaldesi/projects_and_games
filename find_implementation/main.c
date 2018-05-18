/* driver.c */

#include "search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <unistd.h>

/* Functions */

void usage(const char *program_name, int status) {
    fprintf(stderr, "Usage: %s PATH [OPTIONS] [EXPRESSION]\n", program_name);
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "    -executable     File is executable or directory is searchable to user\n");
    fprintf(stderr, "    -readable       File readable to user\n");
    fprintf(stderr, "    -writable       File is writable to user\n\n");
    fprintf(stderr, "    -type [f|d]     File is of type f for regular file or d for directory\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -empty          File or directory is empty\n\n");
    fprintf(stderr, "    -name  pattern  Base of file name matches shell pattern\n");
    fprintf(stderr, "    -path  pattern  Path of file matches shell pattern\n\n");
    fprintf(stderr, "    -perm  mode     File's permission bits are exactly mode (octal)\n");
    fprintf(stderr, "    -newer file     File was modified more recently than file\n\n");
    fprintf(stderr, "    -uid   n        File's numeric user ID is n\n");
    fprintf(stderr, "    -gid   n        File's numeric group ID is n\n");
    fprintf(stderr, "\nExpressions:\n\n");
    fprintf(stderr, "    -print          Display file path (default)\n");
    fprintf(stderr, "    -exec cmd {} ;  Execute command on path\n");
    exit(status);
}

/* Main Execution */

int main(int argc, char *argv[]) {

    Settings settings = {
        .access = 0,
        .uid = -1,
        .gid = -1,
    };

    // program name
    const char* program_name = argv[0];

    // if no argument is passed
    if (argc == 1) {
        perror("no arguments passed");
        return 1;
    }
    
    // check for -h flag
    if (strcmp(argv[1], "-h") == 0) {
        usage(program_name, 0);
    }   
    char *root = argv[1];
    int argind = 2;

    while (argind < argc && strlen(argv[argind]) > 1 && argv[argind][0] == '-') {
        char *arg = argv[argind++];
        if (streq(arg, "-executable"))  settings.access |= X_OK;
        if (streq(arg, "-readable"))    settings.access |= R_OK;
        if (streq(arg, "-writable"))    settings.access |= W_OK;
        if (streq(arg, "-type"))        {
            char *TYPE = argv[argind++];
            if (strcmp(TYPE, "f") == 0) {
                settings.type = S_IFREG;
            } else if (strcmp(TYPE, "d") == 0) {
                settings.type = S_IFDIR;
            }
        }
        if (streq(arg, "-empty"))       settings.empty = true;
        if (streq(arg, "-name"))        settings.name = argv[argind++];
        if (streq(arg, "-path"))        settings.path = argv[argind++];
        if (streq(arg, "-perm"))        settings.perm = strtol(argv[argind++], NULL, 8);
        if (streq(arg, "-newer"))       {
            struct stat buf;
            stat(argv[argind++], &buf);
            settings.newer = buf.st_mtime;
        }
        if (streq(arg, "-uid"))        settings.uid = strtol(argv[argind++], NULL, 10);
        if (streq(arg, "-gid"))        settings.gid = strtol(argv[argind++], NULL, 10);
        if (streq(arg, "-print"))      settings.print = true;
        if (streq(arg, "-exec"))       {
            settings.exec_argc = 1;
            settings.exec_argv = &argv[argind];
            while(strcmp(argv[argind], ";")!=0 && argind<argc) {
                    settings.exec_argc++;
                    argind++;
            }
        }
    }

    if (filter(root,&settings) == false) {     
        execute(root,&settings);
    }
    int returnval = search(root, &settings);
    return returnval;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
