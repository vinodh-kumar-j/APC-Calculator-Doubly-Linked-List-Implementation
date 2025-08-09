#include "calc.h"

// Converts a string of digits into a doubly linked list of Node elements
Node *create_list_from_string(const char *num_str)
{
    Node *head = NULL, *tail = NULL;
    for (int i = 0; num_str[i] != '\0'; i++) // Loop through each character in the string
    {
        char c = num_str[i];

        if (!isdigit(c))
        {
            // Validation failed
            printf("Error: Invalid character '%c' in input.\n", c);
            // Clean up any already created nodes
            free_list(head);
            return NULL;
        }

        // Create node
        Node *new_node = malloc(sizeof(Node));
        new_node->digit = c - '0';
        new_node->next = NULL;
        new_node->prev = NULL;

        if (head == NULL) // If list is empty, set first node
        {
            // First node
            head = new_node;
            tail = new_node;
        }
        else // Append to the end of the list
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }

    return head; // Return pointer to first node
}

// Prints the digits in the list
void print_list(Node *head)
{
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }
    else
    {
        while (head)
        {
            /* Printing the list */
            printf("%d", head->digit);

            /* Travering in forward direction */
            head = head->next;
        }
        printf("\n");
    }
}

// Frees the memory of the entire list
void free_list(Node *head)
{
    Node *temp;

    while (head != NULL)
    {
        temp = head;       // store current node
        head = head->next; // move to next node
        free(temp);        // free current node
    }
}

// Reverses the order of nodes in the list
Node *reverse_list(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    Node *current = head;
    Node *temp = NULL;

    // Swap next and prev for all nodes
    while (current != NULL)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;

        // Move to the "new" next node (old prev)
        current = current->prev;
    }

    // After loop, temp points to the old head's previous (new head)
    if (temp != NULL)
        head = temp->prev;

    return head;
}

// Compares two lists numerically
int compare_lists(Node *num1, Node *num2)
{
    // Step 1: find lengths
    int len1 = 0, len2 = 0;
    Node *t1 = num1, *t2 = num2;

    while (t1)
    {
        len1++;
        t1 = t1->next;
    }
    while (t2)
    {
        len2++;
        t2 = t2->next;
    }

    // Compare lengths
    if (len1 > len2)
        return 1;
    if (len1 < len2)
        return -1;

    // Step 2: lengths equal -> compare digit by digit
    t1 = num1;
    t2 = num2;

    while (t1 && t2)
    {
        if (t1->digit > t2->digit)
            return 1;
        if (t1->digit < t2->digit)
            return -1;

        t1 = t1->next;
        t2 = t2->next;
    }

    // Step 3: all digits same
    return 0;
}

// Removes leading zeros from a number
Node *remove_leading_zeros(Node *head)
{
    while (head && head->digit == 0 && head->next)
    {
        Node *temp = head;
        head = head->next;
        head->prev = NULL;
        free(temp);
    }
    return head;
}

// Finds and returns pointer to last node
Node *get_tail(Node *head)
{
    while (head && head->next)
        head = head->next;
    return head;
}

// Inserts a digit at the end of the list
void insert_last(Node **head, Node **tail, int digit)
{
    Node *new_node = malloc(sizeof(Node));
    new_node->digit = digit;
    new_node->next = NULL;
    new_node->prev = *tail;

    if (*tail)
        (*tail)->next = new_node;
    else
        *head = new_node;

    *tail = new_node;
}
