#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const static char match_string[] = "no" "checkin";


#define Array_Count(a) ((sizeof(a))/(sizeof(*a)))
#define Assert(Condition, ErrorText1, ErrorText2) do{\
if (!(Condition)){\
printf("%s%s\n", ErrorText1, ErrorText2);\
exit(1);\
}}while(0)

#if _MSC_VER
#define Open_Pipe(Command, Mode) _popen(Command, Mode)
#define Close_Pipe(Handle) _pclose(Handle)
#else
#define Open_Pipe(Command, Mode) popen(Command, Mode)
#define Close_Pipe(Handle) pclose(Handle)
#endif

int main()
{
    int match_length = (int)strlen(match_string);
    int match_found = 0;
    
    char *git_list_command = "git diff --name-only --staged";
    FILE *git_list_query = Open_Pipe(git_list_command, "r");
    Assert(git_list_query, "Failed to execute command: ", git_list_command);
    
    char path[4096];
    while (fgets(path, sizeof(path), git_list_query) != 0)
    {
        char *new_line = strstr(path, "\n");
        if (new_line) { *new_line = 0; }
        
        //printf("[path] \"%s\"\n", path);
        
        char git_content_command[4096 + 256];
        snprintf(git_content_command, sizeof(git_content_command), "git show :%s", path);
        
        FILE *git_content = Open_Pipe(git_content_command, "r");
        Assert(git_content, "Failed to execute command: ", git_content_command);
        
        
        // NOTE: This search method won't work for strings
        // that repeat their starting character - like: "noncheck"
        int line = 1;
        int column = 1;
        int matched = 0;
        
        for (int c = fgetc(git_content);
             c != EOF;
             c = fgetc(git_content))
        {
            if (c == match_string[matched])
            {
                ++matched;
                if (matched == match_length)
                {
                    printf("[%s found] File: %s; Line: %d; Column: %d\n",
                           match_string, path, line, column-matched+1);
                    matched = 0;
                    match_found = 1;
                }
            }
            else
            {
                matched = 0;
                if (c == match_string[matched])
                {
                    ++matched;
                }
                else if (c == '\n')
                {
                    column = 0;
                    ++line;
                }
            }
            
            
            if ((c & 0xc0) != 0x80) // NOTE: Count unicode characters
            {
                ++column;
            }
        }
        
        
        Close_Pipe(git_content);
    }
    
    Close_Pipe(git_list_query);
    
    return match_found;
}