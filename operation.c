#include "calc.h"

// ADDITION of two numbers stored as doubly linked lists
Node *add_lists(Node *num1, Node *num2)
{
    Node *p1 = get_tail(num1); // Start from least significant digit of num1
    Node *p2 = get_tail(num2); // Start from least significant digit of num2
    Node *result_head = NULL, *result_tail = NULL;
    int carry = 0;

    // Loop while there are digits left or carry is non-zero
    while (p1 != NULL || p2 != NULL || carry != 0)
    {
        int d1 = (p1) ? p1->digit : 0; // Get digit from num1 or 0 if no more
        int d2 = (p2) ? p2->digit : 0;

        int sum = d1 + d2 + carry;
        carry = sum / 10;
        int digit = sum % 10;

        insert_last(&result_head, &result_tail, digit);

        if (p1)
            p1 = p1->prev;
        if (p2)
            p2 = p2->prev;
    }

    // Reverse because we built result from LSB to MSB
    result_head = reverse_list(result_head);
    return result_head;
}

// SUBTRACTION of two numbers stored as doubly linked lists
Node *subtract_lists(Node *num1, Node *num2)
{
    Node *opd1, *opd2;
    int sign = 0; // Will track if result should be negative

    num1 = remove_leading_zeros(num1);
    num2 = remove_leading_zeros(num2);

    // Compare magnitudes
    int cmp = compare_lists(num1, num2);
    if (cmp >= 0)
    {
        opd1 = num1;
        opd2 = num2;
    }
    else
    {
        opd1 = num2;
        opd2 = num1;
        sign = 1;
    }

    Node *p1 = get_tail(opd1);
    Node *p2 = get_tail(opd2);

    Node *result_head = NULL, *result_tail = NULL;
    int borrow = 0;

    while (p1 != NULL || p2 != NULL)
    {
        int d1 = (p1) ? p1->digit : 0;
        int d2 = (p2) ? p2->digit : 0;

        d1 = d1 - borrow;

        if (d1 < d2)
        {
            d1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        int diff = d1 - d2;
        insert_last(&result_head, &result_tail, diff);

        if (p1)
            p1 = p1->prev;
        if (p2)
            p2 = p2->prev;
    }

    result_head = reverse_list(result_head);         // Reverse to correct order
    result_head = remove_leading_zeros(result_head); // Remove unnecessary zeros

    if (sign && result_head)
        result_head->digit *= -1;

    return result_head;
}

// MULTIPLICATION of two numbers stored as doubly linked lists
Node *multiply_lists(Node *num1, Node *num2)
{
    Node *tail1 = get_tail(num1);
    Node *tail2 = get_tail(num2);

    Node *result = NULL; // Will store running total
    int shift = 0;       // Number of zeros to append for place value

    for (Node *p2 = tail2; p2 != NULL; p2 = p2->prev)
    {
        int carry = 0;
        Node *result1 = NULL, *result1_tail = NULL;

        // Add shift zeros for place value
        for (int i = 0; i < shift; i++)
        {
            insert_last(&result1, &result1_tail, 0);
        }

        // Multiply each digit of num1 by current digit of num2
        for (Node *p1 = tail1; p1 != NULL; p1 = p1->prev)
        {
            int prod = p1->digit * p2->digit + carry;
            carry = prod / 10;
            int digit = prod % 10;
            insert_last(&result1, &result1_tail, digit);
        }

        if (carry)
            insert_last(&result1, &result1_tail, carry);

        result1 = reverse_list(result1);

        Node *temp_result = add_lists(result, result1);

        free_list(result);
        free_list(result1);

        result = temp_result;
        shift++;
    }

    return result;
}

Node *divide_lists(Node *num1, Node *num2, Node **remainder)
{
    // Check for division by zero
    if (!num2 || (remove_leading_zeros(num2)->digit == 0 && !num2->next))
    {
        printf("Error: Division by zero.\n");
        return NULL;
    }

    num1 = remove_leading_zeros(num1);
    num2 = remove_leading_zeros(num2);

    // Case: num1 < num2 => quotient = 0, remainder = num1
    if (compare_lists(num1, num2) < 0)
    {
        Node *rem_copy = NULL, *rem_tail = NULL;
        for (Node *temp = num1; temp != NULL; temp = temp->next)
        {
            insert_last(&rem_copy, &rem_tail, temp->digit);
        }
        *remainder = remove_leading_zeros(rem_copy);
        return create_list_from_string("0");
    }

    Node *quotient_head = NULL, *quotient_tail = NULL;
    Node *current_head = NULL, *current_tail = NULL;

    for (Node *ptr = num1; ptr != NULL; ptr = ptr->next)
    {
        // Append next digit of dividend
        insert_last(&current_head, &current_tail, ptr->digit);
        current_head = remove_leading_zeros(current_head);
        current_tail = get_tail(current_head); // update tail

        int count = 0;
        while (compare_lists(current_head, num2) >= 0)
        {
            Node *temp = subtract_lists(current_head, num2);
            free_list(current_head);
            current_head = temp;
            current_tail = get_tail(current_head);
            count++;
        }

        insert_last(&quotient_head, &quotient_tail, count);
    }

    quotient_head = remove_leading_zeros(quotient_head);

    // Copy remainder safely
    if (current_head != NULL)
    {
        Node *rem_copy = NULL, *rem_tail = NULL;
        for (Node *temp = current_head; temp != NULL; temp = temp->next)
        {
            insert_last(&rem_copy, &rem_tail, temp->digit);
        }
        *remainder = remove_leading_zeros(rem_copy);
    }
    else
    {
        *remainder = create_list_from_string("0");
    }

    free_list(current_head);

    return quotient_head;
}
