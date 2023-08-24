#include "monty.h"

/**
 * main - Interpreter for Monty ByteCodes files.
 * @argc: Number of input arguments.
 * @argv: Array of input arguments.
 *
 * Return: Always 0.
 */

int main(int argc, char *argv[])
{
	FILE *fp;
	char *line_buf = NULL;
	unsigned int line_count = 0;
	size_t buffsize = 0;
	ssize_t line_size;
	stack_t *stack = NULL;
	
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	line_size = getline(&line_buf, &buffsize, fp);
	while (line_size >= 0)
	{
		line_count++;
		if (line_size > 1)
			tokenize(line_buf, line_count, &stack);
		
		free(line_buf);
		line_buf = NULL;
		line_size = getline(&line_buf, &buffsize, fp);
	}
	
	free(line_buf);
	free_stack(stack);
	fclose(fp);
	
	return (0);
}

