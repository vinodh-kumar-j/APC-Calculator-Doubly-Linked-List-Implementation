/*-------------------------------------------------------------------------------------------------------------------------------------------------
 *   Author         : VINODH KUMAR J
 *   Date           : 09 AUG 2025
 *   Title          : APC Calculator – Doubly Linked List Implementation
 *   Description    : APC Calculator is a C-based command-line tool that performs arithmetic operations on arbitrarily large integers
 *                    using a doubly linked list to store each digit.
 *------------------------------------------------------------------------------------------------------------------------------------------------*/
#include "calc.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Usage: %s <operand1> <operator> <operand2>\n", argv[0]);
        return 1;
    }

    char *num1_str = argv[1];
    char operator;
    // Validate operator argument length (must be exactly 1 char)
    if (!argv[2][1])
        operator = argv[2][0];
    else
    {
        printf("Enter only one operator + - *  / %% \n");
        return 0;
    }
    char *num2_str = argv[3];

    // Convert string operands to doubly linked lists
    Node *num1 = create_list_from_string(num1_str);
    if (num1 == NULL)
        return 0;
    Node *num2 = create_list_from_string(num2_str);
    if (num2 == NULL)
        return 0;
    Node *result = NULL;
    // Select operation based on operator entered
    switch (operator)
    {
    case '+':
        result = add_lists(num1, num2);
        break;
    case '-':
        result = subtract_lists(num1, num2);
        break;
    case 'x':
        result = multiply_lists(num1, num2);
        break;
    case '/':
    {
        Node *rem = NULL;
        result = divide_lists(num1, num2, &rem);
        if (result)
        {
            printf("Quotient: ");
            print_list(result);
            printf("Remainder: ");
            print_list(rem);
            free_list(rem);
        }
        break;
    }
    default:
        printf("Error: Unsupported operator '%c'\n", operator);
    }

    if (result && operator != '/')
    {
        printf("Result: ");
        print_list(result);
    }

    // Free memory used by operand and result lists
    free_list(num1);
    free_list(num2);
    free_list(result);
}
