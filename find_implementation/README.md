Partial re-implementation of find called search, which recursively searches a directory and prints items it finds based on 
the specified: <br />
Options:

    -executable     File is executable or directory is searchable to user
    -readable       File readable to user
    -writable       File is writable to user
    -type [f|d]     File is of type f for regular file or d for directory

    -empty          File or directory is empty

    -name  pattern  Base of file name matches shell pattern
    -path  pattern  Path of file matches shell pattern

    -perm  mode     File's permission bits are exactly mode (octal)
    -newer file     File was modified more recently than file

    -uid   n        File's numeric user ID is n
    -gid   n        File's numeric group ID is n

Expressions:

    -print          Display file path (default)
    -exec cmd {} ;  Execute command on path
