#ifndef MONTY_H
#define MONTY_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int intvalue;

/**
 * struct stack_s - Doubly linked list node representing a stack or queue
 * @n: Integer value held by the node
 * @prev: Pointer to the previous node in the stack or queue
 * @next: Pointer to the next node in the stack or queue
 *
 * Description: This structure defines a doubly linked list node that is used
 * for implementing stack and queue data structures, supporting LIFO and FIFO operations.
 */

typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

typedef struct bus_s
{
	char *arg;
	FILE *file;
	char *content;
	int lifi;
}  bus_t;
extern bus_t bus;

/**
 * struct instruction_s - Represents an opcode and its corresponding function
 * @opcode: The opcode
 * @f: The function to handle the opcode
 *
 * Description: This structure defines an opcode and its associated function
 * for use in various data structures such as stacks, queues, FIFO, and LIFO.
 */

typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_count);
} instruction_t;

void tokenize(char *line_buf, unsigned int line_count, stack_t **stack);
void exe_opcode(char *op, char *value, unsigned int count, stack_t **stack);
int handle_value(char *value, unsigned int count);
void func_push(stack_t **stack, unsigned int line_count);
void func_pall(stack_t **stack, unsigned int line_count);
void func_pint(stack_t **stack, unsigned int line_count);
void func_pop(stack_t **stack, unsigned int line_count);
void func_swap(stack_t **stack, unsigned int line_count);
void func_add(stack_t **stack, unsigned int line_count);
void func_nop(stack_t **stack, unsigned int line_count);
void free_stack(stack_t *stack);

#endif
