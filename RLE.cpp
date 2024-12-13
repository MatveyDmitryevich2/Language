#include "RLE.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <math.h>
#include <cctype>
#include <iostream>
#include <cstring>

#include "lexical_analysis.h"



Node* Create_node(Node* parent, Node* left, Node* right, Element elem)
{
    Node* node = (Node*)calloc(1, sizeof(Node));

    node->parent = parent;
    node->left = left;
    node->right = right;

    node->elem = elem;

    return node;
}

void Link_node(Node* node)
{
    if ((node->left != NULL) && (node->left->parent == NULL))   { node->left->parent = node; Link_node(node->left);   }
    if ((node->right != NULL) && (node->right->parent == NULL)) { node->right->parent = node; Link_node(node->right); }

    return;
}


Node* GetG(Identifiers* identifiers)
{
    size_t i = 0;
    Node* node = GetE(identifiers, &i);
    if (identifiers[i].type != Types_END_SYMBOL) { assert(0 && "Syntax Error"); }

    i++;

    return node;
}


Node* GetE(Identifiers* identifiers, size_t* i)
{
    Node* node = GetT(identifiers, i);

    if (node == NULL) { assert(0 && "Syntax error"); }

    while ((identifiers[*i].type == Types_OPERATION) && (identifiers[*i].argument.operation == Operation_ADD
                                                         || identifiers[*i].argument.operation == Operation_SUB))
    {
        Operation op = identifiers[*i].argument.operation;
        (*i)++;
        Node* node_2 = GetT(identifiers, i);

        if (node_2 == NULL) { assert(0 && "Syntax error"); }

        if (op == Operation_ADD)
        {
            node = Create_node(NULL, node, node_2, (Element){.type = Types_OPERATION, .argument = { .operation = op}});
            Link_node(node);
        }

        else if (op == Operation_SUB) 
        {
            node = Create_node(NULL, node, node_2, (Element){.type = Types_OPERATION, .argument = { .operation = op}});
            Link_node(node);
        }
    }

    return node;
}

Node* GetT(Identifiers* identifiers, size_t* i)
{
    Node* node = GetP(identifiers, i);

    if (node == NULL) { assert(0 && "Syntax error"); }

    while ((identifiers[*i].type == Types_OPERATION) && (identifiers[*i].argument.operation == Operation_MUL
                                                         || identifiers[*i].argument.operation == Operation_DIV
                                                         || identifiers[*i].argument.operation == Operation_POWER))
    {
        Operation op = identifiers[*i].argument.operation;
        (*i)++;
        Node* node_2 = GetP(identifiers, i);

        if (node_2 == NULL) { assert(0 && "Syntax error"); }

        if (op == Operation_MUL)
        {
            node = Create_node(NULL, node, node_2, (Element){.type = Types_OPERATION, .argument = { .operation = op}});
            Link_node(node);
        }
        else if (op == Operation_DIV)
        {
            node = Create_node(NULL, node, node_2, (Element){.type = Types_OPERATION, .argument = { .operation = op}});
            Link_node(node);
        }
        else if (op == Operation_POWER)
        {
            node = Create_node(NULL, node, node_2, (Element){.type = Types_OPERATION, .argument = { .operation = op}});
            Link_node(node);
        }
    }

    return node;
}

Node* GetP(Identifiers* identifiers, size_t* i)
{
    if (identifiers[*i].type == Types_LEFT_BRACKET)
    {
        (*i)++;
        Node* node = GetE(identifiers, i);

        if (identifiers[*i].type != Types_RIGHT_BRACKET) { assert(0 && "Syntax error"); }

        (*i)++;

        return node;
    }

    else if ((identifiers[*i].type == Types_NUMBER) || (identifiers[*i].type == Types_VARIABLE)) { return GetN(identifiers, i); }
    else { return GetF(identifiers, i); }
}

Node* GetN(Identifiers* identifiers, size_t* i)
{
    Node* node = NULL;

         if (identifiers[*i].type == Types_NUMBER)   { node = Create_node(NULL, NULL, NULL, (Element){.type = Types_NUMBER, .argument = { .number = identifiers[*i].argument.number}}); (*i)++; }
    else if (identifiers[*i].type == Types_VARIABLE) { node = Create_node(NULL, NULL, NULL, (Element){.type = Types_VARIABLE, .argument = { .variable = identifiers[*i].argument.variable}}); (*i)++; }

    return node;
}

Node* GetF(Identifiers* identifiers, size_t* i)
{
    Operation op = identifiers[*i].argument.operation;
    (*i)++;
    
    (*i)++;
    Node* node_1 = GetE(identifiers, i);
    if (node_1 == NULL) { assert(0 && "Syntax error"); }
    (*i)++;

    Node* node = Create_node(NULL, NULL, node_1, (Element){.type = Types_OPERATION, .argument = { .operation = op}});
    Link_node(node);

    return node;
}
