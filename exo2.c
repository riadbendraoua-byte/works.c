#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define TOKEN_SIZE 256

static void append(char *token, size_t *length, int c)
{
	if (*length + 1 < TOKEN_SIZE)
		token[(*length)++] = (char)c;
}

static void emit(const char *kind, const char *token)
{
	printf("%-12s %s\n", kind, token);
}

static int keyword(const char *word)
{
	static const char *const words[] = {
		"auto", "break", "case", "char", "const", "continue", "default",
		"do", "double", "else", "enum", "extern", "float", "for", "goto",
		"if", "inline", "int", "long", "register", "restrict", "return",
		"short", "signed", "sizeof", "static", "struct", "switch", "typedef",
		"union", "unsigned", "void", "volatile", "while", "_Bool", "_Complex"
	};
	size_t i;

	for (i = 0; i < sizeof words / sizeof words[0]; ++i)
		if (strcmp(word, words[i]) == 0)
			return 1;
	return 0;
}

static int is_operator_char(int c)
{
	return strchr("+-*/%=<>!&|^~", c) != NULL;
}

int main(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		char token[TOKEN_SIZE];
		size_t length = 0;

		if (isspace((unsigned char)c))
			continue;

		if (isalpha((unsigned char)c) || c == '_') {
			do {
				append(token, &length, c);
				c = getchar();
			} while (c != EOF && (isalnum((unsigned char)c) || c == '_'));
			if (c != EOF)
				ungetc(c, stdin);
			token[length] = '\0';
			emit(keyword(token) ? "KEYWORD" : "IDENTIFIER", token);
			continue;
		}

		if (isdigit((unsigned char)c)) {
			do {
				append(token, &length, c);
				c = getchar();
			} while (c != EOF && (isalnum((unsigned char)c) || c == '.' ||
								   ((c == '+' || c == '-') && length > 0 &&
									(token[length - 1] == 'e' || token[length - 1] == 'E' ||
									 token[length - 1] == 'p' || token[length - 1] == 'P'))));
			if (c != EOF)
				ungetc(c, stdin);
			token[length] = '\0';
			emit("NUMBER", token);
			continue;
		}

		if (c == '"' || c == '\'') {
			int quote = c, escaped = 0;
			append(token, &length, c);
			while ((c = getchar()) != EOF) {
				append(token, &length, c);
				if (!escaped && c == quote)
					break;
				if (!escaped && c == '\\')
					escaped = 1;
				else
					escaped = 0;
			}
			token[length] = '\0';
			emit(quote == '"' ? "STRING" : "CHARACTER", token);
			continue;
		}

		if (c == '/') {
			int next = getchar();
			if (next == '/') {
				while ((c = getchar()) != EOF && c != '\n')
					append(token, &length, c);
				token[length] = '\0';
				emit("COMMENT", token);
				continue;
			}
			if (next == '*') {
				int previous = 0;
				while ((c = getchar()) != EOF) {
					if (previous == '*' && c == '/')
						break;
					if (previous)
						append(token, &length, '*');
					if (c == '*')
						previous = 1;
					else {
						append(token, &length, c);
						previous = 0;
					}
				}
				token[length] = '\0';
				emit("COMMENT", token);
				continue;
			}
			if (next != EOF)
				ungetc(next, stdin);
			emit("OPERATOR", "/");
			continue;
		}

		if (is_operator_char(c)) {
			int next = getchar();
			int pair = next != EOF &&
				((next == '=' && strchr("+-*/%=<>!&|^", c) != NULL) ||
				 (next == c && strchr("+-&|", c) != NULL) ||
				 (c == '-' && next == '>') ||
				 ((c == '<' || c == '>') && next == c));
			append(token, &length, c);
			if (pair) {
				append(token, &length, next);
				if ((c == '<' || c == '>') && next == c) {
					int third = getchar();
					if (third == '=')
						append(token, &length, third);
					else if (third != EOF)
						ungetc(third, stdin);
				}
			} else if (next != EOF) {
				ungetc(next, stdin);
			}
			token[length] = '\0';
			emit("OPERATOR", token);
			continue;
		}

		token[0] = (char)c;
		token[1] = '\0';
		emit(strchr("(){}[];,.:?", c) ? "PUNCTUATION" : "UNKNOWN", token);
	}
	return 0;
}
