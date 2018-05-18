/* execute.c */

#include "search.h"

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <dirent.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * Executes the -print or -exec expressions (or both) on the specified path.
 * @param   path        Path to a file or directory
 * @param   settings    Settings structure.
 * @return  Whether or not the execution was successful.
 */
int execute(const char *path, const Settings *settings) {
    int argc = settings->exec_argc;
    char *argv[argc];
    bool print = settings->print;
    int status = 0;

    for (int i=0; i< argc; i++) {
        argv[i] = settings->exec_argv[i];
        if (strcmp(argv[i], "{}")==0) {
            argv[i] = path;
        }
    }

    if (print || (!print && !argc)) {
        puts(path);
    }
    if (argc > 0) {
        // fork, execute and wait
        int pid = fork();

        // child
        if (pid == 0) {
            argv[argc-1] = NULL;
            
            if (execvp(argv[0], argv)!= 0) {
                fprintf(stderr, "%s\n", strerror(errno));
                return EXIT_FAILURE;
            }
            _exit(EXIT_FAILURE);

        } else if (pid >0) { // parent
            wait(&status);

        } else { // error
            fprintf(stderr, "%s", strerror(errno));
            return EXIT_FAILURE;
        }
    }   
    return status;
}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
