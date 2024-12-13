#include "dump.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include <sys/time.h>
#include <unistd.h>

#include "lexical_analysis.h"
#include "utils.h"
#include "RLE.h"

static void Generate_nodes(Node* node, FILE* file);
static void Write_before_body();
static void Write_body();
static void Write_html();

//--------------------------------------------------global--------------------------------------------------------------

void Write_html_mode(Dump_html mode)
{
    if (mode == Dump_html_BEGIN) 
    { 
        Write_before_body(); 
        Write_body(); 
    }
    
    if (mode == Dump_html_END)   
    { 
        Write_body(); 
        Write_html(); 
    }
}

void Dump_grapviz(Node* root) 
{
    assert(root != NULL);

    struct timeval tv;
    gettimeofday(&tv, NULL);

    long seconds = tv.tv_sec;
    long microseconds = tv.tv_usec;
    
    char filename[100] = {0};
    snprintf(filename, sizeof(filename), "file_%ld_%06ld.dot", seconds, microseconds);

    FILE* file_html = fopen("dump.html", "a+");

    FILE* file_dump = fopen(filename, "a+");

    fprintf(file_dump, INFO_GRAPH);

    Generate_nodes(root, file_dump);

    fprintf(file_dump, "}\n");

    fclose(file_dump);

    char command[256];
    snprintf(command, sizeof(command), "dot -Tpng %s -o %.22s.png", filename, filename);

    // fprintf(stderr, "pid: %d\n", getpid());

    system(command);
    // if (errrr < 0) {
    //     perror("bebera");
    //     fprintf(stderr, "what a heck\n");
    // }
    // fprintf(stderr, "pid: %d\n", getpid());

    snprintf(filename, sizeof(filename), "file_%ld_%06ld.png", seconds, microseconds);
    fprintf(file_html, "<img src=\"%s\"/>\n", filename);
    fclose(file_html);
}

//--------------------------------------------------static--------------------------------------------------------------

static void Generate_nodes(Node* node, FILE* file)
{
    DPRINTF("\nАДРЕС НОДЫ ДЛЯ ПЕЧАТИ: %p\n", node);

    if (node == NULL) { return; }

    char node_id[100];
    snprintf(node_id, sizeof(node_id), "node_%lx", (long unsigned int)node);

    // fprintf(stderr, "node: %p\n", node);
    // fprintf(stderr, "node->left: %p\n", node->left);
    // fprintf(stderr, "node->right: %p\n", node->right);

    const char* node_color = "white";
    
    switch(node->elem.type)
    {
        case Types_VARIABLE:  { node_color = "blue";  } break;
        case Types_NUMBER:    { node_color = "green"; } break;
        case Types_OPERATION: { node_color = "red";   } break;
        default: { assert(0 && "No tipes"); }
    }

    fprintf(file, "    %s\n    [\n", node_id);
    fprintf(file, "        shape=plaintext,\n");
    fprintf(file, "        label=<\n");
    fprintf(file, "        <table border=\"0\" cellpadding=\"4\" cellborder=\"1\" width=\"300\" bgcolor=\"%s\">\n", node_color);
    fprintf(file, "        <tr><td align=\"center\" colspan=\"2\">Parent: %p</td></tr>\n", (void*)node->parent);

    if (node->elem.type == Types_OPERATION) {
        fprintf(file, "        <tr><td align=\"center\" colspan=\"2\">%d</td></tr>\n", Types_OPERATION);
        fprintf(file, "        <tr><td align=\"center\" colspan=\"2\">%s</td></tr>\n", Enum_op_to_str(node->elem.argument.operation));
    } else 

    if (node->elem.type == Types_NUMBER) {
        fprintf(file, "        <tr><td align=\"center\" colspan=\"2\">%d</td></tr>\n", Types_NUMBER);
        fprintf(file, "        <tr><td align=\"center\" colspan=\"2\">%.lf</td></tr>\n", node->elem.argument.number);
    } else 
    
    if (node->elem.type == Types_VARIABLE) {
        fprintf(file, "        <tr><td align=\"center\" colspan=\"2\">%d</td></tr>\n", Types_VARIABLE);
        fprintf(file, "        <tr><td align=\"center\" colspan=\"2\">%c</td></tr>\n", node->elem.argument.variable);
    } else {
        assert(0 && "unknown type");
    }

    fprintf(file, "        <tr>\n");
    fprintf(file, "        <td align=\"center\" width=\"150\">Left: %p</td>\n", (void*)node->left);
    fprintf(file, "        <td align=\"center\" width=\"150\">Right: %p</td>\n", (void*)node->right);
    fprintf(file, "        </tr>\n");

    fprintf(file, "        </table>\n");
    fprintf(file, "        >\n");
    fprintf(file, "    ];\n");

    if (node->left != NULL)
    {
        char left_id[100];
        snprintf(left_id, sizeof(left_id), "node_%lx", (long unsigned int)node->left);
        fprintf(file, "    %s -> %s [color=\"#000000\"];\n", node_id, left_id);

        Generate_nodes(node->left, file);
    }

    if (node->right != NULL)
    {
        char right_id[100];
        snprintf(right_id, sizeof(right_id), "node_%lx", (long unsigned int)node->right);
        fprintf(file, "    %s -> %s [color=\"#000000\"];\n", node_id, right_id);

        Generate_nodes(node->right, file);
    }
}

const char* Enum_op_to_str(Operation operation)
{
    #define CASE(enum, op) case enum: { return op; }

    switch (operation)
    {
        CASE(Operation_ADD,          ADD_               );
        CASE(Operation_SUB,          SUB_               );
        CASE(Operation_MUL,          MUL_               );
        CASE(Operation_DIV,          DIV_               ); 
        CASE(Operation_POWER,        POWER_             );
        CASE(Operation_SIN,          SIN_               ); 
        CASE(Operation_COS,          COS_               );
        CASE(Operation_TG,           TG_                );
        CASE(Operation_CTG,          CTG_               );
        CASE(Operation_SH,           SH_                );
        CASE(Operation_CH,           CH_                );
        CASE(Operation_TH,           TH_                );
        CASE(Operation_CTH,          CTH_               );
        CASE(Operation_ARCSIN,       ARCSIN_            );
        CASE(Operation_ARCCOS,       ARCCOS_            );
        CASE(Operation_ARCTG,        ARCTG_             );
        CASE(Operation_ARCCTG,       ARCCTG_            );
        CASE(Operation_LOG,          LOG_               );
        CASE(Operation_LN,           LN_                );
        CASE(Operation_EXP,          EXP_               );
        
        default: { return NULL; };
    }

    #undef CASE
}

static void Write_before_body()
{
    FILE* html_file = fopen("dump.html", "a+");

    fprintf(html_file, INFO_HTML);
    fclose(html_file);
}

static void Write_body()
{
    FILE* html_file = fopen("dump.html", "a+");

    fprintf(html_file, "<body>\n");

    fclose(html_file);
}

static void Write_html()
{
    FILE* html_file = fopen("dump.html", "a+");

    fprintf(html_file, "</html>\n");
    
    fclose(html_file);
}