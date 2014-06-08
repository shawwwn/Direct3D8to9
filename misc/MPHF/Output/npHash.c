/* table for the mapping for the perfect hash */
#ifndef STANDARD
#include "standard.h"
#endif /* STANDARD */
#ifndef NPHASH
#include "npHash.h"
#endif /* NPHASH */
#ifndef LOOKUPA
#include "lookupa.h"
#endif /* LOOKUPA */

/* small adjustments to _a_ to make values distinct */
ub2 np_table[] = {
162,264,0,65,211,258,3,0,328,154,183,0,0,154,258,234,
28,157,26,28,0,328,152,48,258,6,0,328,26,243,154,101,
65,0,184,238,211,28,110,0,0,157,379,345,131,0,13,260,
28,154,243,158,328,0,65,4,0,211,230,184,28,364,65,154,
162,243,234,65,243,154,72,270,277,124,0,111,345,238,365,364,
62,131,117,194,184,365,327,174,136,0,6,174,36,65,154,65,
243,28,184,0,160,81,93,65,364,0,211,162,0,230,328,6,
374,0,270,238,117,242,157,65,239,378,319,248,258,372,129,101,
};

/* The hash function */
ub4 npHash(val)
ub4 val;
{
  ub4 a, b, rsl;
  val += 0xa4a6104e;
  val ^= (val >> 16);
  val += (val << 8);
  val ^= (val >> 4);
  b = (val >> 1) & 0x7f;
  a = (val + (val << 2)) >> 25;
  rsl = (a^np_table[b]);
  return rsl;
}

