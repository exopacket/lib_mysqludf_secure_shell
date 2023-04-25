#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "mysql.h"
#include "mysql/udf_registration_types.h"

#if defined (__WIN32__)
#define SHELL "cmd.exe"
#define FLAG "/C"
#else
#define FLAG "-c"
#ifdef SECURE_SHELL
#define SHELL "/usr/bin/rbash"
#else
#define SHELL "/usr/bin/bash"
#endif
#endif

#ifndef SECURE_SHELL
extern "C" bool sys_run_init(UDF_INIT *initid, UDF_ARGS *args,
                              char *message) {

    if(args->arg_count == 2
       && args->arg_type[0]==STRING_RESULT
          && args->arg_type[1]==STRING_RESULT){
        return false;
    } else {
        strcpy(
                message
                ,	"Expected exactly two string type parameters"
        );
        return true;
    }

}

extern "C" unsigned long long sys_run(UDF_INIT *, UDF_ARGS *args,
                                       unsigned char *is_null, unsigned char *) {

    //use default shell
    //return system(args->args[0]);

    //use restricted shell
    int child;
    int fd[2];
    pipe(fd);
    if ( (child = fork() ) == -1){
        return 1;
    } else if( child == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        execlp(args->args[0], args->args[1], NULL);
    }
    int status;
    wait(&status);

    return WEXITSTATUS(status);

}
#endif

extern "C" bool sys_exec_init(UDF_INIT *initid, UDF_ARGS *args,
                                   char *message) {

    unsigned int i=0;
    if(args->arg_count == 1
       && args->arg_type[i]==STRING_RESULT){
        return false;
    } else {
        strcpy(
                message
                ,	"Expected exactly one string type parameter"
        );
        return true;
    }

}

extern "C" unsigned long long sys_exec(UDF_INIT *, UDF_ARGS *args,
                                unsigned char *is_null, unsigned char *) {

    //use default shell
    //return system(args->args[0]);

    //use restricted shell
    int child;
    int fd[2];
    pipe(fd);
    if ( (child = fork() ) == -1){
        return 1;
    } else if( child == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        execlp(SHELL, args->args[0], NULL);
    }
    int status;
    wait(&status);

    return WEXITSTATUS(status);

}

extern "C" bool sys_shell_init(UDF_INIT *initid, UDF_ARGS *args,
                              char *message) {

    unsigned int i=0;
    if(args->arg_count == 1
       && args->arg_type[i]==STRING_RESULT){
        return false;
    } else {
        strcpy(
                message
                ,	"Expected exactly one string type parameter"
        );
        return true;
    }

}

extern "C" unsigned long long sys_shell(UDF_INIT *, UDF_ARGS *args,
                                       unsigned char *is_null, unsigned char *) {

    //use default shell
    //return system(args->args[0]);

    //use restricted shell
    int child;
    int fd[2];
    pipe(fd);
    if ( (child = fork() ) == -1){
        return 1;
    } else if( child == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        execlp(SHELL, SHELL, FLAG, args->args[0], NULL);
    }
    int status;
    wait(&status);

    return WEXITSTATUS(status);

}
