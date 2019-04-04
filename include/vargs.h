#ifndef INCLUDE_VARGS_H_
#define INCLUDE_VARGS_H_

#ifdef USE_BUILDIN_VARGS
// typedef __builtin_va_list va_list;

// #define VA_START(ap, last)         (__builtin_va_start(ap, last))
// #define VA_ARG(ap, type)           (__builtin_va_arg(ap, type))
// #define VA_END(ap)
#else
#define va_list char *

#define VA_START(p, first) (p = (va_list)&first + sizeof(first))
#define VA_ARG(p, next) (*(next *)((p += sizeof(next)) - sizeof(next)))
#define VA_END(p) (p = (va_list)NULL)
#endif

#endif // INCLUDE_VARGS_H_