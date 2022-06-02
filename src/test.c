/*
	Adds function logs for function tracing for C/C++ code.

	Expects code to be formatted with: astyle -A4 -t

	Copyright (c) 2022 David Shoon
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *strip_newline(char *s)
{
	char *p = strpbrk(s, "\r\n");
	if (p) *p = '\0';
	return s;
}

void print_function(const char *function_name)
{
	printf("\tfprintf(stderr, \"ENTER: %s\\n\");\n", function_name);
}

int main()
{
	char buf[10*1024];
	char lastline[10*1024];

	lastline[0] = '\0';

	printf("#include <stdio.h>\n");

	while (fgets(buf, sizeof(buf), stdin)) {
		strip_newline(buf);

		printf("%s\n", buf);

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
