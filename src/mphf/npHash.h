/* Perfect hash definitions */
#ifndef STANDARD
#include "standard.h"
#endif /* STANDARD */
#ifndef NPHASH
#define NPHASH

extern ub2 np_table[];
#define NPHASHLEN 0x80  /* length of hash mapping table */
#define NPHASHNKEYS 301  /* How many keys were hashed */
#define NPHASHRANGE 512  /* Range any input might map to */
#define NPHASHSALT 0xa4a6104e /* internal, initialize normal hash */

ub4 npHash(ub4 val);

#endif  /* NPHASH */

