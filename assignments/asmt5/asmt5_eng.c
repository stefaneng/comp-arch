#include <stdio.h>
#include <stdlib.h>

int n; // Number of instructions

struct node {
  int dest;
  int src1;
  int src2;
  int delay;
} *set = NULL;
typedef struct node instr;

void printChart() {
  int i, j;
  for(i = 1; i <= n; i++) {
    printf("%d) ", i);
    for(j = 0; j < set[i].delay; j++) {
      printf("\t");
    }
    printf("FI\tDI\tCO\tFO\tEI\tWO\n");
  }
}

/* Option 1: Enter instructions */
void enterInstr() {
  char instr_string[8];
  printf("Enter total number of instructions: ");
  scanf("%d",&n);
  set = (instr *) malloc((n+1)*sizeof(instr));
  set[0].dest = -1;
  int i;
  for(i = 1;i <= n; i++) {
    printf("%d) ",i);
    scanf("%s", instr_string);
    set[i].dest = instr_string[1];
    set[i].src1 = instr_string[4];
    set[i].src2 = instr_string[7];
  }
} // End option 1

/* Option 2: Pipeline */
void pipeline() {
  set[1].delay = 0;
  int dep_delay, overlap;
  int i;
  for(i = 2; i <= n; i++) {
    // Check for a raw dep
    dep_delay = 0; // Assume instr is independent
    if((set[i-2].dest == set[i].src1) ||
       (set[i-2].dest == set[i].src2)) {
      if(overlap == 0) {
	dep_delay = 1;
	overlap = 1;
      }
      else {
	dep_delay = 0;
	overlap = 0;
      }
    }
    else { // Not dependent
      overlap = 0;
    }
    if((set[i-1].dest == set[i].src1) ||
       (set[i-1].dest == set[i].src2)) {
      dep_delay = 2;
      overlap = 1;
    }
    set[i].delay = set[i-1].delay + dep_delay + 1;
  } // End for loop
  printf("Total number of cycles: %d\n", set[n].delay + 6);
  printChart();
}

/* Option 3: Superscalar */
void superscalar() {
  int pipe_delay = 1;
  int dep_delay = 0;
  int overlap1, overlap2, overlap3, overlap4;
  overlap1 = overlap2 = overlap3 = overlap4 = 0;
  set[1].delay = 0;
  int i;
  for(i = 2; i <= n; i++) {
    dep_delay = 0;
    pipe_delay = 1 - pipe_delay;
    if(i >= 5) {
      if((set[i-5].dest == set[i].src1) ||
	 (set[i-5].dest == set[i].src2)) {
	pipe_delay = 1;
      }
    } // End 5

    if(i >= 4) {
      if((set[i-4].dest == set[i].src1) || 
	 (set[i-4].dest == set[i].src2)) {
	if((overlap1 == 0) && (overlap2 == 0) &&
	   (overlap3 == 0) && (overlap4 == 0)) {
	  overlap4 = 1;
	  if(pipe_delay == 0) dep_delay = 1;
	  else dep_delay = 1;
	  pipe_delay = 1;
	}
	else {
	  overlap4 = 0;
	}
      }
      else { 
	overlap4 = 0;
      }
    } // End 4  

    if(i >= 3) {
      if((set[i-3].dest == set[i].src1) || 
	 (set[i-3].dest == set[i].src2)) {
	if((overlap1 == 0) && (overlap2 == 0) &&
	   (overlap3 == 0)) {
	  overlap3 = 1;
	  if(pipe_delay == 0) dep_delay = 1;
	  else dep_delay = 1;
	  pipe_delay = 1;
	}
	else {
	  overlap3 = 0;
	}
      }
      else { 
	overlap3 = 0;
      }
    } // End 3

    if(i >= 2) {
      if((set[i-2].dest == set[i].src1) || 
	 (set[i-2].dest == set[i].src2)) {
	if((overlap1 == 0) && (overlap2 == 0)) {
	  overlap2 = 1;
	  if(pipe_delay == 0) dep_delay = 1;
	  else dep_delay = 2;
	  pipe_delay = 1;
	}
	else {
	  overlap2 = 0;
	}
      }
      else { 
	overlap2 = 0;
      }
    } // End 2

    if(i >= 1) {
      if((set[i-1].dest == set[i].src1) || 
	 (set[i-1].dest == set[i].src2)) {
	if((overlap1 == 0)) {
	  overlap1 = 1;
	  dep_delay = 2;
	  pipe_delay = 1;
	}
	else {
	  overlap1 = 0;
	}
      }
      else { 
	overlap1 = 0;
      }
    } // End 1

    set[i].delay = set[i-1].delay + dep_delay + pipe_delay;
  } // End for loop
  printf("Total number of cycles: %d\n", set[n].delay + 6);
  printChart();
}

int main() {
  int loop = 1;
  int input = -1;
  while(loop) {
    printf("Pipelined/Superscalar instruction performance\n");
    printf("---------------------------------------------\n");
    printf("1) Enter instructions\n");
    printf("2) Calculate total cycle count on a 6-stage pipelined architecture\n");
    printf("3) Calculate total cycle count on a 6-stage superscalar architecture\n");
    printf("4) Quit\n");
    printf("\n");
    printf("Enter selection: ");
    scanf("%d", &input);
    switch(input) {
    case 1:
      enterInstr();
      break;
    case 2:
      pipeline();
      break;
    case 3:
      superscalar();
      break;
    case 4:
      loop = 0;
      break;
    default:
      printf("Invalid selection.");
    }
    printf("\n\n");
  }
  return 0;
}
