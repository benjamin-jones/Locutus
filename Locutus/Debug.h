#ifndef DEBUG_H
#define DEBUG_H

#include <stdio.h>
#include <string.h>

#ifndef _DEBUG
#define debug(M,...)
#else
#define debug(M,...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

#endif