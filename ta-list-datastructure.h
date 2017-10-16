typedef struct TA_list {
  struct TA *head;
  int highest;
} TA_list;

typedef struct TA {
  const char *first, *last;
  int id;
  double salary;
  struct TA *next;
} TA;
