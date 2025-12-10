#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funcs.h"

#define PI 3.14159265359  // defining constants
#define e 2.718281828459  //

static double user_number(void); // function to take an floating point number from the user
static char user_operation(void); // allows the user to enter an operation for use in the arithmetic section of the calculator
static char continue_calc(void); // a function to allow the user to continue doing calculations in the same mode
static int type_of_unit(void); // the user can choose between radian or degree mode in the trig menu section
static int type_of_trig(void); // the user can enter which trig ratio they wish to use
static void radian_mode(void); // computes the value of the users trig calclation and outputs to terminal
static void degree_mode(void); // converts the users input/answer to degrees from radians and does the same as radian mode
static int type_of_log(void); // allows the user to choose which log they use
static int type_of_equation(void); // the user can choose between solving a linear or quadratic equation
static void linear_mode(void); // solves linear equations
static void quadratic_mode(void); // solves quadratics
double ans = 0; // declaration of vairables
double root1;   //
double root2;   //
double rootr;   //
double rooti;   //

// Arithmetic mode
void menu_item_1(void) {
    //  prints the curent calculator mode and clears any confusion with the rooting operation
    printf("\n>> Arithmetic: Complete arithmetic operations on numbers you enter.\nFor the root (R) operation, first enter the number you wish to be rooted, followed by the root\n");

    Arithmetic: // lable so the user can continue to complete calcualtions in this mode
    double num1 = user_number();  // Takes a user input, validates and converts to a float to be stored in the variable num1
    char operation = user_operation();  // Takes a user input, ensures its one of the 6 supported operations and stores this in the variable operation 
    double num2 = user_number(); 
    
    int div_by_zero = 0;

    // This switch implements the arithmetic operations and stores the value in the variable ans
    switch(operation){
        case '+':
            ans = num1 + num2;
            break;
        case '-':
            ans = num1 - num2;
            break;
        case '*':
            ans = num1 * num2;
            break;
        case '/':
            ans = num1 / num2;
            if (num2 == 0){  // I have used an if statement with the div_by_zero flag to allow the output of undefined, when division by zero takes place
                div_by_zero = 1;
            }
            break;
        case '^':
            ans = pow(num1, num2);
            break;
        case 'R':
            ans = pow(num1, 1/num2);
            break;
        default:
        break;

    }
    if(div_by_zero == 1){
        printf("%f %c %f = undefined ", num1, operation, num2);  // outputting undefined when division by zero takes place
    }
    else if(operation == 'R'){
        printf("%f ^ 1/%f = %f\n", num1, num2, ans);  // more clear way of showing a root.
    }
    else {
        printf("%f %c %f = %f\n", num1, operation, num2, ans);  // shows the results
    }

    char cont = continue_calc(); // allow the user to continue in this mode by entering y

    if (cont == 'y' || cont == 'Y'){
        goto Arithmetic; // jump to the top of the arithmetic section to allow more user inputs and calculations
    }

}
// Trig mode
void menu_item_2(void) {
    Trig: // label so the program can jump here if the user enters y to continue with calculations
    printf("\n>> Select an angle unit.\n");
    printf("\n\t1. Radians\n"
            "\t2. Degrees\n");
        int unit = type_of_unit(); // allow the user to enter 1 for radians and 2 for degrees
        
        switch(unit){ // select which mode to call depending on the users input
            case 1:
                radian_mode();
                break;
            case 2:
                degree_mode();
                break;
            default:
            break;
        }
    char cont = continue_calc();

    if (cont == 'y' || cont == 'Y'){
        goto Trig; // jump to where the user is asked to select their angle unit
    }
}
// Logarithms mode
void menu_item_3(void) {
    Logarithmic:
    printf("\n>> Logarithms\n");
    // allow the user to choose their desired logarithm
    int logarithm = type_of_log();
    int error = 0;

    // allow the user to enter a number they wish to calculate the log of, compute and output the answer.
    switch(logarithm){
        case 1:
        printf("\nenter the number you wish to perform the logarithm on ");
        double log10num = user_number();
            if(log10num <= 0){  // domain is all positive real numbers
                error = 1;
                goto Jump;
            }
        ans = log10(log10num);
        printf("\nlog10(%f) = %f ", log10num, ans);
        break;

        case 2:
        printf("\nenter the number you wish to perform the logarithm on ");
        double lnnum = user_number();
            if(lnnum <= 0){
                error = 1;
                goto Jump;
            }
        ans = log(lnnum);
        printf("\nln(%f) = %f ", lnnum, ans);
        break;

        // for case three, the user chooses the base for the log
        case 3:
        printf("\nenter the base of your logarithm"); 
        double base = user_number();
        printf("\nenter the number you wish to perfomr the logarithm on\n ");
        double lognnum = user_number();
            if(base < 0 || base == 1 || lognnum <= 0){ // domain is all positive real numbers and the base must be a positive real number != to 1
                error = 1;
                goto Jump;
            }
        ans = log(lognnum) / log(base); // ln(a) / ln(b) = log_b(a)
        printf("\nlog%f(%f) = %f",base, lognnum, ans);
        break;

        default:
        break;
    }
    Jump:
    if (error == 1){
        printf("MATH ERROR... your inputs must be within the logarithms domain\n");
    }

    // as before allows the user to continue calculations in this mode
    char cont = continue_calc();

    if (cont == 'y' || cont == 'Y'){
        goto Logarithmic;
    }
}
// Quadratic mode
void menu_item_4(void) {
    Quadratic:
    printf("\n>> Select a type of equation\n");
    printf("\n\t1. Linear\n"
            "\t2. Quadraric\n");

    // allow the user to select between a linear and quadratic equation solver
    int equation = type_of_equation();

        switch(equation){ // select which mode to call depending on the users input
            case 1:
                linear_mode();
                break;
            case 2:
                quadratic_mode();
                break;
            default:
            break;
        }

    // allow user to continue calculating in this mode
    char cont = continue_calc();

    if (cont == 'y' || cont == 'Y'){
        goto Quadratic;
    }

}


// These are my functions for taking and validating the users inputs
// they all follow a similar structure of using fgets to safely read the users input followed by using strcspn to stripp the trailing newline
// the functions then differe depending on what input is required
static double user_number(void){ 

    char buf[128];
    char *pend;
    int valid_input = 0;
    double value = 0;

    do {
        printf("\nEnter a number / 'pi' / 'e' / 'ans' ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        // if statement to allow the user to call the previous answer from their calculation
        // The if statement compares the users input string with the word ans.
        if(strcmp(buf, "ans") == 0){
            value = ans;  // set the user_input value to the previous answer to calculations
            valid_input = 1;  // exit loop
        }
        else if(strcmp(buf, "pi") == 0){ // Allow 'pi' as a valid input from the user
            value = PI;
            valid_input = 1;
        }
        else if(strcmp(buf, "e") == 0){ // Allow 'e' as a valid input from the user
            value = e;
            valid_input = 1;
        }
        else{
            //convert string to a floating-point number
            value = (double)strtod(buf, &pend);
            
            //if statement to check whether anything has been
            //converted or whether the whole input has been converted
            if(pend == buf || *pend!= '\0'){
                printf("Enter a valid integer or decimal number\n");
                valid_input = 0;
            }
            else{
                valid_input = 1;
            }
            }
    } while (!valid_input);

    return value;
}
static char user_operation(void){ 

    char buf[128];
    int valid_input = 0;
    char value = '\0' ;

    do {
        printf("\nEnter an operation (+,-,*,/,^,R) ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';
        
        if (strlen(buf) == 1){  // Esnure the user has only entered a single character 
            value = buf[0];  // Store the entered character into the value variable
            
            // This if ensures that the character the user entered is within the accepted operations
            // sets valid_input flag to 1 if this is the case
            if(value == '+' || value == '-' || value == '*' || value == '/' || value == '^' || value == 'R'){
            valid_input = 1;

            }
        }
        // If the valid_input flag is still equal to zero the user is prompted to enter a correct operation.
        else if(!valid_input){
            printf("please only enter one of the following operations (+,-,*,/,^,R)\n");
        }

          
    } while (!valid_input);

    return value;
}
static char continue_calc(void){ 

    char buf[128];
    int valid_input = 0;
    char value = '\0' ;

    do {
        printf("\nWould you like to complete another calulation? (y/n) ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';
        
        // if statement to check the users input for continueing with calculations in this menu
        if(strlen(buf) == 1){
            value = buf[0];

            if(value == 'y' || value == 'Y' || value == 'n' || value == 'N'){  // allow caps or lowercase
                valid_input = 1;
            }
        }
        
          
    } while (!valid_input);

    return value;
}
static int type_of_unit(void){

    char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        value = strtol(buf, NULL, 10); // convert string to long number
        if(value == 1 || value == 2){ // if one of the displayed choices is entered set valid input to true
            valid_input = 1;
        }
        else if (!valid_input){ 
            printf("\nchoose either radian mode (1), or degree mode (2)");
        }
    } while (!valid_input);

    return value;
}
static int type_of_trig(void){
    
    char buf[128];
    int valid_input = 0;
    int value = 0 ;

    do {
        printf("Choose your trig operator (sin, cos, tan, sinh, cosh, tanh, arcsin, arccos, arctan) ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';
        
        // if statement using strcmp to asign the value variable a number from 1 - 9 for use in the switch in my radian/degree modes
        if(strcmp(buf, "sin") == 0){ 
            value = 1;
            valid_input = 1;
        }
        else if(strcmp(buf, "cos") == 0){
            value = 2;
            valid_input = 1;
        }
        else if(strcmp(buf, "tan") == 0){
            value = 3;
            valid_input = 1;
        }
        else if(strcmp(buf, "sinh") == 0){
            value = 4;
            valid_input = 1;
        }
        else if(strcmp(buf, "cosh") == 0){
            value = 5;
            valid_input = 1;
        }
        else if(strcmp(buf, "tanh") == 0){
            value = 6;
            valid_input = 1;
        }
        else if(strcmp(buf, "arcsin") == 0){
            value = 7;
            valid_input = 1;
        }
        else if(strcmp(buf, "arccos") == 0){
            value = 8;
            valid_input = 1;
        }
        else if(strcmp(buf, "arctan") == 0){
            value = 9;
            valid_input = 1;
        }
          
    } while (!valid_input);

    return value;
}    
static int type_of_log(void){
    
    char buf[128];
    int valid_input = 0;
    int value = 0 ;

    do {
        printf("\nChoose your logarithm (log10, ln, logn) ");
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';
        
        // if statement using strcmp to assign the variable value a number from 1 to 3 for use in the switch statement in my quadratic menu
        if(strcmp(buf, "log10") == 0){
            value = 1;
            valid_input = 1;
        }
        else if(strcmp(buf, "ln") == 0){
            value = 2;
            valid_input = 1;
        }
        else if(strcmp(buf, "logn") == 0){
            value = 3;
            valid_input = 1;
        }
    } while (!valid_input);

    return value;
}    
static int type_of_equation(void){
// same as my type_of_unit function with a different message prompt
// allows the user to select between solving a linear or quadratic equation
char buf[128];
    int valid_input = 0;
    int value = 0;

    do {
        if (!fgets(buf, sizeof(buf), stdin)) {
            /* EOF or error; bail out gracefully */
            puts("\nInput error. Exiting.");
            exit(1);
        }

        // strip trailing newline
        buf[strcspn(buf, "\r\n")] = '\0';

        value = strtol(buf, NULL, 10); // convert string to long number
        if(value == 1 || value == 2){ // if one of the displayed choices is entered set valid input to true
            valid_input = 1;
        }
        else if (!valid_input){ 
            printf("\nchoose either a linear equation (1), or quadratic equation (2)");
        }
    } while (!valid_input);

    return value;
}

// Here are my functions for the trigonometry menu. They take the users input of trig function and number and output the answer
static void radian_mode(void){
    int operation = type_of_trig(); // calls a function to allow the user to enter their desired trig function
    double num = user_number();
    
    switch (operation) // switch statement that computes the anwser depending on which trig function is chosen
    {
    case 1:
        ans = sin(num);
        break;
    case 2:
        ans = cos(num);
        break;
    case 3:
        ans = tan(num);
        break;
    case 4:
        ans = sinh(num);
        break;
    case 5:
        ans = cosh(num);
        break;
    case 6:
        ans = tanh(num);
        break;
    case 7:
        ans = asin(num);
        break;
    case 8:
        ans = acos(num);
        break;
    case 9:
        ans = atan(num);
        break;
    default:
        break;
    }

    if(isnan(ans)){  // Checks if ans is NaN (not a number), this would be the case for example if the user enters arcsin(2) as its out of the domain -1< x <1
        printf("MATH ERROR ... you must enter values within the domain of the trig functions"); // returns an error message if the user has entered invalid values
        goto skip; // jump to after the switch that outputs the answers 
    }

     switch (operation)
    {
    case 1:
        printf("sin(%f) = %f ",num,ans);
        break;
    case 2:
        printf("cos(%f) = %f ",num,ans);
        break;
    case 3:
        printf("tan(%f) = %f ",num,ans);
        break;
    case 4:
        printf("sinh(%f) = %f ",num,ans);
        break;
    case 5:
        printf("cosh(%f) = %f ",num,ans);
        break;
    case 6:
        printf("tanh(%f) = %f ",num,ans);
        break;
    case 7:
        printf("arcsin(%f) = %f ",num,ans);
        break;
    case 8:
        printf("arccos(%f) = %f ",num,ans);;
        break;
    case 9:
        printf("arctan(%f) = %f ",num,ans);
        break;
    default:
        break;
    }
    skip: // label so the switch printing the answers can be skipped if ans = NaN
    
}
static void degree_mode(void){

    // identical to radian mode besides altering my answer by converting from degrees to radians
    Trig:
    int operation = type_of_trig();
    double num = user_number();
    
    switch (operation)
    {
    case 1:
        ans = sin(num*(PI/180)); // Multiplying the users input by PI/180, gives their input which is in degrees, in radians. 
        break;                   // This has been done as the trig functions take inputs in radians
    case 2:
        ans = cos(num*(PI/180));
        break;
    case 3:
        ans = tan(num*(PI/180));
        break;
    case 4:
        ans = sinh(num*(PI/180));
        break;
    case 5:
        ans = cosh(num*(PI/180));
        break;
    case 6:
        ans = tanh(num*(PI/180));
        break;
    case 7:
        ans = asin(num)*(180/PI); // Multiplying the output of the inverse trig functions by 180/PI gives the answer in degrees rather than radians
        break;
    case 8:
        ans = acos(num)*(180/PI);
        break;
    case 9:
        ans = atan(num)*(180/PI);
        break;
    default:
        break;
    }

    if(isnan(ans)){
        printf("MATH ERROR ... you must enter numbers within the domain your chosen trig function ");
        goto skip;
    }

     switch (operation)
    {
    case 1:
        printf("sin(%f) = %f ",num,ans);
        break;
    case 2:
        printf("cos(%f) = %f ",num,ans);
        break;
    case 3:
        printf("tan(%f) = %f ",num,ans);
        break;
    case 4:
        printf("sinh(%f) = %f ",num,ans);
        break;
    case 5:
        printf("cosh(%f) = %f ",num,ans);
        break;
    case 6:
        printf("tanh(%f) = %f ",num,ans);
        break;
    case 7:
        printf("arcsin(%f) = %f ",num,ans);
        break;
    case 8:
        printf("arccos(%f) = %f ",num,ans);;
        break;
    case 9:
        printf("arctan(%f) = %f ",num,ans);
        break;
    default:
        break;
    }
    skip:
}
// Here are my functions for the quadratic menu. They give the roots of quadratic/linear equations
static void linear_mode(void){
    // prompt user to enter the values a and b
    printf("\nax + b = 0");
    printf("\nEnter value (a) ");
        double a = user_number();
    printf("\nEnter value (b) ");
        double b = user_number();

    // calculate the value of x
    ans = (-b)/a;
    // output x
    printf("\nx = %f",ans);

}
static void quadratic_mode(void){
    // get the users inputs for the equation
    printf("\nax^2 + bx + c = 0");
    Quad:
    printf("\nEnter value (a) ");
        double a = user_number();
        if (a == 0){ // If a is equal to zero, the user is entering a linear equation and the answer given from this mode would be NaN due to division by zero
            printf("This is quadratic mode! enter a quadratic\n");
            goto Quad;

        }
    printf("\nEnter value (b) ");
        double b = user_number();
    printf("\nEnter value (c) ");
        double c = user_number();

    // calculate the discrimimant to be able to handle imaginary numbers
    double discriminant = b*b - 4*a*c;

    // if statement so different outputs can be given depending on the value of the discriminant

    if(discriminant > 0){  // if the discriminent is > 0, there are 2 real roots
        root1 = (-b + sqrt(discriminant))/(2*a);
        root2 = (-b - sqrt(discriminant))/(2*a);
        printf("\nx = %f or x = %f",root1, root2);
    }
    else if(discriminant == 0){  // if the discriminant is = 0 then there is a repeated root
        root1 = -b/(2*a);
        printf("\n one real root... x = %f",root1);
        
    }
    else if (discriminant < 0){  // if the discriminant is < 0, there are 2 imaginary roots
        rootr = -b/(2*a); // calculates the real part of the root
        rooti = sqrt(-discriminant)/(2*a); // calculates the imaginary part of the root
        printf("\nno real roots... x = %f + %fi, x = %f - %fi",rootr, rooti, rootr, rooti); // gives the roots as complex numbers
    }  

}