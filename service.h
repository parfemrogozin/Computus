#ifndef SERVICE_H
#define SERVICE_H


typedef struct service
{
  struct tm date;
  char description[29];
} Service;

void set_full_tm(struct tm * date);
void print_service(Service line);
#endif
