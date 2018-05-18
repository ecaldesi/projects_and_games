/* filter.c */

#include "search.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>

#include <dirent.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <unistd.h>
#include <libgen.h>

/**
 * Test whether or not the given path should be filtered out of the output.
 * @param   path        Path to file or directory.
 * @param   settings    Settings structure.
 * @return  Whether or not the path should be excluded from the output (true to
 * exclude, false to include).
 */
bool filter(const char *path, const Settings *settings) {
    //struct dirent *d;
    struct stat buf;
    lstat(path, &buf);
  
    // get name
    char *temp = (char *)path; 
    char *name = basename(temp);

    // check if path matches the path given in settings
    if (settings->path != 0) {
        int MatchPath = fnmatch(settings->path, path, 0);
        if (MatchPath == FNM_NOMATCH) {
            return true;
        }
    }
    // check if basename matches the name given in settings
    if (settings->name != 0) {
        int MatchName = fnmatch(settings->name, name, 0);
        if (MatchName == FNM_NOMATCH) {
            return true;
        }
    }
    
    int type;
    mode_t mode = buf.st_mode;
    // set empty as false
    bool empty = false;
    // get size 
    int size = buf.st_size;

    if (S_ISDIR(mode)) {
        type = S_IFDIR;
        empty = is_directory_empty(path);
    }
    if (S_ISREG(mode)) {
        type = S_IFREG; 
        if (size == 0) {
            empty = true;
        }   
    }

    // find perm
    int perm = mode & (S_IRWXU | S_IRWXG | S_IRWXO);

    // find uid
    int uid = buf.st_uid;
    // find gid
    int gid = buf.st_gid;
    
    // find last modified time (newer)
    time_t newer = get_mtime(path);
    // find access
    int access1 = access(path, settings->access);

    // compare values found to the values in settings
    if (settings->type != 0 && settings->type != type) {
        return true;
    }
    
    // access
    if (settings->access != 0 && access1) {
        return true;
    }

    // empty
    if (settings->empty !=0 && !empty) {
        return true;
    }

    // perm
    if (settings->perm != 0 && settings->perm != perm) {
        return true;
    }

    // newer
    if (settings->newer != 0 && settings->newer >= newer) {
        return true;
    }

    // uid
    if (settings->uid != -1 && settings->uid != uid) {
        return true;
    }

    // gid
    if (settings->gid != -1 && settings->gid != gid) {
        return true;
    }
    
    return false;

}

/* vim: set sts=4 sw=4 ts=8 expandtab ft=c: */
