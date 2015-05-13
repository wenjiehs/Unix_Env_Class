#ifndef ERR_H
#define ERR_H
#include <errno.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

class Err
{
    public:
        Err();
        virtual ~Err();

        static void ret(const char * fmt, ...);
        static void sys(const char * fmt, ...);
        static void dump(const char * fmt, ...);
        static void Exit(int error, const char * fmt, ...);
        static void cont(int error, const char * fmt, ...);
        static void quit(const char * fmt, ...);
        static void msg(const char * fmt, ...);
    protected:
        static void err_doit(int, int, const char *, va_list);
    private:
        static const int MAXLINE = 4096;
};

#endif // ERR_H
