#include "monty.h"

/**
 * handle_value - Check if a string represents a valid integer value.
 * @value: A character or string containing numeric characters.
 * @count: Monty file line count.
 *
 * Return: An integer value.
 */
int handle_value(char *value, unsigned int count)
{
	int i = 0, n = 0, flag = 0;
	
	if (value != NULL)
	{
		if (value[0] == '-')
			i = 1;
		for (; i < (int)strlen(value); i++)
		{
			if (value[i] < '0' || value[i] > '9')
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			n = atoi(value);
		else
		{
			fprintf(stderr, "L%u: usage: push integer\n", count);
			
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "L%u: usage: push integer\n", count);
		exit(EXIT_FAILURE);
	}
	return n;
}

/**
 * free_stack - Free the entire stack.
 * @stack: A doubly linked list representing the stack.
 *
 * Return: Nothing.
 */

void free_stack(stack_t *stack)
{
	stack_t *temp;
	
	if (!stack)
		return;
	
	temp = stack;
	while (stack)
	{
		temp = stack->next;
		free(stack);
		stack = temp;
	}
}

/**
 * func_pint - Print the value at the top of the stack.
 * @stack: The stack.
 * @count: Monty file line number.
 *
 * Return: Nothing.
 */
void func_pint(stack_t **stack, unsigned int count)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pint, stack empty\n", count);
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("%d\n", (*stack)->n);
	}
}

/**
 * func_pop - Remove the top element from the stack.
 * @stack: The stack.
 * @count: Monty file line number.
 *
 * Return: Nothing.
 */
void func_pop(stack_t **stack, unsigned int count)
{
	stack_t *temp;
	
	if (*stack == NULL)
	{
		fprintf(stderr, "L%u: can't pop an empty stack\n", count);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	temp = *stack;
	*stack = (*stack)->next;
	if (*stack != NULL)
	{
		(*stack)->prev = NULL;
	}
	free(temp);
}

/**
 * func_swap - Swap the values of the top two elements of the stack.
 * @stack: The stack.
 * @count: Monty file line number.
 *
 * Return: Nothing.
 */
void func_swap(stack_t **stack, unsigned int count)
{
	int temp;
	
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%u: can't swap, stack too short\n", count);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->n;
	(*stack)->n = (*stack)->next->n;
	(*stack)->next->n = temp;
}
