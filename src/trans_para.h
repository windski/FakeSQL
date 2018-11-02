//
// Created by falleuion on 10/28/18.
//

#ifndef TRANS_PARA_H
#define TRANS_PARA_H

#include "hyperfine_structure.hpp"
#include "module.h"
#include "commons.h"
#include <memory>

namespace Quantum {

int parse_string(const std::string &str);

void add_to_hyfine_struct(struct _OprtNode *node);

typedef std::vector<std::shared_ptr<Quantum::HyfineStruct_t>> hyfineList_t;
static hyfineList_t data;

}


#endif //TRANS_PARA_H
