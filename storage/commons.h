//
// Created by falleuion on 10/4/18.
//

#ifndef COMMONS_H
#define COMMONS_H

#include <stdint.h>

enum OprtType
{
    TS_CREATE, TS_INSERT, TS_SELECT, TS_DELETE
};


static uint8_t __Sql_NOTNULLX = 0x01;
static uint8_t __Sql_AUTOINC = 0x02;
static uint8_t __Sql_UNIKEY = 0x04;
static uint8_t __Sql_PRIKEY = 0x08;
static uint8_t __Sql_KEY = 0x10;

static uint8_t __SqlInsOpt_LOWPRI = 0x01;           // Low Priority
static uint8_t __SqlInsOpt_DELAYED = 0x02;
static uint8_t __SqlInsOpt_HIGPRI = 0x04;           // High Priority
static uint8_t __SqlInsOpt_IGNORE = 0x08;

// expr 所使用的类型, 它们几个应该算作一组
static uint32_t __Sql_ExprINTNUM = 0x01;
static uint32_t __Sql_ExprNAME = 0x02;
static uint32_t __Sql_ExprUSERVAR = 0x04;
static uint32_t __Sql_ExprSTRING = 0x08;
static uint32_t __Sql_ExprBOOL = 0x10;

// expr 所使用的操作符
static uint32_t __Sql_ExprADD = 0x0001;
static uint32_t __Sql_ExprSUB = 0x0002;
static uint32_t __Sql_ExprMUL = 0x0004;
static uint32_t __Sql_ExprDIV = 0x0008;
static uint32_t __Sql_ExprMOD = 0x0010;
static uint32_t __Sql_ExprANDOP = 0x0020;
static uint32_t __Sql_ExprOR = 0x0040;
static uint32_t __Sql_ExprXOR = 0x0080;
static uint32_t __Sql_ExprNEG = 0x0100;
static uint32_t __Sql_ExprNOT = 0x0200;
static uint32_t __Sql_ExprBITOR = 0x0400;
static uint32_t __Sql_ExprBITAND = 0x0800;
static uint32_t __Sql_ExprBITXOR = 0x1000;


static uint8_t __SqlDelOpt_LOWPRI = 0x01;
static uint8_t __SqlDelOpt_QUICK = 0x02;
static uint8_t __SqlDelOpt_IGNORE = 0x04;


#endif //COMMONS_H
