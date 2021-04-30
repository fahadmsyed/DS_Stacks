#include "Stack.h"

/******
 * In this file, provide all of the definitions of the stack functions as described in stack.h.
 *
 * ****/


Stack newStack(int maximumStackSize){
    
    struct StackImp* s = (struct Stack*)malloc(sizeof(Stack));
    s->maxSize = maximumStackSize;
    s->count =0;
    s->stackElements = (union Element*)malloc(s->maxSize * sizeof( Element));
    return s;
}

void freeStack(Stack s){
    free(s->stackElements);
    free(s);
}

void push(Stack s, Element e){
    if(s->maxSize <= s->count){
        printf("Error: Stack is already full!\n");
    }
    else{
        s->stackElements[s->count] = e;
        //printf("operand is %c but operator is %c\n", e.operand, e.operation);
        s->count++;
    }
}

Element pop(Stack s){
    if (isEmpty(s)) {
        printf("Error: Unable to pop, the stack is empty!\n");
        return s->stackElements[-1];
    }
    s->count--;
    return s->stackElements[s->count];
}

int isEmpty(Stack s){
    if(s->count == 0)
        return 1;
    return 0;
}

Element topElement(Stack s){
    if (isEmpty(s))  {
        printf("Error: There is no top element, the stack is empty!\n");
        return s->stackElements[-1];
    }
    else{
        return s->stackElements[s->count-1];
    }
}

int getResult(int pop1, int pop2, char op){
    int a = 0;
    char b;
    if (op == '+'){
        a = (pop1 + pop2);
         b = (pop1 + pop2);
   // printf("int add %d, char add %d\n",a,b);
            return  (pop1 + pop2);
    }
    if (op == '-')
            return (pop2 - pop1);
    if (op == '*')
        return (pop1 * pop2);
    if (op == '/')
     return (pop2 / pop1);
}

int charConverter(char c){
    if(c < 48 || c > 57){
        printf("Error: This is not a number. It cannot be converted to int.\n");
        return 0;
    }
    if(c == 48)
        return 0;
    if(c == 49)
        return 1;
    if(c == 50)
        return 2;
    if(c == 51)
        return 3;
    if(c == 52)
        return 4;
    if(c == 53)
        return 5;
    if(c == 54)
        return 6;
    if(c == 55)
        return 7;
    if(c == 56)
        return 8;
    if(c == 57)
        return 9;
        
         
}