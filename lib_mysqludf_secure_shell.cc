#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char* command;
    strcpy(command, "/bin/rbash ");
    strcat(command, args->args[0]);

    FILE *p = popen(command,"r");
    if(p == NULL) return -1

    while((ch=fgetc(p)) != EOF) { }

    int status = pclose(p);
    int exitcode = WEXITSTATUS(status);
    return exitcode;

}
