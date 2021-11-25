#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include <fstream>
#include <iostream>

#define BUFFER_SIZE 25
#define OUTPUT_SIZE 100000
#define READ_END 0
#define WRITE_END 1
#define TEST_CASE_DIR "testcases"
#define OUTPUT_FILE "output.csv"

const char* named_pipe = "namedpipe";

using namespace std;

int get_num_of_files(){
    DIR *dir;
    int num = 0;
    struct dirent *ep;     
    dir = opendir(TEST_CASE_DIR);

    if (dir != NULL)
    {
        while(ep = readdir (dir))
        num++;
        closedir(dir);
    }
    else
        perror("Couldn't open the directory");

    return num - 2;
}

int main() {
    int num_of_files = get_num_of_files();

    for(int i = 0; i < num_of_files; i++){
        int fd[2];
        /* create the pipe */
        if ( pipe (fd) == -1) {
            perror("Pipe failed");
            return -1;
        }
        pid_t temp = fork();
        
        if (temp < 0) { /* error occurred */
            perror("Fork Failed");
            return -1;
        }
        else if (temp == 0) { /* child process */
            sleep(i);
            char read_end[BUFFER_SIZE];
            sprintf(read_end, "%d", fd[READ_END]);
            char write_end[BUFFER_SIZE];
            sprintf(write_end, "%d", fd[WRITE_END]);
            execlp ("./map.out", read_end, write_end, named_pipe, NULL);
        }
        else{
            /* close the unused end of the pipe */
            close(fd[READ_END]);
            /* write to the pipe */
            char file[BUFFER_SIZE];
            sprintf(file, "%s/%d.csv", TEST_CASE_DIR,i+1);
            write(fd[WRITE_END], file, strlen(file)+1);
            /* close the write end of the pipe */
            close(fd[WRITE_END]);
        }
    }

    int fd[2];
    /* create the pipe */
    if ( pipe (fd) == -1) {
        perror("Pipe failed");
        return -1;
    }
    pid_t pid = fork();
    if (pid < 0) { /* error occurred */
        fprintf(stderr, "Fork Failed");
        return -1;
    }
    if (pid > 0) { /* parent process */
        /* close the unused end of the pipe */
        close(fd[WRITE_END]);
        char out[OUTPUT_SIZE];
        /* read from the pipe */
        read(fd[READ_END], out, OUTPUT_SIZE);
        /* close the read end of the pipe */
        close(fd[READ_END]);
        ofstream out_file; 
        out_file.open(OUTPUT_FILE);
        out_file << out;
        out_file.close();
    }
    else { /* child process */
        char read_end[BUFFER_SIZE];
        sprintf(read_end, "%d", fd[READ_END]);
        char write_end[BUFFER_SIZE];
        sprintf(write_end, "%d", fd[WRITE_END]);
        char num_of_maps[BUFFER_SIZE];
        sprintf(num_of_maps, "%d", num_of_files);
        execlp ("./reduce.out", read_end, write_end, named_pipe, num_of_maps, NULL);
    }

    return 0;
}
