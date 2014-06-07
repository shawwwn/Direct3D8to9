/* table for the mapping for the perfect hash */
#ifndef STANDARD
#include "standard.h"
#endif /* STANDARD */
#ifndef SVHASH
#include "svHash.h"
#endif /* PHASH */
#ifndef LOOKUPA
#include "lookupa.h"
#endif /* LOOKUPA */

/* small adjustments to _a_ to make values distinct */
ub2 sv_table[] = {
	36,0,260,264,256,230,36,481,0,131,0,166,324,36,342,445,
	0,430,13,391,468,6,281,162,398,53,409,26,3,0,395,468,
	330,0,405,65,0,0,264,481,468,445,468,0,97,338,10,258,
	62,468,468,472,327,440,66,0,0,24,0,258,103,117,0,16,
	327,346,28,0,238,144,301,449,372,398,218,4,169,0,319,146,
	301,292,249,147,407,0,110,0,325,6,0,309,479,298,55,0,
	275,26,136,6,329,421,281,396,23,426,0,481,13,6,304,112,
	470,246,97,240,195,10,469,65,416,238,243,162,6,97,457,209,
};

/* The hash function */
ub4 svHash(val)
ub4 val;
{
  ub4 a, b, rsl;
  val += 0xe270ac26;
  val ^= (val >> 16);
  val += (val << 8);
  val ^= (val >> 4);
  b = (val >> 13) & 0x7f;
  a = (val + (val << 23)) >> 24;
  rsl = (a^sv_table[b]);
  return rsl;
}

