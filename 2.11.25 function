//
// Created by Lenovo on 29.10.2025.
//

#ifndef FUNCTION_PROJECT_1_STUDENT_1_H
#define FUNCTION_PROJECT_1_STUDENT_1_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH_OF_NUMBER 13
#define MAX_LENGTH_OF_FRACTIONAL_PART 12
#define MEMORY_ERROR_CHAR NULL
#define MEMORY_ERROR_DOUBLE (-1.0)
#define MEMORY_ERROR_INT (-1)
#define ALL_DIGITS_MAX 100
int CheckInput();
int ValidateBase(int);
int CharToValue(char);
char ValueToChar(int);
char* AcceptableSymbols(int);
int ValidateNumber(char *, int, int);
void SplitNumberString(char* , char*,char*);
long long IntStringToDecimal(char*, int);
double FracStringToDecimal(char*, int, int);
double StringToDecimal(char*, int);
char* IntDecimalToString(long long, int);
char* FloatDecimalToString(double, int);
char* DecimalToString(double, int);
char *Rounding(char*, int );
int MaxDidgits(char*, int, int, int);
void AddingUnut(char*,char*, int, int, int);
#endif

/* Checks that there are no more characters after the number entered.
 * Reads all characters until the end of the line.
 * If anything other than a space or tab is encountered, considers the
 * input to be incorrected */
int inline CheckInput() {
    int nextchar;
    while ((nextchar = getchar()) != '\n') {
        if (nextchar != ' ' && nextchar != '\t')
            return 0;
    }
    return 1;
}

/*checks the validity of the number system*/
int inline ValidateBase(int base) {
    if (base >= 2 && base <= 16)
        return 1;
    return 0;
}

/* Returns the numeric value of a character using the ASCII table. */
int inline CharToValue(char c) {
    if (c >= '0' && c <= '9')
        return c - '0';

    if (c >= 'a' && c <= 'f')
        return c - 'a' + 10;

    if (c >= 'A' && c <= 'F')
        return c - 'A' + 10;
    return -1;
}

/* Returns the character designation of a number using the ASCII table. */
char inline ValueToChar(int value) {
    if (value >= 0 && value <= 9)
        return (char)('0' + value);

    return (char)('a' + (value - 10));
}


/* Returns a list of characters that are valid in the given number system. */
char inline *AcceptableSymbols(int base) {
    int lenlist;

    if (base <= 10)
        lenlist = base + 1;

    /* For a base greater than 9, the list needs a space for uppercase
     *letters, because the function ValueToChar only returns lowercase letters */
    else
        lenlist = base + (base - 10) + 1;

    char *listofcharacters = malloc((lenlist + 1) * sizeof(char));

    if (listofcharacters == NULL)
        return MEMORY_ERROR_CHAR;

    int capitalletters = 0;

    for (int i = 0; i < base; i++) {
        *(listofcharacters + i) = ValueToChar(i);

        /* Adds uppercase letters, leaving space for a point */
        if (i >= 10) {
            capitalletters++;
            *(listofcharacters + lenlist - 1 - capitalletters) = (char)('A' + (i - 10));
        }
        }

        *(listofcharacters + lenlist - 1) = '.';
        *(listofcharacters + lenlist) = '\0';

        return listofcharacters;
    }

/* checks that all characters in the number satisfy the given number system
 * and that there are no leading zeros, dots at the beginning and end of the
 * number, or more than one point*/
int inline ValidateNumber(char *number, int base, int len) {
    char *list = AcceptableSymbols(base);

    if (list == NULL)
        return MEMORY_ERROR_INT;

    if (*number == '.' || *(number + len - 1) == '.') {
        free(list);
        return 0;
    }
    int point = 0;

    for (int i = 0; i < len; i++)
        if (*(number + i) == '.') {
            point++;

            if (point > 1) {
                free(list);
                return 0;
            }
        }
    /* Checks that each character in the string appears in the list*/
    for (int i = 0; i < len; i++) {
        int validcharacter = 0;

        for (int j = 0; *(list + j) != '\0'; j++)
            if (*(number + i) == *(list + j)) {
                validcharacter = 1;
                break;
            }

        if (validcharacter == 0) {
            free(list);
            return 0;
        }
    }

    /* Checks that an integer does not start with 0 if the number is not zero */
    if (point == 0 && *number == '0' && len != 1){
    free(list);
    return 0;
}
    /* Checks that a real number can only start with 0 when its integer part
     * is zero*/
    if (point == 1 && *number == '0' && *(number + 1) != '.') {
        free(list);
        return 0;
    }
    free(list);
    return 1;
}

/*Splits a string number into its integer and fractional parts.*/
void inline SplitNumberString(char* number, char* integerpart, char* fractionalpart) {

    int pointindex = 0;

    for (int i = 0; *(number + i) != '\0'; i++) {
        if (*(number + i) == '.') {
            pointindex = i;
            break;
        }
    }
    /* If there is no dot in the number,copies the integer part and
     * leaves the fractional part empty.*/
    if (pointindex == 0) {
        strcpy(integerpart, number);
        *fractionalpart = '\0';
    }
    else {
        /* copies the integer part*/
        strncpy(integerpart, number, pointindex);
        *(integerpart + pointindex) = '\0';

        /* copies the fractional part*/
        strcpy(fractionalpart, number + pointindex + 1);
    }
}

/* Converts an integer part from a certain number system to decimal using
 * the Gorner algorithm */
long long inline IntStringToDecimal(char* integerpart, int base) {
    long long result = 0;

    for (int i = 0; *(integerpart + i) != '\0'; i++)
        result = result * base + CharToValue(*(integerpart + i));

    return result;
}

/* Converts a fractional part from a certain number system to decimal. */
double inline FracStringToDecimal(char* fractionalpart, int base, int len) {
    double result = 0;
    for (int i = len - 1; i >= 0; i--)
        result = (result + CharToValue(*(fractionalpart + i))) / base;
    return result;
}

/* Converts the integer and fractional parts of a number to the decimal system
 *and sums the results*/
double inline StringToDecimal(char* number, int base) {
    char* integerpart = malloc( (MAX_LENGTH_OF_NUMBER + 1) * sizeof(char));

    if (integerpart == NULL)
        return MEMORY_ERROR_DOUBLE;

    char* fractionalpart = malloc( (MAX_LENGTH_OF_FRACTIONAL_PART + 1) * sizeof(char));

    if (fractionalpart == NULL) {
        free(integerpart);
        return MEMORY_ERROR_DOUBLE;
    }

    SplitNumberString(number, integerpart, fractionalpart);

    long long intpartindecimal = IntStringToDecimal(integerpart, base);
    double fracpartindecimal = FracStringToDecimal(fractionalpart, base, (int)strlen(fractionalpart));

    double result = (double)intpartindecimal + fracpartindecimal;

    free(integerpart);
    free(fractionalpart);

    return result;
}

/* Converts an integer from decimal to a certain number system. */
char inline * IntDecimalToString(long long number, int base) {
    if (number == 0) {
        char *res = malloc(2 * sizeof(char));

        if (res == NULL)
            return MEMORY_ERROR_CHAR;

        *res = '0';
        *(res + 1) = '\0';
        return res;
    }

    int lenres = 0;
    long long copynum = number;

    /* Defines the length of the converted number. */
    while (copynum > 0) {
        lenres++;
        copynum /= base;
    }

    char *result = malloc((lenres + 1)  * sizeof(char));

    if (result == NULL)
        return MEMORY_ERROR_CHAR;

    *(result + lenres) = '\0';

    /* Fills an array with characters in reverse order. */
    int i = lenres - 1;
    while (number > 0) {
        char character = ValueToChar((int)(number % base));
        *(result + i) = character;
        number /= base;
        i--;
    }

    return result;
}

/* Converts the fractional part of a number from decimal to a certain number
 * system. Multiplies the fractional part by the base of the number system.
 * The character designation of the integer part of the resulting number
 * is the first digit after the decimal point of the converted number.
 * The fractional remainder is then converted in a similar manner. */
char inline *FloatDecimalToString(double number, int base) {
    int signsafterpoint = 0;
    char *result = malloc((MAX_LENGTH_OF_FRACTIONAL_PART + 1 + 1) * sizeof(char));

    if (result == NULL)
        return MEMORY_ERROR_CHAR;

    /* Needs to get the first 13 digits after decimal point for rounding*/
    while (signsafterpoint < MAX_LENGTH_OF_FRACTIONAL_PART + 1) {
        char character = ValueToChar((int)(number * base));

        *(result + signsafterpoint) = character;
        signsafterpoint ++;

        number = number * base - (int)(number * base);

        /* Returns the result earlier if there are fewer than 13 digits after
         * the decimal point.*/
        if (number == 0) {
            *(result + signsafterpoint) = '\0';
            return result;
        }
    }
    *(result + signsafterpoint) = '\0';
    return result;
}

/*Converts a number from the decimal number system to the finite number system*/
char inline *DecimalToString(double number, int base) {

    long long integerpart = (long long)number ;
    double fractionalpart = number - (double)integerpart ;

    /*If the number does not contain a fractional part, simply convert it.*/
    if (number == (double)integerpart) {
        char* result = IntDecimalToString((long long)number, base);
        return result;
    }

    /* If there is a fractional part, it converts the integer and fractional parts
     * separately and combines the results*/
    char* convintpart = IntDecimalToString(integerpart, base);

    if (convintpart == NULL) {
        return MEMORY_ERROR_CHAR;
    }

    char* convfracpart = FloatDecimalToString(fractionalpart, base);
    if (convfracpart == NULL) {
        free(convintpart);
        return MEMORY_ERROR_CHAR;
    }

    /* Determines the length of the result, including the point */
    int lenres = (int)strlen(convintpart) + (int)strlen(convfracpart) + 1;

    char* result = malloc((lenres + 1) * sizeof(char));

    if (result == NULL)
        return MEMORY_ERROR_CHAR;

    int pointindex = 0;
    for (int i = 0; i < strlen(convintpart); i++) {
        *(result + i) = *(convintpart + i);
        pointindex = i + 1;
    }

    *(result + pointindex) = '.';
    int j = 0;
    for (int i = pointindex + 1; i <= pointindex + strlen(convfracpart); i++) {
        *(result + i) = *(convfracpart + j);
        j++;
    }

    *(result + lenres) = '\0';

    free(convfracpart);
    free(convintpart);

    return result;
}

/* if all the digits on this segment are equal to the maximum digit in this
 * number system, then returns ALL_DIGITS_MAX, otherwise returns the index
 * of the digit that is less than base - 1 and occupies the rightmost position. */
int inline MaxDidgits(char* number, int index1, int index2, int base) {
    for (int i = index2; i >= index1; i--)
        if (CharToValue(*(number + i)) < base - 1)
            return i;
    return ALL_DIGITS_MAX;
}

/* Increases the number with a digit less than base -1 by one */
void inline AddingUnut(char *number,char *result, int index1, int index2, int nomaxdigitingex) {
    int flag = 0;
    int flagpoint = 0;

    for (int i = index1; i <= index2; i++) {
        if (*(number + i) == '.')
            flagpoint = 1;

        /* The digit at the position whose index was found using
         * the MaxDigits function is increased by 1.*/
        if (i == nomaxdigitingex) {
            int valuechar = CharToValue(*(number + i));
            *(result + i) = ValueToChar(valuechar + 1) ;
            flag = 1;
        }
        /*All numbers before the one being changed are copied*/
        else if (flag == 0)
            *(result + i) = *(number + i);

        /* If the digit being changed is in the fractional
         * part, then the remaining digits are discarded,
         * if in an integer, then they are replaced by zeros.*/
        else

            if (*(number + i) == '.')
                *(result + i) = '.';
            else if (flagpoint == 0)
                *(result + i) = '0';
            else {
                *(result + i) = '\0';
                break;
            }
    }
    *(result + index2 + 1) = '\0';
}


/* Rounds the number to 12 decimal places */
char inline *Rounding(char* number, int base) {
    int len = (int)strlen(number);
    int pointindex = -1;

    for (int i = 0; i < len; i++) {
        if (*(number + i) == '.') {
            pointindex = i;
            break;
        }
    }
    /* If number is an integer, returns it */
    if (pointindex == -1) {
        char *result = malloc((len + 1) * sizeof(char));

        if (result == NULL)
            return MEMORY_ERROR_CHAR;

        strcpy(result, number);
        return result;
    }

    int lenfracpart = len - pointindex - 1;

    /* If the number has no more than 12 decimal places, returns it */
    if (lenfracpart <= MAX_LENGTH_OF_FRACTIONAL_PART) {
        char *result = malloc((len + 1) * sizeof(char));

        if (result == NULL)
            return MEMORY_ERROR_CHAR;

        strcpy(result, number);
        return result;
    }
        /* If the value of the last digit is less than half the base of the number
         * system, simply discards the last digit and returns number */
        int valeulastdigit = CharToValue(*(number + len - 1));
        if (valeulastdigit < (double)base / 2) {
            char* result = malloc(len * sizeof(char));

            if (result == NULL)
                return MEMORY_ERROR_CHAR;

            strncpy(result, number, len-1);
            *(result + len - 1) = '\0';
            return result;
        }

        /* If the first 12 digits of the fractional part are equal to the maximum
         * in the given number system, returns the integer part of the number
         * increased by 1 */
        int digitfracpart = MaxDidgits(number, pointindex + 1, len - 2, base);

        if (digitfracpart == ALL_DIGITS_MAX) {
            int digitintpart = MaxDidgits(number, 0, pointindex - 1, base);

            /*If all digits of the integer part are equal to the maximum
             *possible in a given number system, returns 100...0, Where the
             *number of zeros is equal to the length of the integer part
             *of the given number  */
            if (digitintpart== ALL_DIGITS_MAX) {
                int lenres = pointindex + 1;

                char *result = malloc((lenres + 1) * sizeof(char));

                if (result == NULL)
                    return MEMORY_ERROR_CHAR;

                *result = '1';
                for (int i = 1; i < lenres; i++)
                    *(result + i) = '0';

                *(result + lenres) = '\0';
                return result;
            }

            /* If not all digits of the integer part are equal to the maximum
             * in a given number system, uses the function AddingUnit */
            char *result = malloc((pointindex + 1) * sizeof(char));

            if (result == NULL)
                return MEMORY_ERROR_CHAR;

            AddingUnut(number,result,0,pointindex - 1, digitintpart);
            return result;
        }

        /* If not first 12 digits of the fractional part are equal to the maximum
        * in a given number system, uses the function AddingUnit */
        char *result = malloc(len * sizeof(char));

        if (result == NULL)
            return MEMORY_ERROR_CHAR;

        AddingUnut(number, result, 0, len - 2, digitfracpart);
        return result;
    }



