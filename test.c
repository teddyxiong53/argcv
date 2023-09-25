#include <stdio.h>
#include <stdbool.h>
#include "argcv.h"

int main(int argc, char* argv[]) {
    int myInt = 0;
    float myFloat = 0.0f;
    const char* myString = NULL;
    bool myBool = false;
    argcv_init(argc, argv);

    argcv_add_option("-i", "--int", ARGCV_INT, &myInt, "An integer option");
    argcv_add_option("-f", "--float", ARGCV_FLOAT, &myFloat, "A floating-point option");
    argcv_add_option("-s", "--string", ARGCV_STRING, &myString, "A string option");
    argcv_add_option("-b", "--bool", ARGCV_BOOL, &myBool, "A boolean option");

    argcv_parse();

    // Your code here to use the parsed options
    printf("myInt: %d\n", myInt);
    printf("myFloat: %f\n", myFloat);
    printf("myString: %s\n", myString ? myString : "NULL");
    printf("myBool: %s\n", myBool ? "true" : "false");
    argcv_destroy();
    return 0;
}
