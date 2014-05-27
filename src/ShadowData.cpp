#include "ShadowVolumeHandler.h"

namespace SV {
	void InitShadowTable(ShadowTable& table)
	{
		/*
		 *	HUM
		 */
		table.addShadow(28,   25);													// Human Rally Point - top
		/* Heroes */
		table.addShadow(21,   26);													// Archmage - top
		table.addShadow(615,  486);													// Archmage - body
		//table.addShadow(64,   64);												// Blood Mage - top [leak]
		table.addShadow(643,  505);													// Blood Mage - body
		table.addShadow(63,   58);													// Paladin - top [leak]
		table.addShadow(510,  382);													// Paladin - body [leak]
		table.addShadow(18,   22);													// Mountain King - top
		table.addShadow(458,  415,  SHW_USE_TRANSFORMATION);						// Mountain King - body
		/* Units */
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
		table.addShadow(20,   12,   SHW_FLYING_UNIT | SHW_USE_TRANSFORMATION);		// Water Element - top
		table.addShadow(206,  134,  SHW_FLYING_UNIT);								// Water Element - upper part
		table.addShadow(72,   38,   SHW_FLYING_UNIT);								// Water Element - body
		/* Flying Units */
		table.addShadow(32,   40,   SHW_FLYING_UNIT);								// Griffin - top [leak]
		table.addShadow(451,  369,  SHW_FLYING_UNIT);								// Griffin - body [leak]
		table.addShadow(21,   22,   SHW_FLYING_UNIT);								// Griffin - hammer
		table.addShadow(104,  77,   SHW_FLYING_UNIT);								// DragonHawk - top [leak]
		table.addShadow(558,  391,  SHW_FLYING_UNIT);								// DragonHawk - body [leak]
		table.addShadow(89,   53,   SHW_FLYING_UNIT);								// Helicopter - top
		table.addShadow(445,  374,  SHW_FLYING_UNIT);								// Helicopter - body (dislay issue)
		

		/*
		 *	ORC
		 */
		/* Heroes */
		table.addShadow(42,   41);													// Blasdemaster - top
		table.addShadow(405,  365);													// Blasdemaster - body
		table.addShadow(24,   18,   SHW_USE_TRANSFORMATION);						// Blasdemaster - blade
		table.addShadow(31,   30);													// Farseer - top
		table.addShadow(673,  518);													// Farseer - body
		table.addShadow(48,   60);													// Shadow Hunter - top
		table.addShadow(444,  362);													// Shadow Hunter - body
		table.addShadow(30,   17,   SHW_USE_TRANSFORMATION);						// Shadow Hunter - spear
		table.addShadow(108,  99);													// Tauren Warchief - top
		table.addShadow(335,  317);													// Tauren Warchief - body
		table.addShadow(24,   26);													// Tauren Warchief - weapon
		/* Units */
		table.addShadow(83,   85);													// Grunt - top
		table.addShadow(411,  320);													// Grunt - body
		table.addShadow(16,   16,   SHW_USE_TRANSFORMATION);						// Grunt - axe
		table.addShadow(58,   46);													// Peon - top
		table.addShadow(220,  212);													// Peon - body
		table.addShadow(26,   26);													// Berserk Troll - top
		table.addShadow(63,   48);													// Berserk Troll - hair
		//table.addShadow(28,   36);												// Berserk Troll - spear [projectile]
		table.addShadow(313,  321);													// Berserk Troll - body
		table.addShadow(90,   106);													// Spirit Walker(transparent) - top
		table.addShadow(42,   24);													// Spirit Walker(transparent) - feet
		table.addShadow(332,  360);													// Spirit Walker(transparent) - body
		table.addShadow(71,   56);													// Wolf - top (display issue)
		table.addShadow(291,  269);													// Wolf - body (display issue)
		//table.addShadow(18,   56,   SHW_USE_TRANSFORMATION);						// Sepent Ward - top [leak]
		//table.addShadow(120,  112);												// Sepent Ward - body (display issue)
		table.addShadow(41,   42);													// Sepent Ward - base
		table.addShadow(47,   46);													// Healing Ward - base
		table.addShadow(42,   40,   SHW_USE_TRANSFORMATION);						// Stunning Ward - body
		table.addShadow(151,  192);													// Eye Ward - eye
		table.addShadow(30,   38,   SHW_USE_TRANSFORMATION);						// Eye Ward - body
		table.addShadow(94,   85);													// Troll Headhunter - top
		//table.addShadow(9,    7);													// Troll Headhunter - spear
		table.addShadow(364,  322);													// Troll Headhunter - body
		table.addShadow(46,   43);													// Shaman - top
		table.addShadow(465,  348);													// Shaman - body
		table.addShadow(69,   42);													// Shaman - lower hem
		table.addShadow(131,  80);													// Voodoo Priest - top
		table.addShadow(314,  288);													// Voodoo Priest - body
		table.addShadow(27,   28);													// Voodoo Priest - staff
		table.addShadow(84,   80);													// Raider - top
		table.addShadow(493,  381);													// Raider - body
		//table.addShadow(90,   106);												// Spirit Walker(normal) - top (display issue)
		//table.addShadow(332,  360);												// Spirit Walker(normal) - body (display issue)
		//table.addShadow(42,   24);												// Spirit Walker(normal) - bristle (display issue)
		table.addShadow(42,   36);													// Kodo Beast - top
		table.addShadow(591,  537);													// Kodo Beast - body
		//table.addShadow(30,   26);												// Kodo Beast - drums
		table.addShadow(50,   35);													// Tauren - top
		table.addShadow(459,  379);													// Tauren - body
		table.addShadow(50,   32,   SHW_USE_TRANSFORMATION);						// Demolisher - top
		table.addShadow(643,  389);													// Demolisher - body
		//table.addShadow(53,   40,   SHW_USE_TRANSFORMATION | SHW_FLYING_UNIT);	// Demolisher - rock [projectile]
		/* Flying Units */
		/*
		table.addShadow(88,   91,   SHW_FLYING_UNIT);								// Wyvern - top
		//table.addShadow(4,    4,    SHW_FLYING_UNIT);								// Wyvern - spear
		table.addShadow(395,  383,  SHW_FLYING_UNIT);								// Wyvern - body
		table.addShadow(29,   22,   SHW_FLYING_UNIT | SHW_USE_TRANSFORMATION);		// Wyvern - spear2
		table.addShadow(37,   34,   SHW_FLYING_UNIT);								// Troll Batrider - top
		table.addShadow(398,  379,  SHW_FLYING_UNIT);								// Troll Batrider - body
		table.addShadow(20,   12,   SHW_FLYING_UNIT | SHW_USE_TRANSFORMATION);		// Troll Batrider - bomb [projectile]
		table.addShadow(108,  73,   SHW_FLYING_UNIT);								// Troll Batrider - wings
		*/


		/*
		 *	NE
		 */
		/* Heroes */
		table.addShadow(30,   36);													// Demon Hunter - top
		table.addShadow(377,  397);													// Demon Hunter	- body


		/*
		 *	Netural
		 */
		/* Units */
		table.addShadow(75,   69);													// Sheep
	}
}