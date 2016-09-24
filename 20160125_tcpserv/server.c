#define _XOPEN_SOURCE 600
#include <string.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <err.h>
#include <errno.h>
#include <unistd.h>

int fdaccept_register(int fd)
{
  static int fdaccept = -1;
  if (fdaccept == -1 && fd != -1)
    fdaccept = fd;
  return fdaccept;
}

void sigint_handler(int sig)
{
  (void)sig;
  int fd = fdaccept_register(-1);
  if (fd!=-1)
    close(fd);
  _exit(0);
}

void bc(int fdin, int fdout)
{
  dup2(fdin, STDIN_FILENO);
  dup2(fdout, STDOUT_FILENO);
  close(fdin);
  close(fdout);
  char *argm[] = {"bc",0};
  execvp("/usr/bin/bc",argm);
}

void echo(int fdin, int fdout)
{
  char buf[0x10100];
  int bytes = 0;
  bytes = read(fdin,buf,0x10010);
  if (bytes <0 && errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK)
  {
    fprintf(stderr,"reception pb : %s\n",strerror(errno));
    abort();
  }
  buf[bytes] = '\0';
  bytes++;
  bytes = write(fdout,buf,bytes);
  if (bytes <0 && errno != EINTR && errno != EAGAIN && errno != EWOULDBLOCK)
  {
    fprintf(stderr,"emition pb : %s\n",strerror(errno));
    abort();
  }
}


void server(const char *portname)
{
  int info_err = 0;
  struct addrinfo hints, *resinfo = NULL;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = 0;
  hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
  info_err = getaddrinfo(NULL, portname, &hints, &resinfo);

  if(info_err != 0)
    errx(EXIT_FAILURE, "Server set-up fails on port %s:%s", portname,
         gai_strerror(info_err));

  for(;resinfo;resinfo=resinfo->ai_next)
  {
    int s=socket(resinfo->ai_family,resinfo->ai_socktype,resinfo->ai_protocol);
    if (s >=0)
    {
      int reuse_err;
      int reuse = 1;
      reuse_err = setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
                             &reuse,sizeof(reuse));
      if (reuse_err == -1)
        err(EXIT_FAILURE, "Fail to set socket options");
      fdaccept_register(s);
      if (bind(s, resinfo->ai_addr, resinfo->ai_addrlen) == 0)
      {
        if (listen(s,3) < 0)
          err(EXIT_FAILURE, "Listening problem: %s",strerror(errno));
        for (;;)
        {
          int fdcnx = accept(s, NULL,NULL);
          if (fdcnx < 0 && errno != EAGAIN && errno != EWOULDBLOCK &&
              errno != EINTR)
            err(EXIT_FAILURE, "Failed to accept connexion: %s",strerror(errno));
          if (fdcnx >= 0)
          {
            pid_t pid = fork();
            if (pid <0)
              err(EXIT_FAILURE, "Failed to create child");
            if (pid != 0)
            {
              close(fdcnx);
              continue;
            }
            else
            {
              close(s);
              bc(fdcnx,fdcnx);
              close(fdcnx);
              exit(0);
            }
          }
        }
        freeaddrinfo(resinfo);
      }
    }
    else
    {
      fprintf(stderr,"socket fail: %s\n",strerror(errno));
      abort();
    }
  }
  errx(EXIT_FAILURE, "getaddrinfo fail\n");
}


int main(int argc, char* argv[])
{
  if (argc != 2)
    err(EXIT_FAILURE, "Please, specify a port number");
//SIGINT
  struct sigaction sigint;
  memset(&sigint, 0,sizeof(struct sigaction));
  sigint.sa_handler = sigint_handler;
  sigfillset(&sigint.sa_mask);
  sigint.sa_flags = SA_NODEFER;
  if (sigaction(SIGINT, &sigint, NULL) == -1)
    err(EXIT_FAILURE, "can't change SIGINT behavior");

//SIGCHLD
  struct sigaction sigchld;
  memset(&sigchld, 0,sizeof(struct sigaction));
  sigchld.sa_handler = SIG_DFL;
  sigemptyset(&sigchld.sa_mask);
  sigchld.sa_flags = SA_NOCLDSTOP | SA_NOCLDWAIT;
  if (sigaction(SIGCHLD, &sigchld, NULL) == -1)
    err(EXIT_FAILURE, "can't change SIGCHLD behavior");

  server(argv[1]);
  return 1;
}
