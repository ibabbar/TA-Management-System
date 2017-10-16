#include <stdio.h> 
#include <stdlib.h> 
#include "ta-list.h" 

static void test1(void);  
static void test2(void); 
static void test3(void);  
static void test4(void); 
static void test5(void); 

/* testing hire_TA, num_TAs */ 
  static void test1(void) { 
    TA_list our_TAs; 
    
    init(&our_TAs); 
    
    hire_TA(&our_TAs, "Karen", "Kangaroo"); 
    hire_TA(&our_TAs, "Lauren", "Llama"); 
    hire_TA(&our_TAs, "Quigley", "Quokka"); 
    hire_TA(&our_TAs, "Nestor", "Numbat"); 
    hire_TA(&our_TAs, "Peter", "Platypus"); 
    
    if (num_TAs(our_TAs) != 5) { 
      printf("Bug found- num_TAs() was wrong!\n"); 
      exit(FOUND_BUG); 
    } 
  } 

/* testing hire_TA, lookup_TAs */ 
static void test2(void) { 
  TA_list our_TAs; 
  int id= -1; 
  
  init(&our_TAs); 
  
    hire_TA(&our_TAs, "Karen", "Kangaroo"); 
    hire_TA(&our_TAs, "Lauren", "Llama"); 
    hire_TA(&our_TAs, "Quigley", "Quokka"); 
    hire_TA(&our_TAs, "Nestor", "Numbat"); 
    hire_TA(&our_TAs, "Peter", "Platypus"); 
    
    if (lookup_TA(our_TAs, "Lauren", "Llama", &id) != 1) { 
      printf("Bug found- lookup_TA(\"Lauren\", \"Llama\") was wrong!\n"); 
      exit(FOUND_BUG); 
    } 
} 

/* testing hire_TA, set_salary, get_salary */ 
static void test3(void) { 
  TA_list our_TAs; 
  int i;
  double x;
  
  init(&our_TAs);  
  
  hire_TA(&our_TAs, "Karen", "Kangaroo"); 
  hire_TA(&our_TAs, "Lauren", "Llama"); 
  hire_TA(&our_TAs, "Quigley", "Quokka"); 
  hire_TA(&our_TAs, "Nestor", "Numbat"); 
  hire_TA(&our_TAs, "Peter", "Platypus"); 
  
  /* check default salary  */ 
  if(get_salary(our_TAs, 0) != 0.0) { 
    printf("Default value not 0.0. It is %f\n", get_salary(our_TAs, 0));  
      exit(FOUND_BUG); 
  }
  /* test range of salaries */
  for (x = 0.0; x < 122.00; x = x + 11.10) {
    for (i = 0; i < 5; ++i) {
      
      /* set salary */ 
      if (!set_salary(our_TAs, i, x)) {
	printf("Could not find TA"); 
	exit(FOUND_BUG); 
      }
      
      /* check if salary works using get_salary */ 
      if(get_salary(our_TAs, i) != x) { 
	printf("Set_salary not setting correctly\nSalary:%f at index %d\n",get_salary(our_TAs, i), i); 
	exit(FOUND_BUG); 	
      } 
    }
  }
} 

/* testing hire_TA, fire_TA */ 
static void test4(void) { 
  TA_list our_TAs; 
  int id= 0; 
  
  init(&our_TAs);  
  
  hire_TA(&our_TAs, "Karen", "Kangaroo"); 
  hire_TA(&our_TAs, "Lauren", "Llama"); 
  hire_TA(&our_TAs, "Quigley", "Quokka");

  /* get id */
  lookup_TA(our_TAs, "Quigley", "Quokka", &id);
  
  /* fire the TA */ 
  fire_TA(&our_TAs, id);
  
  /* check num_TAs */ 
  if (num_TAs(our_TAs) != 2) { 
    printf("Bug found- num_TAs() was wrong by fire_TA! It is %d\n", num_TAs(our_TAs));  
    exit(FOUND_BUG); 
  } 
  
  /* try lookup_TA on ANYTHING */ 
  if (lookup_TA(our_TAs, "Karen", "Kangaroo", &id) == -1) { 
    printf("Bug found- lookup_TA(\"Karen\", \"Kangaroo\") was deleted!\n");  
    exit(FOUND_BUG); 
  }
  if (lookup_TA(our_TAs, "Lauren", "Llama", &id) == -1) { 
    printf("Bug found- lookup_TA(\"Lauren\", \"Llama\") was deleted!\n");  
    exit(FOUND_BUG); 
  }
  
  /* try lookup_TA on deleted value */
  if (lookup_TA(our_TAs, "Quigley", "Quokka", &id) != -1) {
    printf("Bug found- lookup_TA(\"Quigley\", \"Quokka\") wasn't deleted!\n"); 
    exit(FOUND_BUG); 
  }
  
  hire_TA(&our_TAs, "Nestor", "Numbat"); 
  hire_TA(&our_TAs, "Peter", "Platypus");

    /* get id */
  lookup_TA(our_TAs, "Nestor", "Numbat", &id);
  
  /* fire the TA */ 
  fire_TA(&our_TAs, id);

    /* check num_TAs */ 
  if (num_TAs(our_TAs) != 3) { 
    printf("Bug found- num_TAs() was wrong by fire_TA! It is %d\n", num_TAs(our_TAs)); 
    exit(FOUND_BUG);  
  } 
  
  /* try lookup_TA on not deleted*/ 
  if (lookup_TA(our_TAs, "Karen", "Kangaroo", &id) == -1) { 
    printf("Bug found- lookup_TA(\"Karen\", \"Kangaroo\") was deleted!\n"); 
    exit(FOUND_BUG); 
  }
  if (lookup_TA(our_TAs, "Lauren", "Llama", &id) == -1) { 
    printf("Bug found- lookup_TA(\"Lauren\", \"Llama\") was deleted!\n");  
    exit(FOUND_BUG); 
  }  if (lookup_TA(our_TAs, "Peter", "Platypus", &id) == -1) { 
    printf("Bug found- lookup_TA(\"Peter\", \"Platypus\") was deleted!\n"); 
    exit(FOUND_BUG);  
  }
  
  /* try lookup_TA on deleted */ 
  if (lookup_TA(our_TAs, "Nestor", "Numbat", &id) != -1) { 
    printf("Bug found- lookup_TA(\"Nestor\", \"Numbat\") wasn't deleted!\n");  
    exit(FOUND_BUG); 
  }
} 
/* testing hire_TA, reset */ 
 static void test5(void) { 
   TA_list our_TAs; 
   int id = 0; 
   
   init(&our_TAs);  
   
   hire_TA(&our_TAs, "Karen", "Kangaroo"); 
   hire_TA(&our_TAs, "Lauren", "Llama"); 
   hire_TA(&our_TAs, "Quigley", "Quokka"); 
   hire_TA(&our_TAs, "Nestor", "Numbat"); 
   hire_TA(&our_TAs, "Peter", "Platypus"); 
   
   reset(&our_TAs); 
   
   /* check num_TAs */ 
   if (num_TAs(our_TAs) != 0) { 
     printf("Bug found- num_TAs() was wrong! There are still %d TAs\n", num_TAs(our_TAs));
    exit(FOUND_BUG);       
   } 
   
   /* try lookup_TA on ANYTHING */ 
   if (lookup_TA(our_TAs, "Karen", "Kangaroo", &id) != -1) { 
     printf("Bug found- lookup_TA(\"Karen\", \"Kangaroo\") wasn't deleted!\n"); 
     exit(FOUND_BUG); 
   } 
   if (lookup_TA(our_TAs, "Quigley", "Quokka", &id) != -1) { 
     printf("Bug found- lookup_TA(\"Quigley\", \"Quokka\") wasn't deleted!\n"); 
     exit(FOUND_BUG); 
   } 
   if (lookup_TA(our_TAs, "Nestor", "Numbat", &id) != -1) { 
     printf("Bug found- lookup_TA(\"Nestor\", \"Numbat\") wasn't deleted!\n"); 
     exit(FOUND_BUG); 
   } 
   if (lookup_TA(our_TAs, "Peter", "Platypus", &id) != -1) { 
     printf("Bug found- lookup_TA(\"Peter\", \"Platypus\") wasn't deleted!\n");
     exit(FOUND_BUG); 
   } 
   if (lookup_TA(our_TAs, "Lauren", "Llama", &id) != -1) { 
     printf("Bug found- lookup_TA(\"Lauren\", \"Llama\") wasn't deleted!\n"); 
     exit(FOUND_BUG); 
   } 
 } 

int main() { 
  test1(); 
  test2(); 
  test3(); 
  test4(); 
  test5(); 
  
  printf("No bugs were detected!\n"); 
  
  return CORRECT; 
} 
 
