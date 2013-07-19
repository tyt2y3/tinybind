#ifndef WIN32COMPATIBLE_TINYSQL
#define WIN32COMPATIBLE_TINYSQL

#ifndef WIN32 
  #define stricmp strcasecmp 
  #define strnicmp strncasecmp 
#endif

#endif
