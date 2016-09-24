#define _XOPEN_SOURCE 600
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <err.h>
#include <errno.h>


char* build_query(const char *url, size_t *len)
{
  *len = 17+strlen(url);
  char *res = calloc(*len+1,1);
  res = strcat(res,"GET ");
  res = strcat(res,url);
  res = strcat(res," HTTP/1.0\n\r\n\r");
  return res;
}

void get_page(const char *name, const char *url, const char *port)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  int addrinfo_error = getaddrinfo(name, port, &hints, &result);

  if (addrinfo_error != 0)
    errx(EXIT_FAILURE, "Fail getting address for %s on port %s : %s",
         name, port, gai_strerror(addrinfo_error));
  int s = -1;
  for(rp=result;rp;rp=rp->ai_next)
  {
    s = socket(rp->ai_family,rp->ai_socktype,rp->ai_protocol);
    if (s<0)
    {
      fprintf(stderr,"socket fail: %s\n",strerror(errno));
      abort();
    }

    if(connect(s, rp->ai_addr, rp->ai_addrlen) >=0)
    {
      size_t qlen = 0;
      char *msg = build_query(url,&qlen);
      ssize_t status = send(s,msg,strlen(msg),0);

      if (status == -1)
      {
        fprintf(stderr,"send failed :%s\n",strerror(errno));
        abort();
      }
      while (1)
      {
        int bytes;
        char buf[0x10100];
        bytes = recvfrom(s,buf,0x1000,0,rp->ai_addr,&(rp->ai_addrlen));
        if (!bytes)
          break;
        if (bytes == -1)
        {
          fprintf(stderr,"reception pb : %s\n",strerror(errno));
          abort();
        }
        buf[bytes]='\0';
        printf("%s\n",buf);

      }
      free(msg);
    }
  }

  freeaddrinfo(result);
  freeaddrinfo(rp);
}

int main()
{
  size_t x;
  char *w = build_query("http://perdu.com",&x);
  printf("%s",w);
  get_page("perdu.com","http://perdu.com", "80");
  return 0;
}
