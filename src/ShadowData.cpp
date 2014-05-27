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
		//table.addShadow(24,   18,   SHW_USE_TRANSFORMATION);						// Blasdemaster - blade [conflict]
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
		table.addShadow(72,   40,   SHW_USE_TRANSFORMATION);						// NightElf Rally Point - top [conflict]
		table.addShadow(12,   6,    SHW_USE_TRANSFORMATION);						// NightElf Rally Point - body [conflict]
		/* Heroes */
		table.addShadow(30,   36);													// Demon Hunter - top
		table.addShadow(377,  397);													// Demon Hunter	- body
		table.addShadow(411,  460);													// Demon Hunter	- demon
		table.addShadow(82,   61);													// Keeper of the Grove - top
		table.addShadow(486,  482);													// Keeper of the Grove - body
		table.addShadow(41,   50);													// Warden - top
		table.addShadow(94,   46);													// Warden - cloak
		table.addShadow(86,   46);													// Warden - cloak2
		table.addShadow(610,  521);													// Warden - body
		table.addShadow(60,   66);													// Priest of the Moon - top
		table.addShadow(50,   26);													// Priest of the Moon - bow
		table.addShadow(419,  394);													// Priest of the Moon - body
		/* Units */
		table.addShadow(73,   37);													// Archer - top
		table.addShadow(331,  380);													// Archer - body
		table.addShadow(74,   43);													// Huntress - top
		table.addShadow(49,   23);													// Huntress - glaive
		table.addShadow(490,  457);													// Huntress - body
		table.addShadow(66,   62);													// Dryad - top
		table.addShadow(280,  354);													// Dryad - body [leak]
		//table.addShadow(6,    7,    SHW_USE_TRANSFORMATION);						// Dryad - spear [projectile]
		//table.addShadow(20,   20,   SHW_USE_TRANSFORMATION);						// Dryad - spear top [projectile]
		table.addShadow(62,   52);													// Druid of the Talon - top
		table.addShadow(514,  402);													// Druid of the Talon - body
		table.addShadow(41,   38);													// Druid of the Talon - death top
		table.addShadow(22,   16);													// Druid of the Talon - death top cloak
		table.addShadow(232,  234);													// Druid of the Talon - death body
		table.addShadow(136,  151);													// Druid of the Talon - death body2
		table.addShadow(28,   16);													// Druid of the Claw - top
		table.addShadow(486,  489);													// Druid of the Claw - body
		//table.addShadow(116,  144);												// Druid of the Claw - backpack
		table.addShadow(22,   16);													// Druid of the Claw - bear top
		table.addShadow(493,  428);													// Druid of the Claw - bear body
		table.addShadow(34,   26);													// Mountain Giant - top
		table.addShadow(634,  541);													// Mountain Giant - body
		//table.addShadow(126,  70);												// Mountain Giant - grass
		table.addShadow(27,   22);													// Mountain Giant - weapon1
		table.addShadow(55,   46);													// Mountain Giant - weapon2
		//table.addShadow(12,   8);													// Glaive Thrower - top
		table.addShadow(359,  239);													// Glaive Thrower - body
		//table.addShadow(38,   42,   SHW_USE_TRANSFORMATION);						// Glaive Thrower - glaive [projectile]
		table.addShadow(152,  114);													// Treant - top
		table.addShadow(278,  230);													// Treant - body
		table.addShadow(22,   14);													// Small Ghost - top
		table.addShadow(521,  413);													// Small Ghost - body
		table.addShadow(825,  649);													// Big Ghost - body
		/* Flying Units */
		/*
		table.addShadow(53,   54,   SHW_FLYING_UNIT);								// Chimaera - top [leak]
		table.addShadow(500,  418,  SHW_FLYING_UNIT);								// Chimaera - body [leak]
		table.addShadow(87,   85,   SHW_FLYING_UNIT);								// Hippogryph - top [leak]
		table.addShadow(325,  259,  SHW_FLYING_UNIT);								// Hippogryph - body [leak]
		table.addShadow(81,   81,   SHW_FLYING_UNIT);								// Hippogryph - mounted top wing [leak]
		table.addShadow(90,   48,   SHW_FLYING_UNIT);								// Hippogryph - mounted top archer cloak [leak]
		table.addShadow(246,  253,  SHW_FLYING_UNIT);								// Hippogryph - mounted archer [leak]
		table.addShadow(290,  239,  SHW_FLYING_UNIT);								// Hippogryph - mounted body [leak]
		table.addShadow(76,   80,   SHW_FLYING_UNIT);								// Faerie Dragon - top [leak]
		table.addShadow(264,  260,  SHW_FLYING_UNIT);								// Faerie Dragon - body [leak]
		table.addShadow(42,   32,   SHW_FLYING_UNIT);								// Druid of the Talon - bird top [leak]
		table.addShadow(205,  224,  SHW_FLYING_UNIT);								// Druid of the Talon - bird body [leak]
		*/

		/*
		 *	Netural
		 */
		/* Units */
		table.addShadow(75,   69);													// Sheep

		/*
		 *	Item
		 */
		table.addShadow(178,  116);													// book
	}
}