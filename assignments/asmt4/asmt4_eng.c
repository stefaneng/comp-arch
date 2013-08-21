#include<stdio.h>
#include<stdlib.h>
struct node {
  int virtualpage;
  int pageframe;
} *pagetable = NULL;
typedef struct node pt;

// Global variables
// Memory size, page size, replacement policy, sigma is # of entries in pt
int mem_size, page_size, rpol, sigma;

// Option #1
void setparameters()
{
  printf("Enter main memory size (words): ");
  scanf("%d", &mem_size);
  printf("Enter page size (words/page): ");
  scanf("%d", &page_size);
  printf("Enter replacement policy (0=LRU, 1=FIFO): ");
  scanf("%d", &rpol);
  sigma = mem_size / page_size;
  pagetable = (pt *)malloc(sizeof(pt) * sigma);
  int i;
  for(i = 0; i < sigma; i++) {
    // Fill up -1 for virtualpage
    pagetable[i].virtualpage = -1;
  }
  return;
}

// Option #2
void map_addr()
{
  int va; // Virtual address
  int vp; // Virtual page
  int off; // Offset
  printf("Enter virtual memory address to access: ");
  scanf("%d", &va);
  vp = va / page_size;
  off = va % page_size;
  // CASE 1: Full table=>Fault
  // CASE 2: Find unused entry=>Fault
  // CASE 3: Hit in PT => Translate VA to PA and report
  int i = 0;
  while ((i < sigma) && (pagetable[i].virtualpage != -1)
	 && (pagetable[i].virtualpage != vp)) { 
    i++;
  }

  if (i == sigma) {
    // Replace LRU/FIFO entry in page table
    int k;
    int zeropf = pagetable[0].pageframe;   
    for(k = 0; k <= sigma-2; k++) {
      pagetable[k].pageframe = pagetable[k+1].pageframe;
      pagetable[k].virtualpage = pagetable[k+1].virtualpage;
    }
    pagetable[sigma-1].virtualpage = vp;
    pagetable[sigma-1].pageframe = zeropf;
    printf("Page Fault!\n");
  }
  else if(pagetable[i].virtualpage == -1) {
    pagetable[i].virtualpage = vp;
    pagetable[i].pageframe = i;
    printf("Page Fault!\n");
  }
  else { // pagetable[i].virtualpage == vp
    if(rpol == 0) { // LRU
      int pf = pagetable[i].pageframe;
      int k;
      for(k = i; k <= sigma-2; k++) {
	if(pagetable[k+1].virtualpage == -1)
	  break;
	pagetable[k].pageframe = pagetable[k+1].pageframe;
	pagetable[k].virtualpage = pagetable[k+1].virtualpage;

      }
	pagetable[sigma-1].virtualpage = vp;
	pagetable[sigma-1].pageframe = pf;
      
    }
    printf("Virtual address %d maps to physical address %d\n",
	   va, i*page_size+off);
  }
  return;
}

void print_table()
{
  int i = 0;
  while(i < sigma && pagetable[i].virtualpage != -1) {
    printf("VP %d --> PF %d\n", pagetable[i].virtualpage,
	   pagetable[i].pageframe);
    i++;
  }
  return;
}

int main()
{
  int loop = 1;
  int input = -1;
  while(loop) {
    printf("Virtual memory to Main memory mapping:\n");
    printf("--------------------------------------\n");
    printf("1) Set parameters\n");
    printf("2) Map virtual address\n");
    printf("3) Print page table\n");
    printf("4) Quit\n");
    printf("\n");
    printf("Enter selection: ");
    scanf("%d", &input);
    switch(input) {
    case 1:
      setparameters();
      break;
    case 2:
      map_addr();
      break;
    case 3:
      print_table();
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
