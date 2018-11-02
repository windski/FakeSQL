%require "3.0.4"

%define api.pure full
%lex-param {void *scanner}
%parse-param {void *scanner}{module *mod}

%define parse.trace
%define parse.error verbose

%{

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdint.h>

#include "ast.h"
#include "parser.h"
#include "module.h"
#include "scanner.h"

void emit(char *s, ...);
void yyerror(const char *s, ...);

// 用于内部数据结构的初始化, 在line:492~ 之后调用...
static struct _DataType newDataTypeNode()
{
    struct _DataType data;
    bzero(&data, sizeof(struct _DataType));
    return data;
}

// 代码大量类似...不如直接写个宏
#define setExprVar(node, ltree, rtree, type)    \
    (node)->ltree_ = ltree;                     \
    (node)->rtree_ = rtree;                     \
    (node)->type_ = type

%}
%debug

%code requires
{
#include "module.h"
#include "ast.h"
}


%union {
    int intval;
    double floatval;
    char *strval;
    int subtok;

    struct _OprtNode *oprtNode_p;
    struct _DefOpts *defOpts_p;
    uint8_t uintval8;
    uint64_t uintval64;
    struct _DataType dataType_t;
    columns_list_t *colList_p;
    struct _TablList *tablList_p;
    
    struct _ExprVar *exprVar_p;
    struct _ExprVarCon *exprVarCon_p;
}


%token <strval> NAME
%token <strval> STRING
%token <intval> INTNUM
%token <intval> BOOL
%token <floatval> APPROXNUM
%token <strval> USERVAR

%right ASSIGN
%left OR
%left XOR
%left ANDOP
%nonassoc IN IS LIKE REGEXP
%left NOT '!'
%left BETWEEN
%left <subtok> COMPARISON
%left '|'
%left '&'
%left <subtok> SHIFT
%left '+' '-'
%left '*' '/' MOD '%'
%left '^'

%nonassoc UMINUS

%token ADD
%token ALL
%token ALTER
%token ANALYZE
%token AND
%token ANY
%token AS
%token ASC
%token AUTO_INCREMENT

%token BEFORE
%token BETWEEN
%token BIGINT
%token BINARY
%token BIT
%token BLOB
%token BOTH
%token BY

%token CALL
%token CYCLE
%token CASCADE
%token CASE
%token CHANGE
%token CHAR
%token CHECK
%token COLLATE
%token COLUMN
%token COMMIT
%token COMMENT
%token CONDITION
%token CONSTRAINT
%token CONTINUE
%token CONVERT
%token CREATE
%token CROSS
%token CURRENT_DATE
%token CURRENT_TIME
%token CURRENT_TIMESTAMP
%token CURRENT_USER
%token CURSOR
%token COMPARSION

%token DATA
%token DATABASE
%token DATABASES
%token DATE
%token DATETIME
%token DAY_HOUR
%token DAY_MICROSECOND
%token DAY_MINUTE
%token DAY_SECOND
%token DECIMAL
%token DECLARE
%token DEFAULT
%token DELAYED
%token DELETE
%token DAY
%token DEC
%token DEFERRABLE
%token DESC
%token DESCRIBE
%token DETERMINISTIC
%token DISTINCT
%token DISTINCTROW
%token DIV
%token DOUBLE
%token DROP
%token DUAL
%token DEPTH
%token DYNAMIC

%token EACH
%token ELSE
%token ELSEIF
%token ENCLOSED
%token END
%token EQUALS
%token ESCAPE
%token EVERY
%token EXCEPT
%token EXCEPTION
%token EXEC
%token ENUM
%token ESCAPED
%token <subtok> EXISTS
%token EXIT
%token EXPLAIN

%token FETCH
%token FIRST
%token FLOAT
%token FOR
%token FORCE
%token FOREIGN
%token FROM
%token FULL
%token FULLTEXT
%token FUNCTION

%token GLOBAL
%token GROUPING
%token GRANT
%token GROUP

%token HAVING
%token HOST
%token HOUR
%token HIGH_PRIORITY
%token HOUR_MICROSECOND
%token HOUR_MINUTE
%token HOUR_SECOND

%token IF
%token IGNORE
%token IN
%token IDENTITY
%token INDEX
%token INFILE
%token INNER
%token INOUT
%token INSENSITIVE
%token INSERT
%token INT
%token INTEGER
%token INITIALIZE
%token INPUT
%token ISOLATION
%token INTERVAL
%token INTO
%token ITERATE
%token INDICATOR

%token JOIN

%token KEY
%token KEYS
%token KILL

%token LANGUAGE
%token LARGE
%token LEADING
%token LEAVE
%token LEFT
%token LAST
%token LESS
%token LIKE
%token LIMIT
%token LINES
%token LOAD
%token LOCALTIME
%token LOCALTIMESTAMP
%token LOCK
%token LONG
%token LONGBLOB
%token LONGTEXT
%token LOOP
%token LOW_PRIORITY

%token MATCH
%token MEDIUMBLOB
%token MEDIUMINT
%token MEDIUMTEXT
%token MINUTE_MICROSECOND
%token MINUTE_SECOND
%token MOD
%token MODIFIES
%token MINUTE
%token MODIFY
%token MONTH
%token MODULE

%token NAMES
%token NATIONAL
%token NATURAL
%token NOT
%token NO_WRITE_TO_BINLOG
%token NULLX
%token NUMBER
%token NEW
%token NEXT
%token NONE
%token NO
%token NULLOP
%token NUMERIC

%token OBJECT
%token OF
%token OFF
%token OLD
%token ON
%token ONDUPLICATE
%token OPTIMIZE
%token OPTION
%token OPTIONALLY
%token OR
%token ORDER
%token OUT
%token OUTER
%token OUTFILE
%token OPERATION
%token OPEN
%token ONLY
%token OUTPUT

%token PRECISION
%token PRIMARY
%token PROCEDURE
%token PURGE
%token PUBLIC

%token QUICK

%token READ
%token READS
%token REAL
%token REFERENCES
%token REGEXP
%token RELEASE
%token RENAME
%token REPEAT
%token REPLACE
%token REQUIRE
%token RESTRICT
%token RETURN
%token REVOKE
%token RIGHT
%token RELATIVE
%token ROLLUP
%token RESULT
%token ROW

%token SCHEMA
%token SCHEMAS
%token SECOND_MICROSECOND
%token SELECT
%token SENSITIVE
%token SEPARATOR
%token SET
%token SHOW
%token SMALLINT
%token SOME
%token SONAME
%token SPATIAL
%token SPECIFIC
%token SQL
%token SQLEXCEPTION
%token SQLSTATE
%token SQLWARNING
%token SQL_BIG_RESULT
%token SQL_CALC_FOUND_ROWS
%token SQL_SMALL_RESULT
%token SSL
%token STARTING
%token STRAIGHT_JOIN
%token SESSION
%token STATE
%token STRUCTURE

%token TABLE
%token TEMPORARY
%token TEXT
%token TERMINATED
%token THEN
%token TIME
%token TIMESTAMP
%token TINYBLOB
%token TINYINT
%token TINYTEXT
%token TO
%token TRAILING
%token TRIGGER

%token UNDO
%token UNION
%token UNIQUE
%token UNLOCK
%token UNSIGNED
%token UPDATE
%token USAGE
%token USE
%token USER
%token USING
%token UTC_DATE
%token UTC_TIME
%token UTC_TIMESTAMP

%token VALUE
%token VALUES
%token VARBINARY
%token VARCHAR
%token VARYING

%token WHEN
%token WHENEVER
%token WHERE
%token WHILE
%token WITHOUT
%token WITH
%token WRITE

%token XOR

%token YEAR
%token YEAR_MONTH

%token ZEROFILL

%token FSUBSTRING
%token FTRIM
%token FDATE_ADD FDATE_SUB
%token FCOUNT

%type <oprtNode_p> create_table_stmt insert_stmt
%type <defOpts_p> create_col_list create_definition
%type <colList_p> column_list opt_col_names
%type <uintval8> opt_binary opt_uz insert_opts
%type <dataType_t> data_type
%type <uintval64> opt_length
%type <intval> column_atts
/* %type <tablList_p> table_references table_reference table_factor */
%type <exprVar_p> expr
%type <exprVarCon_p> insert_vals insert_vals_list
/* %type <strval> opt_as_alias */

/* %type <intval> opt_for_join */
/* emmmm, 未使用的规则的类型声明... */
%type <intval> opt_ondupupdate insert_asgn_list

%start stmt_list

%%

stmt_list: stmt ';'
    | stmt_list stmt ';'
    ;

/** create table **/
stmt: create_table_stmt { mod->root = $1; }
    ;

create_table_stmt: CREATE TABLE NAME '(' create_col_list ')'
            {
                struct _OprtNode *root = new_oprt_node(TS_CREATE);
                struct _TablList *table = new_tabl_list($3, NULL);
                struct _DefOpts *opts = $5;
                root->table_ = table;
                root->universalList_.defOpts_ = opts;
                root->options_ = NULL;
                $$ = root;
                free($3);
            }
    ;

create_table_stmt: CREATE TABLE NAME '.' NAME '(' create_col_list ')'
            {
                struct _OprtNode *root = new_oprt_node(TS_CREATE);
                struct _TablList *table = new_tabl_list($3, $5);
                struct _DefOpts *opts = $7;
                root->table_ = table;
                root->universalList_.defOpts_ = opts;
                root->options_ = NULL;
                $$ = root;
                free($3);
                free($5);
            }
    ;

/* 在这里建一个链表.. */
create_col_list: create_definition  { $$ = $1; }
    | create_col_list ',' create_definition
    {
        $3->next = $1;
        $$ = $3;
    }
    ;

create_definition: NAME data_type column_atts
                {
                    struct _DefOpts *head = new_DefOpts_node();
                    head->attri_ = $3;
                    head->dataType_ = $2;
                    strncpy(head->nameRef_, $1, sizeof(head->nameRef_));
                    $$ = head;
                }
    ;

column_atts: /* nil */ { $$ = 0; }
    | column_atts NOT NULLX             { $$ = $1 | __Sql_NOTNULLX; }
    | column_atts AUTO_INCREMENT        { $$ = $1 | __Sql_AUTOINC; }
    | column_atts UNIQUE KEY            { $$ = $1 | __Sql_UNIKEY; }
    | column_atts PRIMARY KEY           { $$ = $1 | __Sql_PRIKEY; }
    | column_atts KEY                   { $$ = $1 | __Sql_KEY; }
    ;

opt_length: /* nil */   { $$ = 0; }
    | '(' INTNUM ')'    { $$ = $2; }
    | '(' INTNUM ',' INTNUM ')' { $$ = $2 + 1000*$4; }
    ;

opt_binary: /* nil */ { $$ = 0; }
    | BINARY    { $$ = 0x04; }
    ;

opt_uz: /* nil */       { $$ = 0; }
    | opt_uz UNSIGNED   { $$ = $1 | 0x01; }
    | opt_uz ZEROFILL   { $$ = $1 | 0x02; }
    ;

data_type: BIT opt_length            { struct _DataType data = newDataTypeNode(); data.type_ = DT_BIT; data.size_ = $2; $$ = data; }
    | TINYINT opt_length opt_uz      { struct _DataType data = newDataTypeNode(); data.type_ = DT_TINYINT; data.size_ = $2; $$ = data; }
    | SMALLINT opt_length opt_uz     { struct _DataType data = newDataTypeNode(); data.type_ = DT_SMALLINT; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | MEDIUMINT opt_length opt_uz    { struct _DataType data = newDataTypeNode(); data.type_ = DT_MEDINT; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | INT opt_length opt_uz          { struct _DataType data = newDataTypeNode(); data.type_ = DT_INT; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | INTEGER opt_length opt_uz      { struct _DataType data = newDataTypeNode(); data.type_ = DT_INTEGER; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | BIGINT opt_length opt_uz       { struct _DataType data = newDataTypeNode(); data.type_ = DT_BIGINT; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | REAL opt_length opt_uz         { struct _DataType data = newDataTypeNode(); data.type_ = DT_REAL; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | DOUBLE opt_length opt_uz       { struct _DataType data = newDataTypeNode(); data.type_ = DT_DOUBLE; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | FLOAT opt_length opt_uz        { struct _DataType data = newDataTypeNode(); data.type_ = DT_FLOAT; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | DECIMAL opt_length opt_uz      { struct _DataType data = newDataTypeNode(); data.type_ = DT_DECIMAL; data.size_ = $2; data.uz_ = $3; $$ = data; }
    | DATE                           { struct _DataType data = newDataTypeNode(); data.type_ = DT_DATE; $$ = data; }
    | TIME                           { struct _DataType data = newDataTypeNode(); data.type_ = DT_TIME; $$ = data; }
    | TIMESTAMP                      { struct _DataType data = newDataTypeNode(); data.type_ = DT_TIMESTAMP; $$ = data; }
    | DATETIME                       { struct _DataType data = newDataTypeNode(); data.type_ = DT_DATETIME; $$ = data; }
    | YEAR                           { struct _DataType data = newDataTypeNode(); data.type_ = DT_YEAR; $$ = data; }
    | CHAR opt_length                { struct _DataType data = newDataTypeNode(); data.type_ = DT_CHAR; data.size_ = $2; $$ = data; }
    | VARCHAR '(' INTNUM ')'         { struct _DataType data = newDataTypeNode(); data.type_ = DT_VARCHAR; data.size_ = $3; $$ = data; }
    | BINARY opt_length              { struct _DataType data = newDataTypeNode(); data.type_ = DT_BINARY; data.size_ = $2; $$ = data; }
    | VARBINARY '(' INTNUM ')'       { struct _DataType data = newDataTypeNode(); data.type_ = DT_VARBIN; data.size_ = $3; $$ = data; }
    | TINYBLOB                       { struct _DataType data = newDataTypeNode(); data.type_ = DT_TINYBLOB; $$ = data; }
    | BLOB                           { struct _DataType data = newDataTypeNode(); data.type_ = DT_BLOB; $$ = data; }
    | MEDIUMBLOB                     { struct _DataType data = newDataTypeNode(); data.type_ = DT_MEDBLOB; $$ = data; }
    | LONGBLOB                       { struct _DataType data = newDataTypeNode(); data.type_ = DT_LONGBLOB; $$ = data; }
    | TINYTEXT opt_binary            { struct _DataType data = newDataTypeNode(); data.type_ = DT_TINYTEXT; data.isBin_ = $2; $$ = data; }
    | TEXT opt_binary                { struct _DataType data = newDataTypeNode(); data.type_ = DT_TEXT; data.isBin_ = $2; $$ = data; }
    | MEDIUMTEXT opt_binary          { struct _DataType data = newDataTypeNode(); data.type_ = DT_MEDTEXT; data.isBin_ = $2; $$ = data; }
    | LONGTEXT opt_binary            { struct _DataType data = newDataTypeNode(); data.type_ = DT_LONGTEXT; data.isBin_ = $2; $$ = data; }
    ;

/* select statement */

/* 先注释掉大部分规则，等后面加入 */
/* stmt: select_stmt { mod->root = $1; } */
    /* ; */
/*  */
/* select_stmt: SELECT select_opts select_expr_list FROM table_references opt_where opt_groupby opt_having opt_orderby opt_limit */
     /* opt_into_list { */
        /* $$ = new_sexp_node(ST_LIST, $3); */
        /* $$ = new_sexp_node(ST_LIST, $5); */
     /* } */
    /* ; */

/* opt_where: [> nil <] { $$ = NULL; }
 *     | WHERE expr { emit("WHERE"); }; */

/* opt_groupby: [> nil <]  */
    /* | GROUP BY groupby_list opt_with_rollup { emit("GROUPBYLIST %d %d", $3, $4); } */
    /* ; */
/*  */
/* groupby_list: expr opt_asc_desc */
            /* { emit("GROUPBY %d",  $2); $$ = 1; } */
   /* | groupby_list ',' expr opt_asc_desc */
                             /* { emit("GROUPBY %d",  $4); $$ = $1 + 1; } */
    /* ; */
/*  */
/* opt_asc_desc: [> nil <] { $$ = 0; } */
    /* | ASC           { $$ = 0; } */
    /* | DESC          { $$ = 1; } */
    /* ; */
/*  */
/* opt_with_rollup: [> nil <]  { $$ = 0; } */
    /* | WITH ROLLUP   { $$ = 1; } */
    /* ; */
/*  */
/* opt_having: [> nil <] */
    /* | HAVING expr   { emit("HAVING"); } */
    /* ; */
/*  */
/* opt_orderby: [> nil <] | ORDER BY groupby_list { emit("ORDERBY %d", $3); } */
    /* ; */
/*  */
/* opt_limit: [> nil <] */
    /* | LIMIT expr    { emit("LIMIT 1"); } */
    /* | LIMIT expr ',' expr { emit("LIMIT 2"); } */
    /* ; */
/*  */
/* opt_into_list: [> nil <]  */
    /* | INTO column_list  { emit("INTO %d", $2); } */
    /* ; */

column_list: NAME
            {
                columns_list_t *root = new_NameList_node();
                add_NameList_node(root, $1);
                free($1);
                $$ = root;
            }
            | column_list ',' NAME
            {
                add_NameList_node($1, $3);
                free($3);
                $$ = $1;
            }
    ;

/* select_opts:                          { $$ = 0; } */
    /* | select_opts ALL                 { if($$ & 01) yyerror("duplicate ALL option"); $$ = $1 | 01; } */
    /* | select_opts DISTINCT            { if($$ & 02) yyerror("duplicate DISTINCT option"); $$ = $1 | 02; } */
    /* | select_opts DISTINCTROW         { if($$ & 04) yyerror("duplicate DISTINCTROW option"); $$ = $1 | 04; } */
    /* | select_opts HIGH_PRIORITY       { if($$ & 010) yyerror("duplicate HIGH_PRIORITY option"); $$ = $1 | 010; } */
    /* | select_opts STRAIGHT_JOIN       { if($$ & 020) yyerror("duplicate STRAIGHT_JOIN option"); $$ = $1 | 020; } */
    /* | select_opts SQL_SMALL_RESULT    { if($$ & 040) yyerror("duplicate SQL_SMALL_RESULT option"); $$ = $1 | 040; } */
    /* | select_opts SQL_BIG_RESULT      { if($$ & 0100) yyerror("duplicate SQL_BIG_RESULT option"); $$ = $1 | 0100; } */
    /* | select_opts SQL_CALC_FOUND_ROWS { if($$ & 0200) yyerror("duplicate SQL_CALC_FOUND_ROWS option"); $$ = $1 | 0200; } */
    /* ; */
/*  */
/* select_expr_list: select_expr           { $$ = 1; } */
    /* | select_expr_list ',' select_expr  { $$ = $1 + 1; } */
    /* | '*'                               { emit("SELECTALL"); $$ = 1; } */
    /* ; */
/*  */
/* select_expr: expr opt_as_alias ; */

/* table_references: table_reference           { $$ = $1; }
 *     | table_references ',' table_reference  { $1->next = $3; $$ = $1; }
 *     ;
 *
 * table_reference: table_factor               { $$ = $1; }
 *     ;
 *
 * table_factor: NAME opt_as_alias index_hint  { emit("TABLE %s", $1); free($1); }
 *     | NAME '.' NAME opt_as_alias index_hint { emit("TABLE %s.%s", $1, $3); free($1); free($3); }
 *     | table_subquery opt_as NAME            { emit("SUBQUERYAS %s", $3); free($3); }
 *     | '(' table_references ')'              { emit("TABLEREFERENCES %d", $2); }
 *     ;
 *
 * [> opt_as: AS <]
 *     [> | [> nil <] <]
 *     [> ; <]
 *
 * opt_as_alias: AS NAME   { $$ = $1; free($2); }
 *     | NAME              { $$ = $1; free($1); }
 *     | [> nil <]
 *     ; */

/* join_table: table_reference opt_inner_cross JOIN table_factor opt_join_condition */
                  /* { emit("JOIN %d", 0100+$2); } */
    /* | table_reference STRAIGHT_JOIN table_factor */
                  /* { emit("JOIN %d", 0200); } */
    /* | table_reference STRAIGHT_JOIN table_factor ON expr */
                  /* { emit("JOIN %d", 0200); } */
    /* | table_reference left_or_right opt_outer JOIN table_factor join_condition */
                  /* { emit("JOIN %d", 0300+$2+$3); } */
    /* | table_reference NATURAL opt_left_or_right_outer JOIN table_factor */
                  /* { emit("JOIN %d", 0400+$3); } */
    /* ; */
/*  */
/* opt_inner_cross: [> nil <] { $$ = 0; } */
    /* | INNER { $$ = 1; } */
    /* | CROSS { $$ = 2; } */
    /* ; */
/*  */
/* opt_outer: [> nil <]  { $$ = 0; } */
    /* | OUTER {$$ = 4; } */
    /* ; */
/*  */
/* left_or_right: LEFT { $$ = 1; } */
    /* | RIGHT         { $$ = 2; } */
    /* ; */
/*  */
/* opt_left_or_right_outer: LEFT opt_outer { $$ = 1 + $2; } */
    /* | RIGHT opt_outer  { $$ = 2 + $2; } */
    /* | [> nil <] { $$ = 0; } */
    /* ; */
/*  */
/* opt_join_condition: join_condition */
    /* | [> nil <] */
    /* ; */
/*  */
/* join_condition: ON expr { emit("ONEXPR"); } */
    /* | USING '(' column_list ')' { emit("USING %d", $3); } */
    /* ; */

/* index_hint: USE KEY opt_for_join '(' index_list ')'
 *                   { emit("INDEXHINT %d %d", $5, 010+$3); }
 *     | IGNORE KEY opt_for_join '(' index_list ')'
 *                   { emit("INDEXHINT %d %d", $5, 020+$3); }
 *     | FORCE KEY opt_for_join '(' index_list ')'
 *                   { emit("INDEXHINT %d %d", $5, 030+$3); }
 *     | [> nil <]
 *     ;
 *
 * opt_for_join: FOR JOIN { $$ = 1; }
 *     | [> nil <]        { $$ = 0; }
 *     ;
 *
 * index_list: NAME  { emit("INDEX %s", $1); free($1); $$ = 1; }
 *     | index_list ',' NAME { emit("INDEX %s", $3); free($3); $$ = $1 + 1; }
 *     ; */

/* table_subquery: '(' select_stmt ')' { emit("SUBQUERY"); } */
    /* ; */
/*  */
/*  */
    /* delete statement */

/* stmt: delete_stmt { mod->root = $1; }
 *     ;
 *
 * delete_stmt: DELETE delete_opts FROM NAME opt_where opt_limit
 *             {
 *                 struct _OprtNode *root = new_oprt_node(TS_DELETE);
 *                 struct _TablList *table = new_tabl_list($4, NULL);
 *                 struct _SqlOpts *opts = new_SqlOpts_node();
 *                 opts->options_->delOpts_ = $2;
 *
 *                 root->table_ = table;
 *                 free($4);
 *                 $$ = root;
 *             }
 *     ;
 *
 * delete_opts: delete_opts LOW_PRIORITY { $$ = $1 | __SqlDelOpt_LOWPRI; }
 *     | delete_opts QUICK { $$ = $1 | __SqlDelOpt_QUICK; }
 *     | delete_opts IGNORE { $$ = $1 | __SqlDelOpt_IGNORE; }
 *     | [> nil <] { $$ = 0; }
 *     ;
 *
 * delete_stmt: DELETE delete_opts delete_list
 *     FROM table_references opt_where
 *     {
 *         struct _OprtNode *root = new_oprt_node(TS_DELETE);
 *         struct _TablList *table = $5;
 *         struct _SqlOpts *opts = new_SqlOpts_node();
 *         emit("DELETEMULTI %d %d %d", $2, $3, $5);
 *     }
 *
 * delete_list: NAME opt_dot_star { emit("TABLE %s", $1); free($1); $$ = 1; }
 *     | delete_list ',' NAME opt_dot_star { emit("TABLE %s", $3); free($3); $$ = $1 + 1; }
 *     ;
 *
 * opt_dot_star: [> nil <] | '.' '*'
 *     ; */

/* delete_stmt: DELETE delete_opts FROM delete_list USING table_references opt_where
 *             { emit("DELETEMULTI %d %d %d", $2, $4, $6); }
 *     ; */

    /* insert statement */

stmt: insert_stmt { mod->root = $1; }
    ;

insert_stmt: INSERT insert_opts INTO NAME opt_col_names VALUES insert_vals_list opt_ondupupdate
    {
        struct _OprtNode *root = new_oprt_node(TS_INSERT);
        struct _TablList *table = new_tabl_list($4, NULL);
        struct _SqlOpts *opts = new_SqlOpts_node();
        opts->optColName_ = $5;
        root->table_ = table;
        root->options_ = opts;
        root->universalList_.exprVarCon_ = $7;
        free($4);
        $$ = root;
    }
    ;

/* insert_asgn_list 是个啥?,..先放着不写好了.. */
opt_ondupupdate: /* nil */      {  $$ = 0; }
    | ONDUPLICATE KEY UPDATE insert_asgn_list { $$ = 1; }
    ;

insert_asgn_list: { $$ = 0; }

insert_opts: /* nil */          { $$ = 0; }
    | insert_opts LOW_PRIORITY  { $$ = $1 | __SqlInsOpt_LOWPRI; }
    | insert_opts DELAYED       { $$ = $1 | __SqlInsOpt_DELAYED; }
    | insert_opts HIGH_PRIORITY { $$ = $1 | __SqlInsOpt_HIGPRI; }
    | insert_opts IGNORE        { $$ = $1 | __SqlInsOpt_IGNORE; }
    ;

opt_col_names: /* nil */  { $$ = NULL; }
    | '(' column_list ')' { $$ = $2; }
    ;

insert_vals_list: '(' insert_vals ')' { $$ = $2; }
    ;

insert_vals: expr               { struct _ExprVarCon *root = new_ExprVarCon_node(); add_ExprVar_node(root, $1); $$ = root; }
    | insert_vals ',' expr      { add_ExprVar_node($1, $3); $$ = $1; }
    ;

/* insert_stmt: INSERT insert_opts opt_into NAME SET insert_asgn_list opt_ondupupdate
 *                     { emit("INSERTASGN %d %d %s", $2, $6, $4); free($4); }
 *     ;
 *
 * insert_stmt: INSERT insert_opts opt_into NAME opt_col_names select_stmt opt_ondupupdate
 *                     { emit("INSERTSELECT %d %s", $2, $4); free($4); }
 *     ; */

/* insert_asgn_list: NAME COMPARISON expr { if ($2 != 4) yyerror("bad insert assignment to %s", $1);
 *                     emit("ASSIGN %s", $1); free($1); $$ = 1; }
 *     | NAME COMPARISON DEFAULT { if ($2 != 4) yyerror("bad insert assignment to %s", $1);
 *                     emit("DEFAULT"); emit("ASSIGN %s", $1); free($1); $$ = 1; }
 *     | insert_asgn_list ',' NAME COMPARISON expr { if ($4 != 4) yyerror("bad insert assignment to %s", $1);
 *                     emit("ASSIGN %s", $3); free($3); $$ = $1 + 1; }
 *     | insert_asgn_list ',' NAME COMPARISON DEFAULT { if ($4 != 4) yyerror("bad insert assignment to %s", $1);
 *                     emit("DEFAULT"); emit("ASSIGN %s", $3); free($3); $$ = $1 + 1; }
 *     ; */


    /* [> replace <] */
/* stmt: replace_stmt { emit("STMT"); } */
    /* ; */
/*  */
/* replace_stmt: REPLACE insert_opts opt_into NAME opt_col_names VALUES insert_vals_list opt_ondupupdate */
                /* { emit("REPLACEVALS %d %d %s", $2, $7, $4); free($4); } */
    /* ; */
/*  */
/* replace_stmt: REPLACE insert_opts opt_into NAME SET insert_asgn_list opt_ondupupdate */
                /* { emit("REPLACEASGN %d %d %s", $2, $6, $4); free($4); } */
    /* ; */
/*  */
/* replace_stmt: REPLACE insert_opts opt_into NAME opt_col_names select_stmt opt_ondupupdate */
                /* { emit("REPLACESELECT %d %s", $2, $4); free($4); } */
    /* ; */
/*  */
/* [>* update *<] */
/* stmt: update_stmt { emit("STMT"); } */
    /* ; */
/*  */
/* update_stmt: UPDATE update_opts table_references SET update_asgn_list opt_where opt_orderby opt_limit */
                /* { emit("UPDATE %d %d %d", $2, $3, $5); } */
    /* ; */
/*  */
/* update_opts: [> nil <]          { $$ = 0; } */
    /* | insert_opts LOW_PRIORITY  { $$ = $1 | 01 ; } */
    /* | insert_opts IGNORE        { $$ = $1 | 010 ; } */
    /* ; */
/*  */
/* update_asgn_list: NAME COMPARISON expr { if ($2 != 4) yyerror("bad insert assignment to %s", $1); */
                /* emit("ASSIGN %s", $1); free($1); $$ = 1; } */
    /* | NAME '.' NAME COMPARISON expr { if ($4 != 4) yyerror("bad insert assignment to %s", $1); */
                /* emit("ASSIGN %s.%s", $1, $3); free($1); free($3); $$ = 1; } */
    /* | update_asgn_list ',' NAME COMPARISON expr { if ($4 != 4) yyerror("bad insert assignment to %s", $3); */
                /* emit("ASSIGN %s.%s", $3); free($3); $$ = $1 + 1; } */
    /* | update_asgn_list ',' NAME '.' NAME COMPARISON expr { if ($6 != 4) yyerror("bad insert assignment to %s.$s", $3, $5); */
                /* emit("ASSIGN %s.%s", $3, $5); free($3); free($5); $$ = 1; } */
    /* ; */
/*  */

/** create database **/

/* stmt: create_database_stmt { emit("STMT"); } */
    /* ; */
/*  */
/* create_database_stmt: CREATE DATABASE NAME    { emit("CREATEDATABASE %d %s", $3, $4); free($4); } */
    /* | CREATE SCHEMA NAME                      { emit("CREATEDATABASE %d %s", $3, $4); free($4); } */
    /* ; */

/* set user variables */

/* stmt: set_stmt { emit("STMT"); } */
    /* ; */
/*  */
/* set_stmt: SET set_list ; */
/*  */
/* set_list: set_expr | set_list ',' set_expr ; */
/*  */
/* set_expr: USERVAR COMPARISON expr { if ($2 != 4) yyerror("bad set to @%s", $1); emit("SET %s", $1); free($1); } */
    /* | USERVAR ASSIGN expr { emit("SET %s", $1); free($1); } */
    /* ; */

/**** expressions ****/
/* 终结符,填上合适的数据后直接返回.. */
expr: NAME
    {
        struct _ExprVar *tmp = new_Expr_node();
        strncpy(tmp->data_, $1, strlen($1));
        tmp->type_ = __Sql_ExprNAME;
        free($1);
        $$ = tmp;
    }
    | USERVAR
    {
        struct _ExprVar *tmp = new_Expr_node();
        strncpy(tmp->data_, $1, strlen($1));
        tmp->type_ = __Sql_ExprUSERVAR;
        free($1);
        $$ = tmp;
    }
    | STRING
    {
        struct _ExprVar *tmp = new_Expr_node();
        strncpy(tmp->data_, $1, strlen($1));
        tmp->type_ = __Sql_ExprSTRING;
        free($1);
        $$ = tmp;
    }
    | INTNUM
    {
        struct _ExprVar *tmp = new_Expr_node();
        char buf[16];
        bzero(buf, sizeof(buf));
        sprintf(buf, "%d", $1);
        strncpy(tmp->data_, buf, strlen(buf));
        tmp->type_ = __Sql_ExprINTNUM;
        $$ = tmp;
    }
    | BOOL
    {
        struct _ExprVar *tmp = new_Expr_node();
        char buf[2];
        bzero(buf, sizeof(buf));
        sprintf(buf, "%d", $1);
        strncpy(tmp->data_, buf, strlen(buf));
        tmp->type_ = __Sql_ExprBOOL;
        $$ = tmp;
    }
    ;

expr: expr '+' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprADD);
            $$ = tmp;
        }
    | expr '-' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprSUB);
            $$ = tmp;
        }
    | expr '*' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprMUL);
            $$ = tmp;
        }
    | expr '/' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprDIV);
            $$ = tmp;
        }
    | expr '%' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprMOD);
            $$ = tmp;
        }
    | expr MOD expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprMOD);
            $$ = tmp;
        }
    | '-' expr %prec UMINUS
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $2, NULL, __Sql_ExprNEG);
            $$ = tmp;
        }
    | expr ANDOP expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprANDOP);
            $$ = tmp;
        }
    | expr OR expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprOR);
            $$ = tmp;
        }
    | expr XOR expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprXOR);
            $$ = tmp;
        }
    | expr COMPARISON expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, $2);
            $$ = tmp;
        }
    | expr '|' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprBITOR);
            $$ = tmp;
        }
    | expr '&' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprBITAND);
            $$ = tmp;
        }
    | expr '^' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $1, $3, __Sql_ExprBITXOR);
            $$ = tmp;
        }
    | NOT expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $2, NULL, __Sql_ExprNOT);
            $$ = tmp;
        }
    | '!' expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            setExprVar(tmp, $2, NULL, __Sql_ExprNOT);
            $$ = tmp;
        }
    | USERVAR ASSIGN expr
        {
            struct _ExprVar *tmp = new_Expr_node();
            tmp->type_ = __Sql_ExprUSERVAR;
            tmp->ltree_ = $3;
            tmp->rtree_ = NULL;
            strncpy(tmp->data_, $1, strlen($1));
            free($1);
            $$ = tmp;
        }
    ;

/* expr: expr IS NULLX     { emit("ISNULL"); }
 *     | expr IS NOT NULLX { emit("ISNULL"); emit("NOT"); }
 *     | expr IS BOOL      { emit("ISBOOL %d", $3); }
 *     | expr IS NOT BOOL  { emit("ISBOOL %d", $4); emit("NOT"); }
 *     ;
 *
 * expr: expr BETWEEN expr AND expr %prec BETWEEN { emit("BETWEEN"); }
 *     ;
 *
 *
 * val_list: expr { $$ = 1; }
 *     | expr ',' val_list { $$ = 1 + $3; }
 *     ;
 *
 * opt_val_list: [> nil <] { $$ = 0; }
 *     | val_list
 *     ;
 *
 * expr: expr IN '(' val_list ')'          { emit("ISIN %d", $4); }
 *     | expr NOT IN '(' val_list ')'      { emit("ISIN %d", $5); emit("NOT"); }
 *     | expr IN '(' select_stmt ')'       { emit("INSELECT"); }
 *     | expr NOT IN '(' select_stmt ')'   { emit("INSELECT"); emit("NOT"); }
 *     | EXISTS '(' select_stmt ')'        { emit("EXISTS"); if($1) emit("NOT"); }
 *     ;
 *
 * expr: NAME '(' opt_val_list ')' { emit("CALL %d %s", $3, $1); free($1); }
 *     ; */


/* functions with special syntax */

/* expr: FCOUNT '(' '*' ')'    { emit("COUNTALL"); } */
    /* | FCOUNT '(' expr ')'   { emit(" CALL 1 COUNT"); } */
/*  */
/* expr: FSUBSTRING '(' val_list ')'                   { emit("CALL %d SUBSTR", $3); } */
    /* | FSUBSTRING '(' expr FROM expr ')'             { emit("CALL 2 SUBSTR"); } */
    /* | FSUBSTRING '(' expr FROM expr FOR expr ')'    { emit("CALL 3 SUBSTR"); } */
    /* | FTRIM '(' val_list ')'                        { emit("CALL %d TRIM", $3); } */
    /* | FTRIM '(' trim_ltb expr FROM val_list ')'     { emit("CALL 3 TRIM"); } */
    /* ; */
/*  */
/* trim_ltb: LEADING   { emit("INT 1"); } */
    /* | TRAILING      { emit("INT 2"); } */
    /* | BOTH          { emit("INT 3"); } */
    /* ; */
/*  */
/* expr: FDATE_ADD '(' expr ',' interval_exp ')' { emit("CALL 3 DATE_ADD"); } */
    /* | FDATE_SUB '(' expr ',' interval_exp ')' { emit("CALL 3 DATE_SUB"); } */
    /* ; */
/*  */
/* interval_exp: INTERVAL expr DAY_HOUR    { emit("NUMBER 1"); } */
    /* | INTERVAL expr DAY_MICROSECOND     { emit("NUMBER 2"); } */
    /* | INTERVAL expr DAY_MINUTE          { emit("NUMBER 3"); } */
    /* | INTERVAL expr DAY_SECOND          { emit("NUMBER 4"); } */
    /* | INTERVAL expr YEAR_MONTH          { emit("NUMBER 5"); } */
    /* | INTERVAL expr YEAR                { emit("NUMBER 6"); } */
    /* | INTERVAL expr HOUR_MICROSECOND    { emit("NUMBER 7"); } */
    /* | INTERVAL expr HOUR_MINUTE         { emit("NUMBER 8"); } */
    /* | INTERVAL expr HOUR_SECOND         { emit("NUMBER 9"); } */
    /* ; */
/*  */
/* expr: CASE expr case_list END           { emit("CASEVAL %d 0", $3); } */
    /* | CASE expr case_list ELSE expr END { emit("CASEVAL %d 1", $3); } */
    /* | CASE case_list END                { emit("CASE %d 0", $2); } */
    /* | CASE case_list ELSE expr END      { emit("CASE %d 1", $2); } */
    /* ; */
/*  */
/* case_list: WHEN expr THEN expr      { $$ = 1; } */
    /* |   case_list WHEN expr THEN expr { $$ = $1+1; } */
    /* ; */
/*  */
/* expr: expr LIKE expr        { emit("LIKE"); } */
    /* | expr NOT LIKE expr    { emit("LIKE"); emit("NOT"); } */
    /* ; */
/*  */
/* expr: expr REGEXP expr      { emit("REGEXP"); } */
    /* | expr NOT REGEXP expr  { emit("REGEXP"); emit("NOT"); } */
    /* ; */
/*  */
/* expr: CURRENT_TIMESTAMP     { emit("NOW"); } */
    /* | CURRENT_DATE	        { emit("NOW"); } */
    /* | CURRENT_TIME	        { emit("NOW"); } */
    /* ; */
/*  */
/* expr: BINARY expr %prec UMINUS { emit("STRTOBIN"); } */
    /* ; */

%%

void emit(char *s, ...)
{
/*
    extern int yylineno;

    va_list ap;
    va_start(ap, s);

    printf("rpn: ");
    vfprintf(stdout, s, ap);
    printf("\n");
    */
    return ;
}

void yyerror(const char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    vfprintf(stderr, s, ap);
}
