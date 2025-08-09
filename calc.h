#ifndef CALC_H
#define CALC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node {
    int digit;
    struct Node *prev, *next;
} Node;

/* ===== DLL Utility Functions ===== */
Node* create_list_from_string(const char *num_str);
void print_list(Node *head);
void free_list(Node *head);
Node* reverse_list(Node *head);
int compare_lists(Node *num1, Node *num2);
Node* remove_leading_zeros(Node *head);
Node* get_tail(Node *head); 
void insert_last(Node **head, Node **tail, int digit);

/* ===== Arithmetic Functions ===== */
Node* add_lists(Node *num1, Node *num2);
Node* subtract_lists(Node *num1, Node *num2);
Node* multiply_lists(Node *num1, Node *num2);
Node* divide_lists(Node *num1, Node *num2, Node **remainder);

#endif
