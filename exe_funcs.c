#include "monty.h"

/**
 * tokenize - Parse tokens from a line and execute corresponding opcode.
 * @line_buf: Line read from the Monty file.
 * @count: Line number in the Monty file.
 * @stack: Doubly linked list that stores pushed values.
 *
 * This function tokenizes the input line, extracts the operation and value,
 * and then calls exe_opcode to execute the opcode.
 */

void tokenize(char *line_buf, unsigned int count, stack_t **stack)
{
	const char *delim = " \n\t";
	char *token = strtok(line_buf, delim);
	char *op = NULL, *value = NULL;
	
	int i = 0;
	
	while (token != NULL && i < 2)
	{
		if (i == 0)
			op = strdup(token);
		else if (i == 1)
			value = strdup(token);
		i++;
		token = strtok(NULL, delim);
	}
	if (i > 0)
		exe_opcode(op, value, count, stack);
	
	free(op);
	free(value);
}

/**
 * exe_opcode - Execute the corresponding opcode.
 * @op: Opcode.
 * @value: Value associated with the opcode.
 * @count: Line number in the Monty file.
 * @stack: Doubly linked list that stores pushed values.
 *
 * This function matches the opcode to the corresponding function using
 * an instruction array, and executes the appropriate function.
 */

void exe_opcode(char *op, char *value, unsigned int count, stack_t **stack)
{
	int i = 0;
	int flag = 0;
	
	instruction_t instr[] = {
		{"push", func_push}, {"pall", func_pall}, {"pint", func_pint},
		{"pop", func_pop}, {"swap", func_swap}, {"add", func_add},
		{"nop", func_nop}, {NULL, NULL}
	};
	
	if (strcmp(op, "push") == 0)
	{
		if (!value)
		{
			fprintf(stderr, "L%u: usage: push integer\n", count);
			exit(EXIT_FAILURE);
		}
		else
		{
			int intvalue = handle_value(value, count);
			
			func_push(stack, intvalue);
		}
	}
	else
	{
		while (instr[i].opcode != NULL)
		{
			if (strcmp(op, instr[i].opcode) == 0)
			{
				instr[i].f(stack, count);
				flag = 1;
				break;
			}
			i++;
		}
		if (flag == 0)
		{
			fprintf(stderr, "L%u: unknown instruction %s\n", count, op);
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * func_push - Push a new node onto the stack.
 * @stack: Doubly linked list that stores pushed values.
 * @value: Value to be pushed onto the stack.
 *
 * This function creates a new node with the given value and adds it to the stack.
 */

void func_push(stack_t **stack, int value)
{
	stack_t *new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_node->n = value;
	new_node->prev = NULL;
	
	if (*stack != NULL)
	{
		new_node->next = *stack;
		(*stack)->prev = new_node;
	}
	else
	{
		new_node->next = NULL;
	}
	*stack = new_node;
}

/**
 * func_pall - Print values of all nodes in the stack.
 * @stack: Doubly linked list that stores pushed values.
 * @count: Line number in the Monty file.
 *
 * This function prints the values of all nodes in the stack.
 */

void func_pall(stack_t **stack, unsigned int count)
{
	stack_t *node = *stack;
	(void)count;

	while (node)
	{
		printf("%d\n", node->n);
		node = node->next;
	}
}
