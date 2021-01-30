#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define No_Checkin_String "no" "checkin"


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

int main(int arg_count, char *args[])
{
    char *git_command = "git diff --name-only --staged";
    FILE *git_query = Open_Pipe(git_command, "r");
    Assert(git_query, "Failed to execute command: ", git_command);
    
    char path[2048];
    while (fgets(path, sizeof(path), git_query) != 0)
    {
        char *new_line = strstr(path, "\n");
        if (new_line) { *new_line = 0; }
        
        //printf("[path] \"%s\"\n", path);
        
        FILE *file = fopen(path, "rb");
        Assert(file, "Failed to open file: ", path);
        
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        rewind(file);
        
        if (file_size > 0)
        {
            char *memory = (char *)malloc(file_size+1);
            Assert(memory, "Failed to allocate memory for file: ", path);
            
            size_t read_bytes = fread(memory, 1, file_size, file);
            Assert(read_bytes == file_size, "Whole file couldn't be read: ", path);
            memory[read_bytes] = 0;
            
            // TODO(fda0): Implement my own str search that count lines and pos
            char *search = strstr(memory, No_Checkin_String);
            Assert(search == 0, No_Checkin_String " found in file: ", path);
            
            free(memory);
        }
        
    }
    
    Close_Pipe(git_query);
    return 0;
}