#include "Stack.h"


#define MAX_LINE_LENGTH 50


int convertToPostfix(char *infixString, char *postfixString);
int evaluatePostfix(char *postfixString);


int main()
{
	FILE *inputFile;
	inputFile = fopen("p1Input.txt", "r");
	if(inputFile == NULL){

		perror("Error opening file");
		return -1;
	}


	//This string will hold the infix equations that are read from inputFile, one at a time.
	char infixString[MAX_LINE_LENGTH];


	//Use fgets to read the next line from the inputFile.
	//Store the line into infixString.
	//The while loop repeats until there are no more lines in the file.
	while(fgets(infixString, MAX_LINE_LENGTH, inputFile)!=NULL){

		//If the line is blank, skip it.
		if(infixString[0] == '\n')
			continue;

		printf("Current infix string: %s",infixString);

		//postfixString is a string to store the equation from szInfixString converted into postfix.
		char postfixString[MAX_LINE_LENGTH];

		//Call the convertToPostfix function (that you are to implement below main).
		int returnMessage = convertToPostfix(infixString,postfixString);


		//convertToPostfix should return an integer letting us know if the infix string was in a valid format.
		//If the format is valid (we returned 0), then we call the evalutaePostfix function (that you are to implement below), and print the result of the evalution.
		//If the format is not valid (we returned something other than 0), then we print the corresponding error message.
		switch(returnMessage)
		{

			case 0: //0 means the infix string had no errors.  Go ahead and evaluate the postfix string.
				printf("Postfix string: %s\n",postfixString);
				int result = evaluatePostfix(postfixString);
				printf("It evaluates to %d.\n",result);
				break;
			case 1:  //1 means the infix string is missing a left parenthesis.
				printf("WARNING: Missing left parenthesis.\n");
				break;
			case 2: //2 means the infix string is missing a right parenthesis.
				printf("WARNING: Missing right parenthesis.\n");
				break;
			case 3: // 3 means missing operator.
				printf("WARNING: Missing operator.\n");
				break;
			case 4: //4 means missing operand.
				printf("WARNING: Missing operand.\n");
				break;
			default:
				printf("WARNING: %d.\n", returnMessage);


		}


		printf("\n\n");
	}

	fclose(inputFile);

	return 0;
}


/*******
int convertToPostfix(char *infixString, char *postfixString)

Input: 
infixString is a character array of length <= MAX_LINE_LENGTH that contains an equation in infix format.
postfixString is a currently empty character array of length <= MAX_LINE_LENGTH that we should fill with a postfix representation of infixString.

Output:
We return an integer based on any errors found in infixString.
If there are no errors, return 0.
If there is a missing (, return 1.
If there is a missing ), return 2.
If there is a missing operator, return 3 (for extra credit).
If there is a missing operand, return 4 (for extra credit).
*********/
int convertToPostfix(char *infixString, char *postfixString){
    int operators= 0;
    int x, y = 0;
    int operands = 0;
    int parenthesis = 0;
    //int ascii = 0;
    int position = 0;
    int end, count, used = 0;
    char *subject;
    char ascii;
    char prevascii;
    Stack *s = newStack(MAX_LINE_LENGTH);
    Element* e = ( Element*)malloc(sizeof(  Element));
    
    count = 0; 
    
    for(x = 0; x < strlen(infixString); x++){
        //printf("%d is the strlen\n",strlen(infixString));
        subject = &infixString[x];
        //printf("there is no physical way count is messing up! See? its only at %d!\n", count);
        ascii = *subject;
        
        if(ascii >= 40){
            
            if(prevascii == ascii || prevascii == ascii - 1 || (!((ascii >=40 && ascii <=43) || ascii == 45 || ascii == 47 || (ascii >= 48 && ascii <= 57)))){
                break;
            }
           // printf("ascii %c\n",ascii);
       // printf("%d %d\n", ascii, MAX_LINE_LENGTH);
        if(ascii >= 42 && ascii <= 47){
          if(prevascii == 0){  
            prevascii = ascii;
          } 
          
          else if((prevascii == 42 || prevascii == 47)&& (count>1)){
                if(ascii == 43 || ascii == 45){
                    e->operation = ascii;
                    push(s, *e);
                     e->operation = prevascii;
                     push(s, *e);
                     postfixString[position] = pop(s).operation;
                     position++;
            used++;
            count = 1;
                }
                else{
                    e->operation = ascii;
                    push(s, *e);
                     e->operation = prevascii;
                     push(s, *e);
                     position++;
            used++;
            count = 1;
                     
                }
            }
          else{
              
         
            e->operation = ascii;
            push(s, *e);
            if(count > 1){
            postfixString[position] = pop(s).operation;
            
            
             
            position++;
            used++;
            count = 1;
           
            }
           
             }
           operators+=1;
        }
        if(ascii >= 48 && ascii <= 57){
            operands++;
            postfixString[position] = ascii;
            position++;
            count = count+1;
        }
        if(ascii == 40){
            parenthesis++;
           // printf("left parenthesis registered\n");
        }
        if(ascii == 41){
            if(parenthesis ==0)
                return 1;
            parenthesis-= 1;
           // printf("right parenthesis registered\n");
        }
        
    }
    }
    //printf("first loop\n");
    for(y = 0; y < operators-used; y++){
        if(used == 0){
            e->operation = prevascii;
            push(s,*e);
        }
        if(isEmpty(s) != 1 && postfixString[position] != 64){
            
           // printf("isEmpty statement passed!\n");
            //print 
        postfixString[position] = pop(s).operation;
        position++;
        
        }
    }
   // printf("second loop\n");
    
   
    freeStack(s);
    free(e);
    
    if(parenthesis !=0){
        if(parenthesis > 0){
            return 2;
        }
        else{
            return 1;
        }
    }
   // printf("operators:%d operands:%d\n", operators, operands);
    if (operators != operands -1){
        if (operators >= operands){
            return 4;                        // block used to determine if there is a missing operator or operand
        }
        else{
            return 3;
        }
    }
    
    return 0;
    
    
	
}



/************
evaluatePostfix(char *postfixString)

Input:
postfixString is a string of length <= MAX_LINE_LENGTH that contains an equation in postfix representation.
If your convertToPostfix() function is correct, this string should be in a valid postfix format.

Output:
Return an integer representing what the postfix equation evaluated to.
************/
int evaluatePostfix(char *postfixString){
    int eval, x = 0;
    char* subject;
    char ascii;
    int pop1;
    int pop2;
    int final;
    
    Stack *s = newStack(MAX_LINE_LENGTH);
    Element* f = ( Element*)malloc(sizeof(  Element));
   /* int eval, x, pop1, pop2, times, times2   = 0;
   char operator, timer; 
   int ascii1, ascii2;
   char *subject1;
   char *subject2;
   
    Stack *t = newStack(MAX_LINE_LENGTH);
    Element* i = ( Element*)malloc(sizeof(  Element));
    Element* f = ( Element*)malloc(sizeof(  Element));
    Element* g = ( Element*)malloc(sizeof(  Element));
    Element* h = ( Element*)malloc(sizeof(  Element));
    for(x = 0; x < strlen(postfixString)/2;x++){
        subject1 = &postfixString[x];
        subject2 = &postfixString[x+1];
        times =  postfixString[x];
        times2 = postfixString[x+1];
        printf("s1 %c", times);
        ascii1 = &subject1;
        ascii2 = &subject2;
        i->operand = ascii1;
        f->operand = ascii2;
        push(t, *f);
        push(t, *i);
        pop1= pop(t).operand;
        printf("pop1 is %d\n", pop1);
        pop2= pop(t).operand;
        printf("pop2 is %d\n", pop2);
        g->operation = &postfixString[strlen(postfixString)-times-1];
        push(t,*g);
        operator = pop(t).operation;
        h->operand = (getResult(pop1, pop2, operator));
        push(t,*h);
      
    */
    
    for(x = 0; x < strlen(postfixString);x++){
    subject = &postfixString[x];
    ascii = *subject;
        if(ascii >= 42 && ascii <= 47){
           // printf("ascii as char %c and int %d\n", ascii, ascii);
            pop1 =  pop(s).operand ;
            pop2 =  pop(s).operand;
           // printf("p1 is %c and p2 is %d\n", pop1, pop2);
            f->operand = getResult(pop1, pop2, ascii);
           // printf("dec result %d, char result %c\n",getResult(pop1, pop2, ascii),getResult(pop1, pop2, ascii));
            push(s, *f);
        }
        if(ascii >= 48 && ascii <= 57){
         //   printf("ascii as char %c and int %d\n", ascii, ascii);
            f->operand = charConverter(ascii);
            //printf("%d operation for operand\n", f->operation);
            push(s, *f);
        }
    }
    
    final = pop(s).operation;
    return final;

}
