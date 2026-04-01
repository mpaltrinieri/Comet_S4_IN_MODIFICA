#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#undef isdigit
#define isdigit(c)		(('0' <= (c)) && ((c) <= '9'))

#undef isxdigit
#define isxdigit(c)     (('0' <= (c)) && ((c) <= '9') \
					  || ('a' <= (c)) && ((c) <= 'f') \
		              || ('A' <= (c)) && ((c) <= 'F'))

#undef isspace
#define isspace(c)      (((c) == ' ') || ((c) == '\t') || ((c) == '\n') \
		              || ((c) == '\v') || ((c) == '\f') || ((c) == '\r'))

#undef isupper
#define isupper(c)      (('A' <= c) && (c <= 'Z'))

#undef islower
#define islower(c)      (('a' <= c) && (c <= 'z'))

#undef isalpha
#define isalpha(c)      (islower(c) || isupper(c))

#undef isalnum
#define isalnum(c)		(isdigit(c) || isalpha(c))

#undef sscanf
#define sscanf _sscanf
int _sscanf(const char *str, const char *fmt, ...);

#undef strtoll
#define strtoll    _strtoll
long long int _strtoll(const char* str, char** endptr, int base);

#undef strtoull
#define strtoull    _strtoull
unsigned long long int _strtoull(const char* str, char** endptr, int base);

#endif // UTILS_H_INCLUDED
