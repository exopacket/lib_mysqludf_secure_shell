#include <assert.h>
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
    return system(args->args[0]);
}
