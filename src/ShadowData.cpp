#include "ShadowVolumeHandler.h"

namespace SV {
	void InitShadowTable(ShadowTable& table)
	{
		#pragma region Human
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
		table.addShadow(42,   25,  SHW_USE_TRANSFORMATION);							// Spellbreaker - sword
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
		table.addShadow(22,   18,   SHW_USE_TRANSFORMATION);						// Tank - top
		table.addShadow(778,  512);													// Tank - body
		//table.addShadow(78,   118, SHW_USE_TRANSFORMATION);						// Tank - eagle head
		table.addShadow(20,   12,   SHW_FLYING_UNIT | SHW_USE_TRANSFORMATION);		// Water Element - top
		table.addShadow(206,  134,  SHW_FLYING_UNIT);								// Water Element - upper part
		table.addShadow(72,   38,   SHW_FLYING_UNIT);								// Water Element - body
		/* Flying Units */
		/*
		table.addShadow(32,   40,   SHW_FLYING_UNIT);								// Griffin - top [leak]
		table.addShadow(451,  369,  SHW_FLYING_UNIT);								// Griffin - body [leak]
		table.addShadow(21,   22,   SHW_FLYING_UNIT);								// Griffin - hammer
		table.addShadow(104,  77,   SHW_FLYING_UNIT);								// DragonHawk - top [leak]
		table.addShadow(558,  391,  SHW_FLYING_UNIT);								// DragonHawk - body [leak]
		table.addShadow(89,   53,   SHW_FLYING_UNIT);								// Helicopter - top
		table.addShadow(445,  374,  SHW_FLYING_UNIT);								// Helicopter - body (dislay issue)
		*/
		#pragma endregion

		#pragma region Orc
		//table.addShadow(8,    6);													// Orc Rally Point - top [conflict]
		table.addShadow(32,   18);													// Orc Rally Point - body
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
		#pragma endregion

		#pragma region Night Elf
		table.addShadow(72,   40,   SHW_USE_TRANSFORMATION);						// NightElf Rally Point - top
		table.addShadow(12,   6,    SHW_USE_TRANSFORMATION);						// NightElf Rally Point - body
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
		/* New Heroes */
		/*
		table.addShadow(1484, 1322);												// New Warden - wraps
		table.addShadow(150,  202);													// New Warden - cloak
		table.addShadow(123,  140);													// New Warden - helmet
		table.addShadow(122,  184);													// New Warden - leg
		table.addShadow(158,  228);													// New Warden - feet
		table.addShadow(78,   108);													// New Warden - hand
		table.addShadow(424,  528);													// New Warden - body
		table.addShadow(2244, 748);													// New Tyrand - tiger
		table.addShadow(1793, 590);													// New Tyrand - rider
		table.addShadow(223,  76);													// New Tyrand - cloak
		*/
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
		table.addShadow(28,   16,   SHW_USE_TRANSFORMATION);						// Druid of the Claw - top
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
		/* New Units */
		table.addShadow(731,  1038);												// New Mountain Giant - top

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
		#pragma endregion

		#pragma region Undead
		table.addShadow(76,   42,   SHW_USE_TRANSFORMATION);						// Undead Rally Point
		/* Heroes */
		table.addShadow(82,   39);													// Death Knight - top
		table.addShadow(597,  556);													// Death Knight - body
		table.addShadow(110,  94);													// Cryptlord - top
		table.addShadow(513,  587);													// Cryptlord - body
		table.addShadow(128,  79);													// Lich - top
		table.addShadow(562,  418);													// Lich - body
		table.addShadow(99,   68);													// Dreadlord - top
		table.addShadow(432,  442);													// Dreadlord - body
		/* Units */
		table.addShadow(243,  358);													// Inferno - body
		table.addShadow(28,   32);													// Crypt Fiend - top
		table.addShadow(455,  460);													// Crypt Fiend - body
		table.addShadow(72,   42);													// Necromancer - top
		table.addShadow(500,  498);													// Necromancer - body
		table.addShadow(49,   28,   SHW_FLYING_UNIT);								// Witch - top
		table.addShadow(308,  272,  SHW_FLYING_UNIT);								// Witch - body
		table.addShadow(48,   32);													// Meat Wagon - top
		table.addShadow(695,  490);													// Meat Wagon - body
		table.addShadow(31,   34);													// Abomination - top
		table.addShadow(379,  441);													// Abomination - body
		table.addShadow(65,   63,   SHW_USE_TRANSFORMATION);						// Gargoyle ground - top
		table.addShadow(343,  276,  SHW_USE_TRANSFORMATION);						// Gargoyle ground - body
		table.addShadow(51,   62,   SHW_USE_TRANSFORMATION);						// Obsidian Statue - top
		table.addShadow(415,  546,  SHW_USE_TRANSFORMATION);						// Obsidian Statue - body
		table.addShadow(109,  62,   SHW_USE_TRANSFORMATION);						// Obsidian Statue - base
		table.addShadow(31,   26);													// Ghoul - top
		table.addShadow(504,  437);													// Ghoul - body
		table.addShadow(58,   37);													// Acolyte - top
		table.addShadow(365,  316);													// Acolyte - body
		table.addShadow(248,  259,  SHW_FLYING_UNIT);								// Shadow - body
		table.addShadow(42,   37,   SHW_FLYING_UNIT);								// Shadow - top
		table.addShadow(24,   32);													// Beetle - top
		table.addShadow(168,  200);													// Beetle - top
		table.addShadow(8,    9,    SHW_USE_TRANSFORMATION);						// Skeleton - top
		table.addShadow(327,  325);													// Skeleton - body
		table.addShadow(36,   40);													// Skeleton Mage - top
		table.addShadow(363,  321);													// Skeleton Mage - body
		/* Flying Unit */
		/*
		table.addShadow(102,  83,   SHW_FLYING_UNIT);								// Gargoyle fly - top
		table.addShadow(485,  385,  SHW_FLYING_UNIT);								// Gargoyle fly - body
		table.addShadow(53,   64,   SHW_FLYING_UNIT);								// Destroyer - top
		table.addShadow(500,  549,  SHW_FLYING_UNIT);								// Destroyer - body
		table.addShadow(89,   56,   SHW_FLYING_UNIT);								// Frost Wyrm - top
		table.addShadow(125,  110,  SHW_FLYING_UNIT);								// Frost Wyrm - rib
		table.addShadow(358,  279,  SHW_FLYING_UNIT);								// Frost Wyrm - body
		*/
		#pragma endregion

		#pragma region Naga
		/* Heroes */
		table.addShadow(90,   83);													// Naga Sea Witch - top
		table.addShadow(1073, 760);													// Naga Sea Witch - body
		//table.addShadow(90,   52);												// Enchantress - top (performance)
		//table.addShadow(52,   190);												// Enchantress - wraps (performance)
		//table.addShadow(755,  3880);												// Enchantress - body (performance)
		table.addShadow(2046, 2128);												// Murloc Hero - body
		table.addShadow(252,  408);													// Tidal Baron - top
		table.addShadow(948,  808);													// Tidal Baron - body
		//table.addShadow(369,  190);												// Tidal Baron - fin
		table.addShadow(214,  356,  SHW_USE_TRANSFORMATION);						// Tidal Baron - weapon
		//table.addShadow(326,  381);												// Illidan - wing (performance)
		//table.addShadow(534,  823);												// Illidan - hand (performance)
		//table.addShadow(574,  724);												// Illidan - face (performance)
		//table.addShadow(1221, 1513);												// Illidan - lower body (performance)
		//table.addShadow(1566, 2078);												// Illidan - upper body (performance)
		//table.addShadow(538,  740,  SHW_USE_TRANSFORMATION);						// Illidan - weapon (performance)
		/* Units */
		table.addShadow(77,   80);													// Couatl - top
		table.addShadow(90,   52);													// Naga Siren - top
		table.addShadow(543,  552);													// Naga Siren - body
		table.addShadow(95,   74);													// Snap Dragon - top
		table.addShadow(361,  378);													// Snap Dragon - body
		table.addShadow(41,   46);													// Naga Myrmidon - top
		table.addShadow(395,  425);													// Naga Myrmidon - body
		//table.addShadow(39,   36);												// Naga Myrmidon - spikes
		table.addShadow(92,   56);													// Naga Myrmidon - sword
		table.addShadow(36,   34);													// Naga Loyal Guard - top
		table.addShadow(412,  453);													// Naga Loyal Guard - body
		//table.addShadow(94,   58);												// Naga Loyal Guard - spikes
		table.addShadow(90,   83);													// Murloc Slave - top
		table.addShadow(238,  207);													// Murloc Slave - body
		table.addShadow(21,   7);													// Murloc Catapult - basket
		table.addShadow(273,  210);													// Murloc Catapult - body
		//table.addShadow(68,   88);												// Hunting Shark - body (performance)
		//table.addShadow(35,   64);												// Hunting Shark - legs (performance)
		//table.addShadow(40,   90);												// Hunting Shark - arms (performance)
		//table.addShadow(182,  222);												// Hunting Shark - head (performance)
		#pragma endregion

		#pragma region IceTroll
		/* Heroes */
		table.addShadow(1141, 1460);												// Shadow Warlock - top
		table.addShadow(69,   118,  SHW_USE_TRANSFORMATION);						// Shadow Warlock - top rod
		table.addShadow(58,   57,   SHW_USE_TRANSFORMATION);						// Shadow Warlock - top skull
		table.addShadow(473,  565);													// Bloodrager - top
		table.addShadow(154,  110,  SHW_USE_TRANSFORMATION);						// Bloodrager - weapon
		table.addShadow(506,  469);													// Bloodrager - body
		table.addShadow(59,   34);													// Voodoo Priest - top
		table.addShadow(390,  321);													// Voodoo Priest - body
		table.addShadow(197,  209,  SHW_USE_TRANSFORMATION);						// Voodoo Priest - weapon
		/* Units */
		table.addShadow(542,  418);													// Voodoo Doll - top
		table.addShadow(20,   12);													// Gold Digger - hair
		table.addShadow(176,  156);													// Gold Digger - body
		table.addShadow(156,  166);													// Gold Digger - axe
		table.addShadow(18,   24);													// Voodoo Wishman - top
		table.addShadow(240,  217,  SHW_USE_TRANSFORMATION);						// Voodoo Wishman - body
		table.addShadow(328,  261,  SHW_USE_TRANSFORMATION);						// Voodoo Wishman - head
		//table.addShadow(49,   40,   SHW_USE_TRANSFORMATION);						// Totemist - top
		//table.addShadow(40,   25,   SHW_USE_TRANSFORMATION);						// Totemist - top hair
		//table.addShadow(57,   24,   SHW_USE_TRANSFORMATION);						// Totemist - top gen
		//table.addShadow(59,   72,   SHW_USE_TRANSFORMATION);						// Totemist - top rod
		//table.addShadow(42,   30,   SHW_USE_TRANSFORMATION);						// Totemist - face
		//table.addShadow(435,  262,  SHW_USE_TRANSFORMATION);						// Totemist - upper body
		//table.addShadow(36,   32,   SHW_USE_TRANSFORMATION);						// Totemist - skirt edge
		//table.addShadow(30,   32,   SHW_USE_TRANSFORMATION);						// Totemist - skirt
		//table.addShadow(59,   46,   SHW_USE_TRANSFORMATION);						// Totemist - skull
		table.addShadow(18,   14);													// Catapult - top
		table.addShadow(368,  271);													// Catapult - body
		table.addShadow(22,   32,   SHW_USE_TRANSFORMATION);						// IceTroll Warrior - left axe
		table.addShadow(21,   32,   SHW_USE_TRANSFORMATION);						// IceTroll Warrior - right axe
		table.addShadow(23,   30,   SHW_USE_TRANSFORMATION);						// Mocking Totem
		table.addShadow(246,  282,  SHW_USE_TRANSFORMATION);						// Healing Ward
		table.addShadow(622,  562);													// Imp - body
		table.addShadow(66,   32);													// Imp - hair
		table.addShadow(243,  282,  SHW_USE_TRANSFORMATION);						// Statsis Trap
		#pragma endregion

		#pragma region Neutral
		/* Heroes */
		table.addShadow(26,   28);													// Tinker - top
		table.addShadow(1080, 681);													// Tinker - body
		table.addShadow(38,   28);													// Alchemist - top
		table.addShadow(763,  606);													// Alchemist - body
		table.addShadow(60,   60);													// Alchemist - tusks
		table.addShadow(33,   39);													// BeastMaster - top
		table.addShadow(650,  563);													// BeastMaster - body
		table.addShadow(9,    4);													// Dark Ranger - top
		table.addShadow(505,  447);													// Dark Ranger - body
		table.addShadow(56,   40);													// Firelord - top
		table.addShadow(318,  308);													// Firelord - body
		table.addShadow(260,  256);													// Firelord - armor
		table.addShadow(12,   10);													// Brewmaster - top
		table.addShadow(568,  481);													// Brewmaster - body
		table.addShadow(72,   52);													// Brewmaster - barrel
		table.addShadow(451,  413);													// Earth - body
		table.addShadow(93,   62);													// Earth - stone
		table.addShadow(505,  429);													// Fire - body
		table.addShadow(48,   36);													// Fire - blades
		table.addShadow(528,  439);													// Air - body
		table.addShadow(20,   20);													// Pitlord - top
		table.addShadow(702,  635);													// Pitlord - body
		/* Small Animals */
		table.addShadow(75,   69);													// Sheep
		table.addShadow(209,  212);													// Deer
		table.addShadow(139,  98);													// Chicken
		table.addShadow(157,  105);													// Fog
		table.addShadow(91,   70);													// Pig
		table.addShadow(160,  107);													// Rabbit
		table.addShadow(291,  212);													// Racoon
		table.addShadow(353,  374);													// Crab
		table.addShadow(356,  374);													// Helmet Crab
		table.addShadow(251,  194);													// Lizard
		table.addShadow(132,  96);													// Sandworm
		table.addShadow(155,  168);													// Wolf
		table.addShadow(96,   72);													// Mouse
		table.addShadow(69,   52);													// Seal
		table.addShadow(157,  156);													// Penguin
		table.addShadow(394,  325);													// Villager Lady
		table.addShadow(232,  277);													// Villager Man - body
		table.addShadow(49,   34);													// Villager Man - head
		table.addShadow(185,  216);													// Villager Kid
		/* Units */
		table.addShadow(102,  122);													// Nerubian warrior - top
		table.addShadow(121,  106);													// Nerubian warrior - body
		table.addShadow(269,  140);													// Nerubian warrior - claws
		table.addShadow(111,  71);													// Ice Revenant - top
		table.addShadow(209,  215);													// Ice Revenant - body
		table.addShadow(24,   16);													// Doom Guard - top
		table.addShadow(652,  507);													// Doom Guard - body
		table.addShadow(24,   16);													// Sea Giant - top
		table.addShadow(688,  566);													// Sea Giant - body
		table.addShadow(92,   72);													// Sea Giant - hat
		table.addShadow(30,   32);													// Skeletal Orc - top
		table.addShadow(273,  299);													// Skeletal Orc - body
		table.addShadow(35,   34);													// Gul'dan - top
		table.addShadow(536,  569);													// Gul'dan - body
		table.addShadow(30,   21);													// Orge Mauler - top
		table.addShadow(565,  473);													// Orge Mauler - body
		table.addShadow(521,  328);													// Boulder Golem - body
		//table.addShadow(37,   62);												// Boulder Golem - head
		table.addShadow(286,  272);													// Forest Troll Priest - body
		table.addShadow(361,  373);													// Forest Troll Hunter - body
		table.addShadow(257,  183);													// Murloc Reaver - top
		table.addShadow(218,  176);													// Murloc Reaver - body
		table.addShadow(116,  58);													// Dragon Turtle - top
		table.addShadow(566,  513);													// Dragon Turtle - body
		table.addShadow(117,  113);													// Kobos mage - top
		table.addShadow(136,  124);													// Kobos mage - body
		table.addShadow(90,   81);													// Kobos warrior - top
		table.addShadow(19,   22);													// Kobos warrior - weapon
		table.addShadow(165,  152);													// Kobos warrior - weapon
		table.addShadow(566,  513);													// Dragon Turtle - body
		table.addShadow(132,  146);													// Gnoll archer - top
		table.addShadow(281,  256);													// Gnoll archer - body
		table.addShadow(90,   110);													// Gnoll warrior - top
		table.addShadow(296,  268);													// Gnoll warrior - body
		table.addShadow(105,  62);													// Bandit warrior - top
		table.addShadow(369,  268);													// Bandit warrior - body
		table.addShadow(78,   62);													// Bandit archer - top
		table.addShadow(299,  228);													// Bandit archer - body
		table.addShadow(14,   18);													// Skeleton archer - top
		table.addShadow(321,  316);													// Skeleton archer - body
		table.addShadow(57,   44);													// Sasquatch - top
		table.addShadow(380,  371);													// Sasquatch - body
		table.addShadow(58,   54);													// Crab - top
		table.addShadow(298,  321);													// Crab - body
		table.addShadow(317,  292);													// Hydra - top
		table.addShadow(160,  136);													// Hydra - body
		table.addShadow(34,   38);													// Makrura - top
		table.addShadow(476,  524);													// Makrura - body
		table.addShadow(71,   72);													// Tuskarr - top
		table.addShadow(366,  424);													// Tuskarr - body
		table.addShadow(426,  486);													// Tuskarr - body2
		table.addShadow(34,   48);													// Mammoth - top
		table.addShadow(541,  515);													// Mammoth - body
		table.addShadow(40,   20,   SHW_USE_TRANSFORMATION);						// Arachnathid - top
		table.addShadow(617,  518);													// Arachnathid - body
		table.addShadow(52,   52);													// Magnataur - top
		table.addShadow(733,  741);													// Magnataur - body
		table.addShadow(17,   14);													// Spider - top
		table.addShadow(392,  334);													// Spider - body
		table.addShadow(56,   46);													// Bear - top
		table.addShadow(457,  396);													// Bear - body
		table.addShadow(46,   42);													// Clockwreck Goblin - top
		table.addShadow(350,  219);													// Clockwreck Goblin - top
		table.addShadow(164,  74);													// Goblin Shredder - top
		table.addShadow(593,  318);													// Goblin Shredder - body
		table.addShadow(13,   10);													// Goblin Sapper - top
		table.addShadow(742,  536);													// Goblin Sapper - body
		table.addShadow(82,   84);													// Lava Spawn - top
		table.addShadow(419,  378);													// Lava Spawn - body
		table.addShadow(52,   50);													// Quilbeast - top
		table.addShadow(398,  403);													// Quilbeast - body
		table.addShadow(43,   42);													// Furbolg mage - top
		table.addShadow(282,  230);													// Furbolg mage - body
		table.addShadow(139,  84);													// Furbolg mage - top
		table.addShadow(287,  230);													// Furbolg mage - body
		table.addShadow(155,  96);													// Furbolg mage - top
		table.addShadow(335,  246);													// Furbolg mage - body
		table.addShadow(26,   16);													// Furbolg warrior - top
		table.addShadow(325,  272);													// Furbolg warrior - body
		table.addShadow(80,   48,   SHW_USE_TRANSFORMATION);						// Lightning Lizard - top
		table.addShadow(528,  485);													// Lightning Lizard - body
		table.addShadow(85,   93);													// Satyr - top
		table.addShadow(350,  311);													// Satyr - body
		table.addShadow(53,   44);													// Centaur archer - top
		table.addShadow(209,  222);													// Centaur archer - body
		table.addShadow(30,   29);													// Centaur warrior - top
		table.addShadow(233,  238);													// Centaur warrior - body
		table.addShadow(38,   34);													// Wildkin - top
		table.addShadow(617,  520);													// Wildkin - body
		table.addShadow(66,   53);													// Razormane - top
		table.addShadow(450,  349);													// Razormane warrior - body
		table.addShadow(434,  349);													// Razormane archer - body
		table.addShadow(40,   38);													// Draenei warrior - top
		table.addShadow(541,  431);													// Draenei warrior - body
		table.addShadow(577,  470);													// Draenei mage - body
		table.addShadow(78,   61);													// Felguard - top
		table.addShadow(529,  538);													// Felguard - body
		table.addShadow(56,   42);													// Diabolist - top
		table.addShadow(375,  379);													// Diabolist - body
		table.addShadow(183,  108);													// Diabolist - cloak
		table.addShadow(539,  509);													// Fel Beast - body
		table.addShadow(31,   23);													// Inferno Contraption - top
		table.addShadow(605,  596);													// Inferno Contraption - body
		table.addShadow(60,   30,   SHW_USE_TRANSFORMATION);						// Succubus - top
		table.addShadow(548,  586);													// Succubus - body
		table.addShadow(68,   65);													// Apprentice Wizard - top
		table.addShadow(315,  322);													// Apprentice Wizard - body
		table.addShadow(48,   39);													// Reject - top
		table.addShadow(290,  228);													// Reject - body
		table.addShadow(303,  283);													// Zombie - body
		table.addShadow(48,   40);													// Dragonspawn - top
		table.addShadow(571,  526);													// Dragonspawn - body
		table.addShadow(104,  110);													// Dragonspawn - tail
		table.addShadow(21,   36,   SHW_USE_TRANSFORMATION);						// Dragonspawn - weapon
		table.addShadow(60,   28);													// Faceless - top
		table.addShadow(545,  412);													// Faceless - body
		table.addShadow(22,   15);													// Centaur small - top
		table.addShadow(251,  252);													// Centaur small - body
		table.addShadow(18,   27,   SHW_USE_TRANSFORMATION);						// Centaur small - body
		table.addShadow(93,   78);													// Poisonous TreeAnt - top
		table.addShadow(282,  399);													// Poisonous TreeAnt - body
		table.addShadow(422,  265);													// War Golem
		table.addShadow(299,  172);													// Nerubian - body2
		table.addShadow(91,   74);													// Nerubian - body2 claws
		#pragma endregion

		#pragma region Misc
		/* Item */
		table.addShadow(178,  116,  SHW_USE_TRANSFORMATION);						// Book
		table.addShadow(76,   48,   SHW_USE_TRANSFORMATION);						// Treasure Box
		#pragma endregion
	}
}