#include "argcv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static argcv_arg* options = NULL;
static int num_options = 0;
static int argc;
static char** argv;

void argcv_init(int _argc, char** _argv) {
    argc = _argc;
    argv = _argv;
    options = NULL;
    num_options = 0;
}

static void print_usage() {
    printf("Usage:\n");
    for (int i = 0; i < num_options; i++) {
        printf("  %s, %s: %s\n", options[i].shortopt, options[i].longopt, options[i].description);
    }
}


void argcv_add_option(const char* shortopt, const char* longopt, argcv_arg_type type, void* variable, const char* description) {
    if (strlen(shortopt) !=2) {
        fprintf(stderr, "shortopt should be like -x");
        exit(1);
    }
    num_options++;
    options = (argcv_arg*)realloc(options, num_options * sizeof(argcv_arg));

    options[num_options - 1].shortopt = shortopt;
    options[num_options - 1].longopt = longopt;
    options[num_options - 1].type = type;
    options[num_options - 1].value = variable;
    options[num_options - 1].description = description;
}

void argcv_parse() {
    for (int i = 1; i < argc; i++) {
        const char* arg = argv[i];

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                // Long option
                const char* longopt = arg + 2;
                for (int j = 0; j < num_options; j++) {
                    if (options[j].longopt && strcmp(options[j].longopt, longopt) == 0) {
                        // Matched long option
                        i++;
                        if (i < argc) {
                            if (options[j].type == ARGCV_INT) {
                                *((int*)options[j].value) = atoi(argv[i]);
                            } else if (options[j].type == ARGCV_FLOAT) {
                                *((float*)options[j].value) = atof(argv[i]);
                            } else if (options[j].type == ARGCV_STRING) {
                                *((const char**)options[j].value) = argv[i];
                            } 
                        } else {
                            if (options[j].type == ARGCV_BOOL) {
                                *((bool*)options[j].value) = true;
                            } else {
                                fprintf(stderr, "Error: Missing value for option --%s\n", longopt);
                                print_usage();
                                exit(1);
                            }
                        }
                        break;
                    }
                }
            } else {
                // Short option
                char shortopt = arg[1];
                for (int j = 0; j < num_options; j++) {
                    if (options[j].shortopt && options[j].shortopt[1] == shortopt) {
                        // Matched short option
                        i++;
                        if (i < argc) {
                            if (options[j].type == ARGCV_INT) {
                                *((int*)options[j].value) = atoi(argv[i]);
                            } else if (options[j].type == ARGCV_FLOAT) {
                                *((float*)options[j].value) = atof(argv[i]);
                            } else if (options[j].type == ARGCV_STRING) {
                                *((const char**)options[j].value) = argv[i];
                            }
                        } else {
                            if (options[j].type == ARGCV_BOOL) {
                                *((bool*)options[j].value) = true;
                            } else {
                                fprintf(stderr, "Error: Missing value for option -%c\n", shortopt);
                                print_usage();
                                exit(1);
                            }

                        }
                        break;
                    }
                }
            }
        }
    }
}
void argcv_destroy() {
    free(options);
    options = NULL;
    num_options = 0;
}
