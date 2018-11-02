//
// Created by falleuion on 10/28/18.
//

#include "trans_para.h"

int Quantum::parse_string(const std::string &str)
{
    module *mod;
    int res;

    mod = new_module_from_string(str.c_str());
    res = parse_module(mod);

    // pass parameter
    Quantum::add_to_hyfine_struct(mod->root);

    delete_module(mod);

    return res;
}


void Quantum::add_to_hyfine_struct(struct _OprtNode *node)
{
    std::shared_ptr<Quantum::HyfineStruct_t> data(new HyfineStruct_t);
    data.get()->opType_ = node->type_;

    // TODO: waiting implement..

}
