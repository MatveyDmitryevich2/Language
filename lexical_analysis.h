#ifndef LEXICAL_ANALYSIS_H
#define LEXICAL_ANALYSIS_H

#include <stdio.h>
#include <stddef.h>

#include "utils.h"


static const char LEFT_BRACKET_ = '(';
static const char RIGHT_BRACKET_ = ')';

static const char ADD_          [] = "+";
static const char SUB_          [] = "-";
static const char MUL_          [] = "*";
static const char DIV_          [] = "/";
static const char POWER_        [] = "^";

static const char SIN_          [] = "sin";
static const char COS_          [] = "cos";
static const char TG_           [] = "tg";
static const char CTG_          [] = "ctg";
static const char SH_           [] = "sh";
static const char CH_           [] = "ch";
static const char TH_           [] = "th";
static const char CTH_          [] = "cth";
static const char ARCSIN_       [] = "arcsin";
static const char ARCCOS_       [] = "arccos";
static const char ARCTG_        [] = "arctg";
static const char ARCCTG_       [] = "arcctg";

static const char LOG_          [] = "log";
static const char LN_           [] = "ln";
static const char EXP_          [] = "exp";

static const char DOT = '.';
static const char UNDERSCORE = '_';
static const char END = '$';
static const size_t MAX_QUANTITY_IDENTIFIERS = 100;

enum Bracket
{
    Bracket_LEFT = 0,
    Bracket_RIGHT = 1,
};


enum Types
{
    Types_VARIABLE      = 1,
    Types_NUMBER        = 2,
    Types_OPERATION     = 3,
    Types_LEFT_BRACKET  = 4,
    Types_RIGHT_BRACKET = 5,
    Types_END_SYMBOL    = 6,
};


enum Operation
{
    Operation_NO_OPERATION = 0,
    Operation_ADD          = 1,
    Operation_SUB          = 2,
    Operation_MUL          = 3,
    Operation_DIV          = 4,
    Operation_POWER        = 5,
    Operation_SIN          = 6,
    Operation_COS          = 7,
    Operation_TG           = 8,
    Operation_CTG          = 9,
    Operation_SH           = 10,
    Operation_CH           = 11,
    Operation_TH           = 12,
    Operation_CTH          = 13,
    Operation_ARCSIN       = 14,
    Operation_ARCCOS       = 15,
    Operation_ARCTG        = 16,
    Operation_ARCCTG       = 17,
    Operation_LOG          = 18,
    Operation_LN           = 19,
    Operation_EXP          = 20,
};


struct Identifiers
{
    size_t index_first_symbol;
    size_t index_last_symbol;
    size_t size_in_char;
    
    Types type;

    union Argument
    {
        char variable;
        double number;
        Operation operation;
    } argument;
};

Identifiers* Lexical_analysis(Info_buffer* info_buffer);

#endif //LEXICAL_ANALYSIS_H