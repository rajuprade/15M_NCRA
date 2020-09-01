#ifndef H_COMHLINK_H
#define H_COMHLINK_H
#define MAXSIZE 2000

typedef struct _msg
{
  int length;
  unsigned char Msg[2000];
}MSG;

extern int open_socket(struct in_addr local_address);
extern void close_socket(int sock);
int dostuff(int sock);
extern int write_socket(int sock );
extern int read_socket(int sock);

#endif


