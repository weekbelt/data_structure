#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct
{
    element *data;
    int capacity;
    int top;
} StackType;

void init_stack(StackType *s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element *)malloc(s->capacity * sizeof(element));
}

int is_empty(StackType *s)
{
    return (s->top == -1);
}

int is_full(StackType *s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(StackType *s, element item)
{
    if (is_full(s))
    {
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

element pop(StackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[(s->top)--];
}

element peek(StackType *s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s->data[s->top];
}

int eval(char exp[])
{
    int op1, op2, value, i = 0;
    int len = strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);
    for (i = 0; i < len; i++)
    {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
        {
            value = ch - '0';
            push(&s, value);
        }
        else
        {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch)
            {
            case '+':
                push(&s, op1 + op2);
                break;
            case '-':
                push(&s, op1 - op2);
                break;
            case '*':
                push(&s, op1 * op2);
                break;
            case '/':
                push(&s, op1 / op2);
                break;
            }
        }
    }
    return pop(&s);
}

int main(void)
{
    int result;
    printf("후위표기식은 82/3-32*+\n");
    result = eval("82/3-32*+");
    printf("결과값은 %d\n", result);
    return 0;
}
