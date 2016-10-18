/*
 * Kazuya Sakai, sakai@buckeyemail.osu.edu
 * June 15, 2012
 */

#ifndef R_TABLE_H
#define R_TABLE_H

#define MAX_R_ENTRY 10

extern int* r_table[MAX_R_ENTRY];

void init_r_table();
int add_entry(int s, int r);
int get_receiver(int s);
int get_sender(int r);
void print_r_table();
int get_number(char *p);

#endif   /* ROUTING_TABLE_H   */