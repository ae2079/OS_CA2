#include <sys/types.h>
#include <stdio.h>
//#include <string>
//#include <unistd.h>
#include <vector>
#include <dirent.h>

//#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1
#define TEST_CASE_DIR "testcases"

using namespace std;

int get_num_of_files(){
    DIR *dir;
    int num = 0;
    struct dirent *ep;     
    dir = opendir(TEST_CASE_DIR);

    if (dir != NULL)
    {
        while (ep = readdir (dir))
        num++;
        closedir (dir);
    }
    else
        perror ("Couldn't open the directory");

    return num;
}

int main() {
    //char write msg[BUFFER SIZE] = "Greetings";
    //char read msg[BUFFER SIZE];
    //int fd[2];
    //pid_t pid;
    /* create the pipe */
    int num_of_files = get_num_of_files();

    // if ( pipe (fd) == -1) {
    //     fprintf(stderr,"Pipe failed");
    //     return 1;
    // }
    // /* fork a child process */
    // pid = fork();
    // if (pid < 0) { /* error occurred */
    //     fprintf(stderr, "Fork Failed");
    //     return 1;
    // }
    // if (pid > 0) { /* parent process */
    //     /* close the unused end of the pipe */
    //     close(fd[READ END]);
    //     /* write to the pipe */
    //     write(fd[WRITE END], write msg, strlen(write msg)+1);
    //     /* close the write end of the pipe */
    //     close(fd[WRITE END]);
    // }
    // else { /* child process */
    //     /* close the unused end of the pipe */
    //     close(fd[WRITE END]);
    //     /* read from the pipe */
    //     read(fd[READ END], read msg, BUFFER SIZE);
    //     printf("read %s",read msg);
    // }
    // /* close the read end of the pipe */
    // close(fd[READ END]);
    // return 0;
}
