#include <stdio.h>

/* declare global var's */
float cpi = 0;
float exectime = 0;
float mips = 0;

/*********************************************************/
void get_params()
{
/* declare local var's and initialize*/
  int instrucNum = -1;
  int freq = -1;
  int acc = 0;
  int accInst = 0;
  /* prompt for # instruction classes & frequency of machine */
  printf("Enter the number of instruction classes: ");
  scanf("%d", &instrucNum); 
  printf("Enter the frequency of the machine (MHz): ");
  scanf("%d", &freq);

  /* Loop through the number of instruction classes and accumulate */
  int i = 0;
  for(i = 0; i < instrucNum; i++) {
    int tmpCpi = 0; // Holds the CPI of class
    int tmpIC = 0; // Holds the instruction count
    printf("Enter CPI of class %d: ", i+1);
    scanf("%d", &tmpCpi);
    printf("Enter instruction count of class %d (millions): ", i+1);
    scanf("%d", &tmpIC);
    acc += tmpCpi * tmpIC;
    accInst += tmpIC;
  }

  /* Calculate cpi, exectime, and mips, store in global variable */
  cpi = (float)acc/accInst;
  exectime = (float)1000*acc/freq;
  mips = accInst/(exectime/1000);
  
  return;
}

/*********************************************************/
void calc_cpi()
{
/* Print out result */
  printf("The average CPI of the sequence is: %.2f\n", cpi);
  return;
}

/*********************************************************/
void calc_exectime()
{
/* Print out result */
  printf("The total CPU time of the sequence is: %.2f msec\n", exectime);
  return;
}

void calc_mips()
{
/* Print out result */
  printf("The total MIPS of the sequence is: %.2f\n", mips);
  return;
}

int main()
{
/* declare local var's */

/* until user chooses to quit, print menu, 
 * select choice via switch statement and call appropriate function*/

  int loop = 1;
  int input = -1;
  /* Run the loop until the user chooses quit */
  while(loop) {
    printf("Performance assessment:\n");
    printf("-----------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Calculate average CPI of a sequence of instructions\n");
    printf("3) Calculate total execution time of a sequence of instructions\n");
    printf("4) Calculate MIPS of a sequence of instructions\n");
    printf("5) Quit\n\n");
    printf("Enter selection: ");
    scanf("%d", &input);
    switch(input) {
    case 1:
      get_params();
      break;
    case 2:
      calc_cpi();
      break;
    case 3:
      calc_exectime();
      break;
    case 4:
      calc_mips();
      break;
    case 5:
      loop = 0;
      break;
    default:
      printf("Invalid selection.\n");
    }
    printf("\n");
  }

  return 0;
}
