//
// Created by falleuion on 8/17/18.
//

#include "module.h"
#include "parser.h"
#include "scanner.h"

#ifdef __cplusplus
extern "C" {
#endif


module *new_module_from_string(const char *src)
{
    module *mod = (module *) malloc(sizeof(module));
    // remove the const property
    mod->src.filefp = fmemopen((char *)src, strlen(src) + 1, "r");
    return mod;
}

void delete_module(module* mod)
{
    if(mod->root != NULL) {
        del_oprt_node(mod->root);
    }
    fclose(mod->src.filefp);
    free(mod);
}

int parse_module(module* mod)
{
    yyscan_t sc;
    int res;

#ifdef DEBUG
    yydebug = 1;
#endif

    yylex_init(&sc);
    yyset_in(mod->src.filefp, sc);
    res = yyparse(sc, mod);
    yylex_destroy(sc);


    return res;
}

#ifdef __cplusplus
}
#endif