#include "monty.h"

/**
 * func_add - Adds the top two elements of the stack.
 * @stack: Stack on which the operation is performed.
 * @count: Line number in the Monty file.
 *
 * Return: Nothing.
 */

void func_add(stack_t **stack, unsigned int count)
{
	int sum;
	stack_t *node;
	
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", count);
		free_stack(*stack);
		exit(EXIT_FAILURE);
	}
	node = *stack;
	sum = (*stack)->n + (*stack)->next->n;
	(*stack)->next->n = sum;
	*stack = (*stack)->next;
	(*stack)->prev = NULL;
	free(node);
}

/**
 * func_nop - No operation, does nothing.
 * @stack: Doubly linked list representing the stack.
 * @count: Line number in the Monty file.
 *
 * Return: Nothing.
 */

void func_nop(stack_t **stack, unsigned int count)
{
	(void)stack;
	(void)count;
}
