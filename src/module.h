//
// Created by falleuion on 8/17/18.
//

#ifndef MODULE_H_
#define MODULE_H_

#ifdef __cplusplus
extern "C" {
# include <cstdio>
#else
# include <stdio.h>
#endif


#include "ast.h"

typedef struct {
    union {
        FILE* filefp;
        int fileno;
    } src;

    struct _OprtNode *root;
} module;


module* new_module_from_string(const char* src);

void delete_module(module* mod);

int parse_module(module* mod);

#ifdef __cplusplus
}
#endif


#endif //MODULE_H_
