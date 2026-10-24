 #include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "keywords.h"

int isKeyword(char *word)
{
    for (int i = 0; i < KEYWORD_COUNT; i++)
    {
        if (strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' ||
            ch == '/' || ch == '=' || ch == '<' || ch == '>');
}

int isSpecialSymbol(char ch)
{
    return (ch == ';' || ch == ',' || ch == '(' ||
            ch == ')' || ch == '{' || ch == '}');
}

int main()
{
    FILE *fp;
    char ch, buffer[50];
    int i = 0;

    fp = stdin; // Read from standard input
    
    if (fp == NULL)
    {
        printf("Cannot open file\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        /* Identifier or Keyword */
        if (isalpha(ch))
        {
            buffer[i++] = ch;

            while (isalnum(ch = fgetc(fp)))
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';
            i = 0;
            fseek(fp, -1, SEEK_CUR);

            if (isKeyword(buffer))
                printf("Keyword: %s\n", buffer);
            else
                printf("Identifier: %s\n", buffer);
        }

        /* Number */
        else if (isdigit(ch))
        {
            buffer[i++] = ch;

            while (isdigit(ch = fgetc(fp)))
            {
                buffer[i++] = ch;
            }

            buffer[i] = '\0';
            i = 0;
            fseek(fp, -1, SEEK_CUR);

            printf("Number: %s\n", buffer);
        }

        /* Operator */
        else if (isOperator(ch))
        {
            printf("Operator: %c\n", ch);
        }

        /* Special Symbol */
        else if (isSpecialSymbol(ch))
        {
            printf("Special Symbol: %c\n", ch);
        }
    }

    fclose(fp);
    return 0;
}
