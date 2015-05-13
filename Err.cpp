#include "../include/Err.h"

Err::Err()
{
    //ctor
}

Err::~Err()
{
    //dtor
}
void Err::err_doit(int errnoFlag, int error, const char * fmt, va_list ap)
{
    char Buff[MAXLINE];
    vsnprintf(Buff, MAXLINE - 1, fmt, ap);
    if(errnoFlag)
    {
        snprintf(Buff + strlen(Buff), MAXLINE - strlen(Buff) - 1, ": %s", strerror(error));
        strcat(Buff, "\n");
        fflush(stdout);
        fputs(Buff, stderr);
        fflush(NULL);
    }
}
void Err::ret(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
}
void Err::sys(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}

void Err::cont(int error, const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
}
void Err::Exit(int error,  const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, error, fmt, ap);
    va_end(ap);
    exit(1);
}

void Err::quit(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0,0, fmt, ap);
    va_end(ap);
}

void Err::dump(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    abort();
    exit(1);
}

void Err::msg(const char * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    err_doit(0,0, fmt, ap);
    va_end(ap);
}
