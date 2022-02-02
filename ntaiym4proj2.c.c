// a program that reads symbols from data and pushes it into a stack. Program determines if there is a matching symbol 
// that belongs to it and if not reports 1 of 3 errors, 1: missing opening symbol 2: expected a different closing symbol 3: missing a closing symbol
// 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE  1
#define FALSE 0

int DebugMode;


// struct for the stack - handles the array, size of the array and the last element
struct my_stack{
    
    char* array;  // pointer to the dynamic array that actually holds the stack
    int size;  // the integer variable specifying the current size of the dynamic array 
    int end; // the integer variable specifying the top of the stack 
    
};

// this fuction initializes the array using Stack
void init(struct my_stack* myStack){ 
    myStack->array = (char*)malloc(2 * sizeof(char));
    myStack->size = 2;
    myStack->end = 0;
}


// Function used to check if the stack will be empty.
int is_empty(struct my_stack* myStack)
{
    if (myStack->end == 0)
        return 1;
    else
        return 0;
}

// Function that will pushand or add any element into the stack.
void push(struct my_stack* myStack, char elem)
{
    myStack->array[myStack->end] = elem;
    myStack->end++;

    if (myStack->end == myStack->size) // if stack array is full than grow the size
    {
        char* newArr = (char*)malloc((myStack->size * 2) * sizeof(char));
        int i = 0;
        while (i < myStack->size){
            newArr[i] = myStack->array[i];
            i++;
        }
        myStack->array = newArr;
        myStack->size = 2 * myStack->size;

    }
}

// Function that will pop and or remove an element off the stack.
void pop(struct my_stack* myStack)
{
    myStack->end--;
}

// returns top element of struct
char top(struct my_stack* myStack)
{
    return myStack->array[myStack->end - 1];
}


// Function that will access / return the top elemnt of the stack after it has been already called.
void clear(struct my_stack* myStack)
{
    myStack->array = (char*)malloc(2 * sizeof(char));
    myStack->size = 2;
    myStack->end = 0;
}

int main (int argc, char** argv)
{
 char input[301];
 struct my_stack myStack;
 
 myStack.size = -1;
 myStack.end = -1;
 
 init(&myStack);
 

 /* check for command line argument of -d */
 DebugMode = FALSE;
 
 // debugging 
 int i, j, k, q;
 for (i = 0; i < argc; i++)
    if ( strcmp (argv[i], "-d") == 0)
       DebugMode = TRUE;

 /* set up an infinite loop */
 while (1)
 {
    /* get line of input from standard input */
    printf ("\nEnter input to check or q to quit\n");
    fgets(input, 300, stdin);
    int count = 0;
    
   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;
   }
   input[i] = '\0';

   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
 
   printf ("%s\n", input);
    
    i = 0;
        int val = 1;
        
        while (input[i] != '\0')
        {
            if (input[i] == '(' || input[i] == '{' || input[i] == '[' || input[i] == '<')
            {
                push(&myStack, input[i]); // pushing symbols into the stack
            }

            else if (input[i] == ')' || input[i] == '}' || input[i] == ']' || input[i] == '>')
            {
                if (is_empty(&myStack))
                {
                    char key;
                    if (')' == input[i]) {
                        key = '(';
                    }
                    else if ('}' == input[i]) {
                        key = '{';
                    }
                    else if (']' == input[i]) {
                        key = '[';
                    }
                    else if ('>' == input[i]) {
                        key = '<';
                    }
                    
                    int j = 0;
                    while (j < count) {
                        printf(" ");
                        j++;
                    }
                    printf("^ missing %c\n", key);  // error 1 for missing opening key
                    
                    val = 0;
                    break;
                }
                // pops the opening key from the stack
                if (input[i] == ')' && top(&myStack) == '('){
                    pop(&myStack);
                }
                else if (input[i] == '}' && top(&myStack) == '{') {
                    pop(&myStack);
                }
                    
                else if (input[i] == ']' && top(&myStack) == '[') {
                    pop(&myStack);
                }
                else if (input[i] == '>' && top(&myStack) == '<'){
                    pop(&myStack);
                }
                
                else { // verifies the top of the stack contains the matching symbol 
                    char symbol;
                    if ('(' == top(&myStack)) {
                        symbol = ')';
                    }
                    else if ('{' == top(&myStack)) {
                        symbol = '}';
                    }
                        
                    else if ('[' == top(&myStack)) {
                        symbol = ']';
                    }
                        
                    else if ('<' == top(&myStack)) {
                        symbol = '>';
                    }
                        
                    for (int k = 0; k < count; k++) {
                        printf(" ");
                    }
                    printf("^ expecting %c\n", symbol);  // error 2: expecting a different closing symbol
                    
                    j = 0;
                    break;
                }
            }

            i++;

            count++;

        }
        // verifies that the stack is empty
        if (is_empty(&myStack) && val) {
            printf("Expression is balanced\n");
        }
        else if (!is_empty(&myStack) && val) {
            char elem;
            if (top(&myStack) == '(') {
                elem = ')';
            }
            else if (top(&myStack) == '{') {
                elem = '}';
            }
            else if (top(&myStack) == '[') {
                elem = ']';
            }
            else if (top(&myStack) == '<') {
                elem = '>';
            }
            for (int k = 0; k < count; k++) {
                printf(" ");
            }
            printf("^ missing %c\n", elem); // error 3: missing a closing symbol
        }

        clear(&myStack); // clears stack so its ready to be used again
   /* run the algorithm to determine is input is balanced */

 }

 printf ("\nGoodbye\n");
 return 0;
}