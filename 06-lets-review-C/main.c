/**
 * \file		main.c
 * \since		29-Apr-2023
 * \author		Andrei Jakab
 */

//----------------------------------------------------------------------------------------------------------
//   								Includes
//----------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//----------------------------------------------------------------------------------------------------------
//   								Macros
//----------------------------------------------------------------------------------------------------------
// constants
#define MAX_STRING_LEN 10000 /*!< Maximum input string length */

// debug macros
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) \
    do                 \
    {                  \
    } while (0)
#endif

//----------------------------------------------------------------------------------------------------------
//   								Prototypes
//----------------------------------------------------------------------------------------------------------
void processString(char *, char *, int);

//----------------------------------------------------------------------------------------------------------
//   								Code
//----------------------------------------------------------------------------------------------------------
int main()
{
    // variable declarations
    char inputString[MAX_STRING_LEN + 1]; // storage for input string
    char **pOutputStrings;                // array of output strings
    int i = 0;                            // loop counter
    int outputStringLen = -1;             // length of output string
    int T = -1;                           // number of test cases

    // read number of test cases
    scanf("%d%*c", &T);
    if (T < 1)
    {
        printf("Invalid number of test cases entered.\n");
        exit(1);
    }
    else
    {
        DEBUG_PRINT(("# of test cases: %d\n", T));
    }

    // allocate memory for output strings
    pOutputStrings = calloc(T, sizeof(char *));
    if (pOutputStrings == NULL)
    {
        perror("calloc() failed");
        exit(1);
    }

    // generate output
    for (i = 0; i < T; i++)
    {
        // read input string
        scanf("%[^\n]%*c", inputString);

        // allocate memory for resulting output string
        outputStringLen = strlen(inputString) + 2;
        pOutputStrings[i] = (char *)calloc(outputStringLen, sizeof(char));
        if (pOutputStrings == NULL)
        {
            perror("calloc() failed");
            exit(1);
        }

        // process input string
        processString(inputString, pOutputStrings[i], outputStringLen);
    }

    // display output
    for (i = 0; i < T; i++)
    {
        // display output string
        printf("%s\n", pOutputStrings[i]);

        // release memory allocated for current output string
        free(pOutputStrings[i]);
    }

    // release memory allocated for output strings array
    free(pOutputStrings);

    return 0;
}

/**
 * \brief		Separate even and odd numbered characters of the input string and return them in the output string.
 *
 * \param[in]	inputString input string array
 * \param[in]	pOutputString output string array
 * \param[in]	outputStringLen length of output string array (in # of characters)
 */
void processString(char *inputString, char *pOutputString, int outputStringLen)
{
    int i;                                       // loop counter
    int inputStringLength = strlen(inputString); // length of input string
    int outputStringMid = -1;                    // mid point out output string
    int letterIndex = 0;                         // location where character should be inserted in output string

    // calculate output string midpoint
    outputStringMid = outputStringLen / 2;
    if (outputStringLen % 2 == 0)
    {
        // for even length output strings, subtract 1 position
        outputStringMid -= 1;
    }

    // separate input string into even and odd letteres
    for (i = 0; i < inputStringLength; i++)
    {
        if (i % 2 == 0)
        {
            pOutputString[letterIndex] = inputString[i];
        }
        else
        {
            pOutputString[letterIndex + outputStringMid + 1] = inputString[i];
            letterIndex++;
        }
    }

    // insert space between even and odd letters
    pOutputString[outputStringMid] = ' ';

    return;
}