#ifndef ARGCV_H
#define ARGCV_H

#include <stdbool.h>


typedef enum {
    ARGCV_INT,
    ARGCV_FLOAT,
    ARGCV_STRING,
    ARGCV_BOOL
} argcv_arg_type;


typedef struct {
    const char* shortopt;
    const char* longopt;
    argcv_arg_type type;
    void* value;
    const char* description;
} argcv_arg;


void argcv_init(int argc, char* argv[]);


void argcv_parse();


void argcv_add_option(const char* shortopt, const char* longopt, argcv_arg_type type, void* variable, const char* description);
void argcv_destroy();

#endif // ARGCV_H
