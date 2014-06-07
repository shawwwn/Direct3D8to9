/* Perfect hash definitions */
#ifndef STANDARD
#include "standard.h"
#endif /* STANDARD */
#ifndef SVHASH
#define SVHASH

extern ub2 tab[];
#define SVHASHLEN 0x80  /* length of hash mapping table */
#define SVHASHNKEYS 432  /* How many keys were hashed */
#define SVHASHRANGE 512  /* Range any input might map to */
#define SVHASHSALT 0xe270ac26 /* internal, initialize normal hash */

ub4 phash(ub4 val);

#endif  /* SVHASH */

