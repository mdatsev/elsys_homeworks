//------------------------------------------------------------------------
// NAME: Martin Datsev
// CLASS: XIb
// NUMBER: 17
// PROBLEM: #2
// FILE NAME: shell.c
// FILE PURPOSE:
// reads commands from stdin and executes them wit parameters
// and pipe `|` can be used to redirect the output of the left
// command to the right command
//------------------------------------------------------------------------

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

char **parse_cmdline(const char *line);
char **parse_pipes(const char *line, int *size);
bool empty(const char *str);

//------------------------------------------------------------------------
// FUNCTION: main
// entry point of the program
//------------------------------------------------------------------------
int main()
{
    char *line = NULL;
    size_t len = 0;
    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);              //print out prompt
        ssize_t read = getline(&line, &len, stdin); //read a line

        if (read <= 0 || feof(stdin)) //check if end of input
            break;
        if (empty(line)) //check if empty command
            continue;
        if (line[read - 1] == '\n') //cut out newline
            line[read - 1] = '\0';
        int commands_count;
        char **commands = parse_pipes(line, &commands_count); //parse the commands
        int prev_pipe[2], next_pipe[2];                       // 2 pipes
        for (int i = 0; i < commands_count; i++)
        {
            const bool first = (i == 0);
            const bool last = (i == commands_count - 1);
            if (!last)
            {
                pipe(next_pipe); // create a pipe for each command except the last
            }
            pid_t pid = fork(); // create child process for the command
            if (pid < 0)
            {
                perror("fork");
            }
            else if (pid == 0)
            {
                if (!first)
                {
                    dup2(prev_pipe[0], STDIN_FILENO); // if not the first command take
                                                      // input from the previous pipe
                    close(prev_pipe[1]);              // close unused pipe ends
                    close(prev_pipe[0]);
                }
                if (!last)
                {

                    dup2(next_pipe[1], STDOUT_FILENO); // if not the last command
                                                       // redirect stdout to the next pipe
                    close(next_pipe[0]);
                    close(next_pipe[1]);
                }

                char **cmdargv = parse_cmdline(commands[i]); // parse command arguments
                                                             // from the command string

                execvp(cmdargv[0], cmdargv); // execute the command

                perror(cmdargv[0]); // if it didn't execute error
                free(cmdargv[0]);   // free everyting
                free(cmdargv);
                free(line);
                free(commands[0]);
                free(commands);
                exit(-1); // and exit the child process
            }
            if (!first)
            {
                close(prev_pipe[0]); // close unused previous pipe ends
                close(prev_pipe[1]);
            }
            prev_pipe[0] = next_pipe[0]; // the next pipe for the current command
            prev_pipe[1] = next_pipe[1]; // becomes the previous pipe for the next command
        }
        for (int i = 0; i < commands_count; i++)
        { // wait for all the child processes to finish
            wait(NULL);
        }
        free(commands[0]);
        free(commands);
    }
    free(line);
    return 0;
}

//------------------------------------------------------------------------
// FUNCTION: split (име на функцията)
// splits a string by a delimiter
// PARAMETERS:
// line - string to be split
// delimiter - separates the string by this character
// size - out param returning the number of substrings
//------------------------------------------------------------------------
char **split(const char *line, char delimiter, int *size)
{

    const char *start = line;
    for (int i = 0; line[i] == delimiter; i++)
    { // find the start of the command(if there's leading whitespace)
        start = &line[i + 1];
    }
    char *mutable = malloc((strlen(start) + 1) * sizeof(char)); // create a mutable string
    strcpy(mutable, start);                                     // copy into mutable string from the found start
    char **result = NULL;
    int argc = 0;
    char *beginning = &mutable[0];
    int result_size = 128;
    for (char *cur = &mutable[0];; cur++)
    {
        if (*cur == delimiter || *cur == '\0') // if found a delimier or the end of the string
        {
            if (cur - beginning == 0) // if not 2 delimiters next to each other
            {                         // to not have empty strings in between 2 delimiters
                beginning = cur + 1;  // the next string begins 1 after the delimiter
                if (*cur == '\0')     // if we reached the end
                    break;            // break,
                else                  // else-
                    continue;         // continue searching
            }
            argc++;

            if (argc + 1 > result_size)
                result_size *= 2; // manage memory
            result = realloc(result, result_size * sizeof(char *));
            result[argc - 1] = beginning; // point to the beggining of the substring
            beginning = cur + 1;
            if (*cur == '\0') // some duplicated logic but its too late zzz
                break;
            *cur = '\0'; // set the delimiter to `'\0'` to set the end of the string
        }
    }

    result[argc] = NULL; // last element NULL to be suitable for execv*
    if (size)
    {
        *size = argc; // out arg
    }
    return result;
}

//------------------------------------------------------------------------
// FUNCTION: parse_cmdline
// takes a command string and returns array suitable for execv*
// PARAMETERS:
// line - string to be split
//------------------------------------------------------------------------
char **parse_cmdline(const char *line)
{
    return split(line, ' ', NULL); // split by space
}

//------------------------------------------------------------------------
// FUNCTION: parse_pipes
// takes a command string and returns array of command string separated by pipe `|`
// PARAMETERS:
// line - string to be split
// size - out param - number of commands
//------------------------------------------------------------------------
char **parse_pipes(const char *line, int *size)
{
    return split(line, '|', size); // split by `|`
}

//------------------------------------------------------------------------
// FUNCTION: empty
// check if string is whitespace only
// PARAMETERS:
// str - string to be checked
//------------------------------------------------------------------------
bool empty(const char *str)
{
    for (const char *c = str; *c != '\0'; c++) // search through to the end
    {
        if (*c != ' ' && *c != '\n' && *c != '|' && *c != '\t') // if ant non-whitespace
            return false;                                       // return fase
    }
    return true; // else - true
}