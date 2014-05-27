#include "ShadowVolumeHandler.h"

namespace SV {
	void InitShadowTable(ShadowTable& table)
	{
		/*
		 *	HUM
		 */
		table.addShadow(28,   25);													// Human Rally Point - top
		table.addShadow(46,   60);													// Peasant - body
		table.addShadow(302,  270);													// Peasant - top
		table.addShadow(120,  48,  SHW_USE_TRANSFORMATION);							// Peasant - lumber
		table.addShadow(36,   35);													// Peasant - gold
		table.addShadow(280,  278);													// Militia - body
		table.addShadow(138,  107);													// Spellbreaker - top
		table.addShadow(310,  296);													// Spellbreaker - body
		table.addShadow(42,   25);													// Spellbreaker - sword
		table.addShadow(52,   35);													// Footman - top
		table.addShadow(447,  288);													// Footman - body
		table.addShadow(169,  115);													// Riflemane - top
		table.addShadow(342,  299);													// Riflemane - body
		table.addShadow(88,   61);													// Knight - top
		table.addShadow(541,  428);													// Knight - body
		table.addShadow(96,   99);													// Priest - top
		table.addShadow(301,  300);													// Priest - body
		table.addShadow(10,   9);													// Priest - staff
		table.addShadow(107,  58);													// Mage - top
		table.addShadow(407,  369);													// Mage - body
		table.addShadow(40,   29);													// Motar Team - top
		table.addShadow(490,  481);													// Motar Team - body
		//table.addShadow(17,   22,  SHW_USE_TRANSFORMATION);						// Motar Team - scope
		table.addShadow(52,   44);													// Motar Team - cannon
		table.addShadow(22,   18);													// Tank - top
		table.addShadow(778,  512);													// Tank - body
		//table.addShadow(78,   118, SHW_USE_TRANSFORMATION);						// Tank - eagle head
		table.addShadow(21,   26);													// Archmage - top
		table.addShadow(615,  486);													// Archmage - body
		//table.addShadow(64,   64);												// Blood Mage - top [leak]
		table.addShadow(643,  505);													// Blood Mage - body
		table.addShadow(63,   58);													// Paladin - top [leak]
		table.addShadow(510,  382);													// Paladin - body [leak]
		table.addShadow(18,   22);													// Mountain King - top
		table.addShadow(458,  415,  SHW_USE_TRANSFORMATION);						// Mountain King - body

		table.addShadow(20,   12);													// Water Element - top
		table.addShadow(206,  134);													// Water Element - upper part
		table.addShadow(72,   38);													// Water Element - body

		/* Buildings */
		/*
		table.addShadow(99,   46,   SHW_USE_TRANSFORMATION);						// Barracks - top
		table.addShadow(387,  209,  SHW_USE_TRANSFORMATION);						// Barracks - body
		table.addShadow(27,   15,   SHW_USE_TRANSFORMATION);						// Tower - top
		table.addShadow(251,  149,  SHW_USE_TRANSFORMATION);						// Tower - body
		*/

		/* Flying Units */
		
		table.addShadow(32,   40,   SHW_FLYING_UNIT);								// Griffin - top [leak]
		table.addShadow(451,  369,  SHW_FLYING_UNIT);								// Griffin - body [leak]
		table.addShadow(21,   22,   SHW_FLYING_UNIT);								// Griffin - hammer
		table.addShadow(104,  77,   SHW_FLYING_UNIT);								// DragonHawk - top [leak]
		table.addShadow(558,  391,  SHW_FLYING_UNIT);								// DragonHawk - body [leak]
		table.addShadow(89,   53,   SHW_FLYING_UNIT);								// Helicopter - top
		table.addShadow(445,  374,  SHW_FLYING_UNIT);								// Helicopter - body (dislay issue)
		

		/*
		 *	NE
		 */
		table.addShadow(30,   36);													// Demon Hunter - top
		table.addShadow(377,  397);													// Demon Hunter	- body

		/*
		 *	Netural
		 */
		/* Buildings */
		//table.addShadow(271,  239,  SHW_USE_TRANSFORMATION);						// Golb Mine - mine
	}
}