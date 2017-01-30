#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>    // for fork(), pid_t
#include <sys/types.h>
#include <sys/wait.h>
const char * const PARADITY[] = { "even","odd" };
int orig_numb;
int count_bits(int val){
    if(val==0){
    return 0;
    }
    return pcount_bits(val);
}
int pcount_bits(int val){
    pid_t pidn_1;
    int bits_1;
    int status;
    if(val == 0){
    exit(0);
    }
    if ((pidn_1 = fork()) == 0) {
        pcount_bits(val/2);
    }
    while(waitpid(pidn_1,&status,0)>0){
        if (WIFEXITED(status))
            bits_1 = WEXITSTATUS(status);
    }
    if(val==orig_numb){
    return val%2 + bits_1;
    }else{
        exit(val%2+bits_1);
    }



}
int main(int argc, char** argv)
{   int val = -1;
    if(argc!=2||atoi(argv[1]) < 0){
    printf("Please enter valid input. %d is not valid input",val);
    return -1;
    }
    val = atoi(argv[1]);
    orig_numb = val;
    printf("The value %d has a  %s paridity",val,PARADITY[count_bits(val)%2]/*count_bits(val)%2==0?"Even":"Odd"*/);
                                                                            //^^this is a better way of acomplishing what we want


}
