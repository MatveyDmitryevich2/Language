#ifndef RLE_H
#define RLE_H

#include <stdio.h>
#include <stddef.h>

#include "lexical_analysis.h"

struct Element
{
    Types type;

    union Argument
    {
        char variable;
        double number;
        Operation operation;
    } argument;
};

struct Node
{
    Element elem;

    Node* left;
    Node* right;
    Node* parent;
};

Node* Create_node(Node* parent, Node* left, Node* right, Element elem);
void Link_node(Node* node);
Node* GetG(Identifiers* identifiers);
Node* GetE(Identifiers* identifiers, size_t* i);
Node* GetT(Identifiers* identifiers, size_t* i);
Node* GetP(Identifiers* identifiers, size_t* i);
Node* GetN(Identifiers* identifiers, size_t* i);
Node* GetF(Identifiers* identifiers, size_t* i);

#endif //RLE_H