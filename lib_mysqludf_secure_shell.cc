#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unistd.h"
#include <sys/wait.h>

#include "mysql.h"
#include "mysql/udf_registration_types.h"

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
        execlp("/bin/rbash", "/bin/rbash", "-c", args->args[0], NULL);
    }
    wait(NULL);

    return 0;

}
