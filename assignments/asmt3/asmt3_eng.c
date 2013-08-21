#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/* declare global vars */
/* define hamming string as a dynamic array of characters */ 
char *hcode = NULL;
int max_length, parity;
/***************************************************************/
void enter_params()
{
/* prompt for maximum hamming code length and for even/odd parity */
  printf("Enter the maximum length: ");
  scanf("%d", &max_length);
  printf("Enter the parity (0=even, 1=odd): ");
  scanf("%d", &parity);

/* allocate memory for hamming string based on maximum length and size of a character element*/
  hcode = (char *) malloc(max_length*sizeof(char));
  return;
}

/***************************************************************/
void check_code()
{
  /* declare local vars */
  int real_length, errors, par, temp_sum, i, j, k;
  errors = 0;
  /* prompt for hamming code as a "string"*/
  printf("Enter the Hamming code: ");
  scanf("%s", hcode);
  real_length = strlen(hcode);

  /* OUTER LOOP: for each parity bit in the Hamming code*/
  /* BEGIN OF OUTER LOOP */
  //  int i;
  for(i = 1; i <= real_length; i=i*2) {
    temp_sum = parity;
    //    int j;
    for(j = i; j <= real_length; j+=(2*i)) {
      //      int k;
      for(k = j; k <= real_length && k < j+i; k++) {
	temp_sum ^= hcode[real_length-k]-'0';
      }
    }
    errors += (i*temp_sum);
  } /* END OF OUTER LOOP */
/* report error in hamming code based on result from parity bits or report no error if none */
  if(errors == 0) printf("There is no bit error\n");
  else {
    printf("There is an error in bit: %d\n", errors);
    hcode[real_length-errors] ^= 1;
    printf("The corrected Hamming code is: %s\n", hcode);
  }
/* correct hamming code by flipping error bit (if necessary)*/
  
  return;
}

/***************************************************************/
int main()
{
/* print out menu, prompt for choice, and call appropriate procedure until user quits */

/* until program exits, print menu, select choice via switch statement and call appropriate function*/
  int loop = 1;
  int input = -1;
  /* Run the loop until the user chooses quit */
  while(loop) {
    printf("Error detection/correction:\n");
    printf("---------------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Check Hamming code\n");
    printf("3) Quit\n\n");
    printf("Enter selection: ");
    scanf("%d", &input);
    printf("\n");
    switch(input) {
    case 1:
      enter_params();
      break;
    case 2:
      check_code();
      break;
    case 3:
      loop = 0;
      break;
    default:
      printf("Invalid selection.");
    }
    printf("\n\n");
  }

  return 0;
}
