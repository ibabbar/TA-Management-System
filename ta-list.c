#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ta-list.h"

void init(TA_list *const ta_list_ptr) {  
  ta_list_ptr->head = NULL;
  ta_list_ptr->highest = 0;
}
int hire_TA(TA_list *const ta_list_ptr, const char *const first_name,
            const char *const last_name) {
  TA *hiree = NULL, *current = NULL;
  current = ta_list_ptr->head;
  
  /* check if valid parameters */
  if(last_name == NULL) /* lookup TA */
    return 0;

  /* allocate space for new TA */
  hiree = malloc(sizeof(TA));
  hiree->first = malloc(sizeof(first_name)+1);
  hiree->last = malloc(sizeof(last_name)+1);
  hiree->next = NULL;
  
  /* adding param values to new TA */
  hiree->first = first_name;
  hiree->last = last_name;

  /* checking if current exists */
  if (current == NULL) {
    ta_list_ptr->head = hiree;
  }
  else {
    while (current->next != NULL) {
      current = current->next;
    }
    hiree->id = ta_list_ptr->highest + 1;
    ta_list_ptr->highest = ta_list_ptr->highest + 1;
    current->next = hiree;
  }
  return 1;
}
int num_TAs(TA_list ta_list) {
  TA *current = ta_list.head;
  int counter = 0;
  while (current != NULL) {
    counter++;
    current = current->next;
  }
  return counter;
}
int lookup_TA(TA_list ta_list, const char *const first_name,
              const char *const last_name, int *const id) {
  TA *current = ta_list.head;
  int counter = 0;

   if(id == NULL || last_name == NULL) 
     return 0; 
  
  while (current != NULL) {
    if (strcmp(current->last, last_name) == 0) {
      if (first_name != NULL) {
	if (strcmp(current->first, first_name) == 0) {
	  *id = current->id;
	  return 1;
	}
      }
      else {
	counter++;
      }
    }
    current = current->next;
  }
  if (counter != 0) {
    return counter;
  }
  return -1;
}
int set_salary(TA_list ta_list, int id, double salary) {
  TA *current = ta_list.head;
  
  while (current != NULL) { 
    if (current->id == id) { 
      current->salary = salary;
      return 1;
    } 
    current = current->next;
  }
  return 0;
}
double get_salary(TA_list ta_list, int id) {
  TA *current = ta_list.head;
  
  while (current != NULL) {
    if (current->id == id) {
      return current->salary;
    } 
    current = current->next;
  }
  return 0.0;
}
int fire_TA(TA_list *const ta_list_ptr, int id) {
  TA *current = ta_list_ptr->head, *prev = NULL;
  int fired = 0;

  for (current = ta_list_ptr->head;
       current != NULL; prev = current,
       current = current->next) {
    
    if (current->id == id) {
      if (prev == NULL) {
        ta_list_ptr->head = current->next;
      } else {
        prev->next = current->next;
      }
      
      free(current);
      fired = 1;	
    }
  }
  return fired;
}
void reset(TA_list *const ta_list_ptr) {
  TA *current = ta_list_ptr->head, *prev;
  
  while (current != NULL) {
    prev = current;
    current = current->next;
    free(prev);
  }
  
  ta_list_ptr->head = NULL;
}
