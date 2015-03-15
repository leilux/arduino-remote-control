#ifndef PARSE_URI
#define PARSE_URI

#include <stdio.h>
#include <string.h>

#define MAXLINE 1024
void get_url_from_request(char *request_line, char *url);
void parse_url(char *uri, char *path, char *cgiargs);


void get_url_from_request(char *request_line, char *url) 
{
  char buf[MAXLINE], method[5], http_version[10];
  char path[MAXLINE], cgi_args[MAXLINE];
  
  sscanf(request_line, "%s %s %s", method, url, http_version);
}


void parse_url(char *url, char *path, char *cgi_args) 
{
  char *ptr;

  ptr = strchr(url, '?');
  if (ptr) {
    strcpy(cgi_args, ptr+1);
    *ptr = '\0';
  }
  else {
    strcpy(cgi_args, "");
  }
  strcpy(path, url+1);
}


void parse_query(char *cgi_args) 
{
}

#endif
