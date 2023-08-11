/*
	Prints out function names

	Expects code to be formatted with: astyle -A4 -t

	Copyright (c) 2022 David Shoon
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

/*

static char *Class::Function(blah& blahfoo)
{
	

}


*/

static int print_local_or_global = 0;

char *strip_newline(char *s)
{
	char *p = strpbrk(s, "\r\n");
	if (p) *p = '\0';
	return s;
}

int is_special_function_chars(int c)
{
	switch (c) {
		case '_':
		case ':':
			return 1;

		default:
			return 0;

	}
}

char *get_function_name(const char *str)
{
	char buf[10*1024];

	strcpy(buf, str);

	char *p = strchr(buf, '(');

	if (p) {
		*p = '\0';

		while (p != buf) {
			p--;
			if (!isalnum(*p) && !is_special_function_chars(*p)) {
				p++;
				break;
			}
		}

		return strdup(p);
	}

	return NULL;
}

int is_static_function(const char *str)
{
	if (strstr(str, "static ")) {
		return 1;
	}

	return 0;
}

void print_function(const char *function_name)
{
	char *name = get_function_name(function_name);

	int local_function = is_static_function(function_name);

	if (name) {
		if (print_local_or_global) {
			if (local_function) {
				printf("local %s\n", name);
			}

			else {
				printf("global %s\n", name);
			}
		}

		else {
			printf("%s\n", name);
		}
	}

	free(name);
}

int main(int argc, char **argv)
{
	char buf[10*1024];
	char lastline[10*1024];

	if (argc == 2) {
		if (strcmp(argv[1], "-print_local_or_global") == 0) {
			print_local_or_global = 1;
		}
	}

	lastline[0] = '\0';

	while (fgets(buf, sizeof(buf), stdin)) {
		strip_newline(buf);

		if (strlen(lastline) != 0) {
			if (buf[0] == '{') {
				print_function(lastline);
			}
		}

		if (strlen(buf) != 0) {
			strcpy(lastline, buf);
		}
	}
}
