//--------------------------------------------
// NAME: Martin Datsev
// CLASS: XIb
// NUMBER: 17
// PROBLEM: #4
// FILE NAME: ls.c
// FILE PURPOSE:
// shows files in a directory
// -l - show more detailed information
// -A - show hidden files
// -R - recursively iterate directories
//---------------------------------------------

#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>
#include <pwd.h>
#include <time.h>
#include <grp.h>
#define L_BLOCK_SIZE 1024
int nCols = 8;
struct
{
    bool A;
    bool l;
    bool R;
    bool multiple_files;
} flags;

typedef struct
{
    int length;
    int capacity;
    int max_row_length;
    const char **rows;
    bool no_format;
    const char *format;
} column_t;

typedef struct
{
    char *path;
    struct stat st;
    bool invalid;
} file_t;

//--------------------------------------------
// FUNCTION: add_row
// adds a row to a column, managing memory and max length ( for padding)
// PARAMETERS:
// col - column to add to
// value - value to add
//----------------------------------------------
void add_row(column_t *col, const char *value)
{

    if (col->length == col->capacity)
    {
        int new_capacity = col->length > 0 ? col->length * 2 : 1;
        col->rows = realloc(col->rows, new_capacity * sizeof(char *));
        col->capacity = new_capacity;
    }
    int len = strlen(value);
    if (len > col->max_row_length)
    {
        col->max_row_length = len;
    }
    col->rows[col->length] = value;
    col->length++;
}

//--------------------------------------------
// FUNCTION: print_columns
// prints an array of columns (like table)
// PARAMETERS:
// columns - columns to print
// free_rows - whether to free rows after printing
//----------------------------------------------
void print_columns(column_t *columns, bool free_rows)
{
    for (int row = 0; row < columns[0].length; row++)
    {
        for (int col = 0; columns[col].length > row; col++)
        {
            if (col != 0)
                putchar(' ');
            const char *format = columns[col].format;
            format = format ? format : "%*s";
            const char *data = columns[col].rows[row];
            if (columns[col].no_format)
                printf("%s", data);
            else
                printf(format, columns[col].max_row_length, data);
            if (free_rows)
            {
                free((void *)data);
            }
        }
        puts("");
    }
}

//--------------------------------------------
// FUNCTION: get_file_info
// adds an entry to the array of colums about that file
// PARAMETERS:
// file - file to add
// columns - columns to add to
//----------------------------------------------
void get_file_info(file_t file, column_t *columns)
{
    __mode_t m = file.st.st_mode;
    char *perm = malloc(11 * sizeof(char));
    perm[0] = S_ISDIR(m)
                  ? 'd'
                  : S_ISREG(m)
                        ? '-'
                        : S_ISBLK(m)
                              ? 'b'
                              : S_ISCHR(m)
                                    ? 'c'
                                    : S_ISFIFO(m)
                                          ? 'p'
                                          : S_ISLNK(m)
                                                ? 'l'
                                                : S_ISSOCK(m)
                                                      ? 's'
                                                      : '?';
    if (flags.l)
    {
        perm[1] = (m & S_IRUSR) ? 'r' : '-';
        perm[2] = (m & S_IWUSR) ? 'w' : '-';
        perm[3] = (m & S_IXUSR) ? 'x' : '-';
        perm[4] = (m & S_IRGRP) ? 'r' : '-';
        perm[5] = (m & S_IWGRP) ? 'w' : '-';
        perm[6] = (m & S_IXGRP) ? 'x' : '-';
        perm[7] = (m & S_IROTH) ? 'r' : '-';
        perm[8] = (m & S_IWOTH) ? 'w' : '-';
        perm[9] = (m & S_IXOTH) ? 'x' : '-';
        perm[10] = 0;
    }
    else
    {
        perm[1] = 0;
    }

    int columnIndex = 0;
    add_row(&columns[columnIndex++], perm);
    if (flags.l)
    {
        char *nHardLinks = malloc(21 * sizeof(char));
        sprintf(nHardLinks, "%lu", file.st.st_nlink);
        add_row(&columns[columnIndex++], nHardLinks);
        columns[columnIndex].format = "%-*s";
        add_row(&columns[columnIndex++], strdup(getpwuid(file.st.st_uid)->pw_name));
        columns[columnIndex].format = "%-*s";
        add_row(&columns[columnIndex++], strdup(getgrgid(file.st.st_gid)->gr_name));
        char *size = malloc(21 * sizeof(char));
        sprintf(size, "%lu", file.st.st_size);
        add_row(&columns[columnIndex++], size);
        char *time = malloc(80);
        struct tm *localtm = localtime(&file.st.st_mtime);
        strftime(time, 80, "%b %-2d %H:%M", localtm);
        add_row(&columns[columnIndex++], time);
    }
    const char *name = strrchr(file.path, '/');
    columns[columnIndex].no_format = true;
    add_row(&columns[columnIndex++], strdup(name ? name + 1 : file.path));
}

//--------------------------------------------
// FUNCTION: getFlags
// parses and sets the flags
// PARAMETERS:
// argc - program argument count
// argv - program argument values
//----------------------------------------------
void getFlags(int argc, char **argv)
{
    int c;

    while ((c = getopt(argc, argv, "lAR")) != -1)
        switch (c)
        {
        case 'A':
            flags.A = 1;
            break;
        case 'l':
            flags.l = 1;
            break;
        case 'R':
            flags.R = 1;
            break;
        default:
            fprintf(stderr, "Could not parse option");
            exit(1);
        }
}

//--------------------------------------------
// FUNCTION: get_files_from_argv
// parses the files from argv
// PARAMETERS:
// argc - program argument count
// argv - program argument values
// files - files array to store the files
// RETURNS:
// number of files parsed
//----------------------------------------------

int get_files_from_argv(int argc, char **argv, file_t **files)
{
    int realargc = argc - optind;
    int nFiles = realargc > 1 ? realargc : 1;
    *files = malloc(nFiles * sizeof(file_t));
    if (realargc >= 1)
        for (int i = optind; i < argc; i++)
            (*files)[i - optind].path = strdup(argv[i]);
    else
        (*files)[0].path = strdup(".");
    for (int i = 0; i < nFiles; i++)
    {
        if (stat((*files)[i].path, &((*files)[i].st)) != 0)
        {
            char buffer[1024];
            sprintf(buffer, "ls: cannot access %s", (*files)[i].path);
            perror(buffer);
            (*files)[i].invalid = true;
        }
    }
    if (nFiles > 1)
        flags.multiple_files = true;
    return nFiles;
}

//--------------------------------------------
// FUNCTION: get_files_from_argv
// gets the files from a directory
// PARAMETERS:
// dir_path - name of the directory
// files - files array to store the files
// RETURNS:
// number of files parsed
//----------------------------------------------
int get_files_from_dir(const char *dir_path, file_t **files)
{
    DIR *dir = opendir(dir_path);
    int count = 0;
    if (dir != NULL)
    {
        /* print all the files and directories within directory */
        for (struct dirent *file; (file = readdir(dir)) != NULL;)
        {
            if (!(strcmp(file->d_name, ".") == 0 ||
                  strcmp(file->d_name, "..") == 0) &&
                (file->d_name[0] != '.' || flags.A))
            {
                *files = realloc(*files, (count + 1) * sizeof(file_t));
                int size = (strlen(dir_path) + 1 + strlen(file->d_name) + 1) * sizeof(char);
                char *path = malloc(size);
                sprintf(path, "%s/%s", dir_path, file->d_name);
                (*files)[count].invalid = false;
                if (stat(path, &((*files)[count].st)) != 0)
                {
                    char buffer[1024];
                    sprintf(buffer, "ls: cannot access %s", file->d_name);
                    perror(buffer);
                    (*files)[count].invalid = true;
                }
                (*files)[count].path = path;
                //print_file_line(temp);
                //free(path);
                count++;
            }
        }
        closedir(dir);
    }
    else
    {
        char buffer[1024];
        sprintf(buffer, "ls: cannot open directory %s", dir_path);
        perror(buffer);
        return -1;
    }
    return count;
}

bool reg_file_args;
//--------------------------------------------
// FUNCTION: free_files
// frees dynamically allocated memory in the files
// PARAMETERS:
// files - files array
// count - length of the files array
//----------------------------------------------
void free_files(file_t *files, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(files[i].path);
    }
}

//--------------------------------------------
// FUNCTION: print_files
// prints files
// PARAMETERS:
// files - files to print
// count - number of files
// recursion_depth - depth to recursively iterate directories
// skip_files - don't print files
// skip_dirs - don't print dirs
// dir_as_file - print directories as files
//----------------------------------------------
void print_files(file_t *files, int count, int recursion_depth, bool skip_files, bool skip_dirs, bool dir_as_file)
{
    column_t *columns = calloc(nCols, sizeof(column_t));
    for (int i = 0; i < count; i++)
    {
        if (files[i].invalid)
            continue;
        if (S_ISDIR(files[i].st.st_mode) && skip_dirs)
            continue;
        if (S_ISDIR(files[i].st.st_mode) && recursion_depth != 0 && !dir_as_file)
        {
            file_t *dir_files = 0;
            int nFiles = get_files_from_dir(files[i].path, &dir_files);
            if (nFiles < 0)
                continue;
            if (flags.multiple_files || flags.R)
            {
                if (reg_file_args)
                    putchar('\n');
                printf("%s:\n", files[i].path);
            }
            int total = 0;
            if (flags.l)
            {
                for (int i = 0; i < nFiles; i++)
                {
                    total += dir_files[i].st.st_blocks * 512 / L_BLOCK_SIZE;
                }
                printf("total %d\n", total);
            }
            print_files(dir_files, nFiles, 0, false, false, true);
            print_files(dir_files, nFiles, recursion_depth - 1, true, false, false);
            free_files(dir_files, nFiles);
            free(dir_files);
        }
        else if (!skip_files)
        {
            get_file_info(files[i], columns);
        }
    }
    if (columns->length > 0)
    {
        reg_file_args = true;
        print_columns(columns, true);
    }
    for (int i = 0; i < nCols; i++)
    {
        free(columns[i].rows);
    }
    free(columns);
}

//--------------------------------------------
// FUNCTION: main
// entry point of program
// calls getFlags, gets the fies from argv with get_files_from_argv, prints them and frees the memory
// PARAMETERS:
// argc - command line arguments count
// argv - command line arguments values
//----------------------------------------------
int main(int argc, char **argv)
{
    getFlags(argc, argv);
    file_t *files;
    int nFiles = get_files_from_argv(argc, argv, &files);
    print_files(files, nFiles, flags.R ? -1 : 1, false, true, false);
    print_files(files, nFiles, flags.R ? -1 : 1, true, false, false);
    free_files(files, nFiles);
    free(files);
    return 0;
}