#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "ex2.h"

char **reconstruct_trip(Ticket **tickets, int length)
{
  HashTable *ht = create_hash_table(length);
  char **route = malloc(length * sizeof(char *));

  for (int i = 0; i < length; i++) {
    hash_table_insert(ht, tickets[i]->source, tickets[i]->destination);
    if (strcmp(tickets[i]->source, "NONE") == 0) {
      route[0] = tickets[i]->destination;
    } else if (strcmp(tickets[i]->destination, "NONE") == 0) {
      route[length-2] = tickets[i]->source; 
      route[length-1] = tickets[i]->destination; 
    } 
  }

  int route_mapped = 0;
  int route_place = 0; 

  while (!route_mapped) {
    if (strcmp(hash_table_retrieve(ht, route[route_place]), "NONE") == 0) {
      route_mapped = 1; 
    } else {
      route[route_place+1] = hash_table_retrieve(ht, route[route_place]);
      route_place++; 
    }
  }

  destroy_hash_table(ht); 

  return route;
}

void print_route(char **route, int length)
{
  for (int i = 0; i < length; i++) {
    printf("%s\n", route[i]);
  }
}



#ifndef TESTING
int main(void)
{
  // Short test
  Ticket **tickets = malloc(3 * sizeof(Ticket *));

  Ticket *ticket_1 = malloc(sizeof(Ticket));
  ticket_1->source = "NONE";
  ticket_1->destination = "PDX";
  tickets[0] = ticket_1;

  Ticket *ticket_2 = malloc(sizeof(Ticket));
  ticket_2->source = "PDX";
  ticket_2->destination = "DCA";
  tickets[1] = ticket_2;

  Ticket *ticket_3 = malloc(sizeof(Ticket));
  ticket_3->source = "DCA";
  ticket_3->destination = "NONE";
  tickets[2] = ticket_3;

  print_route(reconstruct_trip(tickets, 3), 3); // PDX, DCA, NONE

  for (int i = 0; i < 3; i++) {
    free(tickets[i]);
  }

  free(tickets);

  return 0;
}
#endif
