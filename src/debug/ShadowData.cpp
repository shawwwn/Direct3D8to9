#include "../ShadowVolumeHandler.h"

namespace SV {
	void ShadowTable::InitShadowTable()
	{
		#pragma region Human
		addShadow(28,   25);													// Human Rally Point - top
		/* Heroes */
		addShadow(21,   26);													// Archmage - top
		addShadow(615,  486);													// Archmage - body
		//addShadow(64,   64);												// Blood Mage - top [leak]
		addShadow(643,  505);													// Blood Mage - body
		addShadow(63,   58);													// Paladin - top [leak]
		addShadow(510,  382);													// Paladin - body [leak]
		addShadow(18,   22);													// Mountain King - top
		addShadow(458,  415,  SHW_USE_TRANSFORMATION);						// Mountain King - body
		/* Units */
		addShadow(46,   60);													// Peasant - body
		addShadow(302,  270);													// Peasant - top
		addShadow(120,  48,  SHW_USE_TRANSFORMATION);							// Peasant - lumber
		addShadow(36,   35);													// Peasant - gold
		addShadow(280,  278);													// Militia - body
		addShadow(138,  107);													// Spellbreaker - top
		addShadow(310,  296);													// Spellbreaker - body
		addShadow(42,   25,  SHW_USE_TRANSFORMATION);							// Spellbreaker - sword
		addShadow(52,   35);													// Footman - top
		addShadow(447,  288);													// Footman - body
		addShadow(169,  115);													// Riflemane - top
		addShadow(342,  299);													// Riflemane - body
		addShadow(88,   61);													// Knight - top
		addShadow(541,  428);													// Knight - body
		addShadow(96,   99);													// Priest - top
		addShadow(301,  300);													// Priest - body
		addShadow(10,   9);													// Priest - staff
		addShadow(107,  58);													// Mage - top
		addShadow(407,  369);													// Mage - body
		addShadow(40,   29);													// Motar Team - top
		addShadow(490,  481);													// Motar Team - body
		//addShadow(17,   22,  SHW_USE_TRANSFORMATION);						// Motar Team - scope
		addShadow(52,   44);													// Motar Team - cannon
		addShadow(22,   18,   SHW_USE_TRANSFORMATION);						// Tank - top
		addShadow(778,  512);													// Tank - body
		//addShadow(78,   118, SHW_USE_TRANSFORMATION);						// Tank - eagle head
		addShadow(20,   12,   SHW_FLYING_UNIT | SHW_USE_TRANSFORMATION);		// Water Element - top
		addShadow(206,  134,  SHW_FLYING_UNIT);								// Water Element - upper part
		addShadow(72,   38,   SHW_FLYING_UNIT);								// Water Element - body
		/* Flying Units */
		//addShadow(32,   40,   SHW_FLYING_UNIT);								// Griffin - top [leak]
		//addShadow(451,  369,  SHW_FLYING_UNIT);								// Griffin - body [leak]
		//addShadow(21,   22,   SHW_FLYING_UNIT);								// Griffin - hammer
		//addShadow(104,  77,   SHW_FLYING_UNIT);								// DragonHawk - top [leak]
		//addShadow(558,  391,  SHW_FLYING_UNIT);								// DragonHawk - body [leak]
		//addShadow(89,   53,   SHW_FLYING_UNIT);								// Helicopter - top
		//addShadow(445,  374,  SHW_FLYING_UNIT);								// Helicopter - body (dislay issue)
		#pragma endregion

		#pragma region Orc
		//addShadow(8,    6);													// Orc Rally Point - top [conflict]
		addShadow(32,   18);													// Orc Rally Point - body
		/* Heroes */
		addShadow(42,   41);													// Blasdemaster - top
		addShadow(405,  365);													// Blasdemaster - body
		//addShadow(24,   18,   SHW_USE_TRANSFORMATION);						// Blasdemaster - blade [conflict]
		addShadow(31,   30);													// Farseer - top
		addShadow(673,  518);													// Farseer - body
		addShadow(48,   60);													// Shadow Hunter - top
		addShadow(444,  362);													// Shadow Hunter - body
		addShadow(30,   17,   SHW_USE_TRANSFORMATION);						// Shadow Hunter - spear
		addShadow(108,  99);													// Tauren Warchief - top
		addShadow(335,  317);													// Tauren Warchief - body
		addShadow(24,   26);													// Tauren Warchief - weapon
		/* Units */
		addShadow(83,   85);													// Grunt - top
		addShadow(411,  320);													// Grunt - body
		addShadow(16,   16,   SHW_USE_TRANSFORMATION);						// Grunt - axe
		addShadow(58,   46);													// Peon - top
		addShadow(220,  212);													// Peon - body
		addShadow(26,   26);													// Berserk Troll - top
		addShadow(63,   48);													// Berserk Troll - hair
		//addShadow(28,   36);												// Berserk Troll - spear [projectile]
		addShadow(313,  321);													// Berserk Troll - body
		addShadow(90,   106);													// Spirit Walker(transparent) - top
		addShadow(42,   24);													// Spirit Walker(transparent) - feet
		addShadow(332,  360);													// Spirit Walker(transparent) - body
		addShadow(71,   56);													// Wolf - top (display issue)
		addShadow(291,  269);													// Wolf - body (display issue)
		//addShadow(18,   56,   SHW_USE_TRANSFORMATION);						// Sepent Ward - top [leak]
		//addShadow(120,  112);												// Sepent Ward - body (display issue)
		addShadow(41,   42);													// Sepent Ward - base
		addShadow(47,   46);													// Healing Ward - base
		addShadow(42,   40,   SHW_USE_TRANSFORMATION);						// Stunning Ward - body
		addShadow(151,  192);													// Eye Ward - eye
		addShadow(30,   38,   SHW_USE_TRANSFORMATION);						// Eye Ward - body
		addShadow(94,   85);													// Troll Headhunter - top
		//addShadow(9,    7);													// Troll Headhunter - spear
		addShadow(364,  322);													// Troll Headhunter - body
		addShadow(46,   43);													// Shaman - top
		addShadow(465,  348);													// Shaman - body
		addShadow(69,   42);													// Shaman - lower hem
		addShadow(131,  80);													// Voodoo Priest - top
		addShadow(314,  288);													// Voodoo Priest - body
		addShadow(27,   28);													// Voodoo Priest - staff
		addShadow(84,   80);													// Raider - top
		addShadow(493,  381);													// Raider - body
		//addShadow(90,   106);												// Spirit Walker(normal) - top (display issue)
		//addShadow(332,  360);												// Spirit Walker(normal) - body (display issue)
		//addShadow(42,   24);												// Spirit Walker(normal) - bristle (display issue)
		addShadow(42,   36);													// Kodo Beast - top
		addShadow(591,  537);													// Kodo Beast - body
		//addShadow(30,   26);												// Kodo Beast - drums
		addShadow(50,   35);													// Tauren - top
		addShadow(459,  379);													// Tauren - body
		addShadow(50,   32,   SHW_USE_TRANSFORMATION);						// Demolisher - top
		addShadow(643,  389);													// Demolisher - body
		//addShadow(53,   40,   SHW_USE_TRANSFORMATION | SHW_FLYING_UNIT);	// Demolisher - rock [projectile]
		/* Flying Units */
		//addShadow(88,   91,   SHW_FLYING_UNIT);								// Wyvern - top
		//addShadow(4,    4,    SHW_FLYING_UNIT);								// Wyvern - spear
		//addShadow(395,  383,  SHW_FLYING_UNIT);								// Wyvern - body
		//addShadow(29,   22,   SHW_FLYING_UNIT | SHW_USE_TRANSFORMATION);	// Wyvern - spear2
		//addShadow(37,   34,   SHW_FLYING_UNIT);								// Troll Batrider - top
		//addShadow(398,  379,  SHW_FLYING_UNIT);								// Troll Batrider - body
		//addShadow(20,   12,   SHW_FLYING_UNIT | SHW_USE_TRANSFORMATION);	// Troll Batrider - bomb [projectile]
		//addShadow(108,  73,   SHW_FLYING_UNIT);								// Troll Batrider - wings
		#pragma endregion

		#pragma region FelOrc
		/* Heroes */
		addShadow(695,  742);													// New Blademaster - top lower body (performance)
		addShadow(619,  826);													// New Blademaster - top upper body (performance)
		addShadow(36,   50);													// New Blademaster - top flag (performance)
		addShadow(87,   84,   SHW_USE_TRANSFORMATION);						// New Blademaster - top stick (performance)
		addShadow(62,   59,   SHW_USE_TRANSFORMATION);						// New Blademaster - blade (performance)
		/* Units */
		addShadow(59,   63);													// Fel Grunt - top
		addShadow(435,  342);													// Fel Grunt - body
		addShadow(181,  151);													// Fel Grunt - unknown
		addShadow(85,   96);													// Crossbowman - top lower body
		addShadow(96,   114);													// Crossbowman - top upper body
		addShadow(235,  186);													// Crossbowman - top crossbow
		addShadow(25,   13);													// Crossbowman - top arm
		addShadow(62,   48);													// Warlock - top
		addShadow(220,  234);													// Warlock - body
		addShadow(46,   28,   SHW_USE_TRANSFORMATION);						// War Station - top
		addShadow(673,  393);													// War Station - body
		addShadow(314,  159,  SHW_USE_TRANSFORMATION);						// War Station - tower
		#pragma endregion

		#pragma region Night Elf
		addShadow(72,   40,   SHW_USE_TRANSFORMATION);						// NightElf Rally Point - top
		addShadow(12,   6,    SHW_USE_TRANSFORMATION);						// NightElf Rally Point - body
		/* Heroes */
		addShadow(30,   36);													// Demon Hunter - top
		addShadow(377,  397);													// Demon Hunter	- body
		addShadow(411,  460);													// Demon Hunter	- demon
		addShadow(82,   61);													// Keeper of the Grove - top
		addShadow(486,  482);													// Keeper of the Grove - body
		addShadow(41,   50);													// Warden - top
		addShadow(94,   46);													// Warden - cloak
		addShadow(86,   46);													// Warden - cloak2
		addShadow(610,  521);													// Warden - body
		addShadow(60,   66);													// Priest of the Moon - top
		addShadow(50,   26);													// Priest of the Moon - bow
		addShadow(419,  394);													// Priest of the Moon - body
		/* Units */
		addShadow(73,   37);													// Archer - top
		addShadow(331,  380);													// Archer - body
		addShadow(74,   43);													// Huntress - top
		addShadow(49,   23);													// Huntress - glaive
		addShadow(490,  457);													// Huntress - body
		addShadow(66,   62);													// Dryad - top
		addShadow(280,  354);													// Dryad - body [leak]
		//addShadow(6,    7,    SHW_USE_TRANSFORMATION);						// Dryad - spear [projectile]
		//addShadow(20,   20,   SHW_USE_TRANSFORMATION);						// Dryad - spear top [projectile]
		addShadow(62,   52);													// Druid of the Talon - top
		addShadow(514,  402);													// Druid of the Talon - body
		addShadow(41,   38);													// Druid of the Talon - death top
		addShadow(22,   16,   SHW_USE_TRANSFORMATION);						// Druid of the Talon - death top cloak
		addShadow(232,  234);													// Druid of the Talon - death body
		addShadow(136,  151);													// Druid of the Talon - death body2
		addShadow(28,   16,   SHW_USE_TRANSFORMATION);						// Druid of the Claw - top
		addShadow(486,  489);													// Druid of the Claw - body
		//addShadow(116,  144);												// Druid of the Claw - backpack
		addShadow(22,   16);													// Druid of the Claw - bear top
		addShadow(493,  428);													// Druid of the Claw - bear body
		addShadow(34,   26);													// Mountain Giant - top
		addShadow(634,  541);													// Mountain Giant - body
		//addShadow(126,  70);												// Mountain Giant - grass
		addShadow(27,   22);													// Mountain Giant - weapon1
		addShadow(55,   46);													// Mountain Giant - weapon2
		//addShadow(12,   8);													// Glaive Thrower - top
		addShadow(359,  239);													// Glaive Thrower - body
		//addShadow(38,   42,   SHW_USE_TRANSFORMATION);						// Glaive Thrower - glaive [projectile]
		addShadow(152,  114);													// Treant - top
		addShadow(278,  230);													// Treant - body
		addShadow(22,   14);													// Small Ghost - top
		addShadow(521,  413);													// Small Ghost - body
		addShadow(825,  649);													// Big Ghost - body
		/* New Units */
		addShadow(731,  1038);												// New Mountain Giant - top

		/* Flying Units */
		//addShadow(53,   54,   SHW_FLYING_UNIT);								// Chimaera - top [leak]
		//addShadow(500,  418,  SHW_FLYING_UNIT);								// Chimaera - body [leak]
		//addShadow(87,   85,   SHW_FLYING_UNIT);								// Hippogryph - top [leak]
		//addShadow(325,  259,  SHW_FLYING_UNIT);								// Hippogryph - body [leak]
		//addShadow(81,   81,   SHW_FLYING_UNIT);								// Hippogryph - mounted top wing [leak]
		//addShadow(90,   48,   SHW_FLYING_UNIT);								// Hippogryph - mounted top archer cloak [leak]
		//addShadow(246,  253,  SHW_FLYING_UNIT);								// Hippogryph - mounted archer [leak]
		//addShadow(290,  239,  SHW_FLYING_UNIT);								// Hippogryph - mounted body [leak]
		//addShadow(76,   80,   SHW_FLYING_UNIT);								// Faerie Dragon - top [leak]
		//addShadow(264,  260,  SHW_FLYING_UNIT);								// Faerie Dragon - body [leak]
		//addShadow(42,   32,   SHW_FLYING_UNIT);								// Druid of the Talon - bird top [leak]
		//addShadow(205,  224,  SHW_FLYING_UNIT);								// Druid of the Talon - bird body [leak]
		#pragma endregion

		#pragma region Undead
		addShadow(76,   42,   SHW_USE_TRANSFORMATION);						// Undead Rally Point
		/* Heroes */
		addShadow(82,   39);													// Death Knight - top
		addShadow(597,  556);													// Death Knight - body
		addShadow(110,  94);													// Cryptlord - top
		addShadow(513,  587);													// Cryptlord - body
		addShadow(128,  79);													// Lich - top
		addShadow(562,  418);													// Lich - body
		addShadow(99,   68);													// Dreadlord - top
		addShadow(432,  442);													// Dreadlord - body
		/* Units */
		addShadow(243,  358);													// Inferno - body
		addShadow(28,   32);													// Crypt Fiend - top
		addShadow(455,  460);													// Crypt Fiend - body
		addShadow(72,   42);													// Necromancer - top
		addShadow(500,  498);													// Necromancer - body
		addShadow(49,   28,   SHW_FLYING_UNIT);								// Witch - top
		addShadow(308,  272,  SHW_FLYING_UNIT);								// Witch - body
		addShadow(48,   32);													// Meat Wagon - top
		addShadow(695,  490);													// Meat Wagon - body
		addShadow(31,   34);													// Abomination - top
		addShadow(379,  441);													// Abomination - body
		addShadow(65,   63,   SHW_USE_TRANSFORMATION);						// Gargoyle ground - top
		addShadow(343,  276,  SHW_USE_TRANSFORMATION);						// Gargoyle ground - body
		addShadow(51,   62,   SHW_USE_TRANSFORMATION);						// Obsidian Statue - top
		addShadow(415,  546,  SHW_USE_TRANSFORMATION);						// Obsidian Statue - body
		addShadow(109,  62,   SHW_USE_TRANSFORMATION);						// Obsidian Statue - base
		addShadow(31,   26);													// Ghoul - top
		addShadow(504,  437);													// Ghoul - body
		addShadow(58,   37);													// Acolyte - top
		addShadow(365,  316);													// Acolyte - body
		addShadow(248,  259,  SHW_FLYING_UNIT);								// Shadow - body
		addShadow(42,   37,   SHW_FLYING_UNIT);								// Shadow - top
		addShadow(24,   32);													// Beetle - top
		addShadow(168,  200);													// Beetle - top
		addShadow(8,    9,    SHW_USE_TRANSFORMATION);						// Skeleton - top
		addShadow(327,  325);													// Skeleton - body
		addShadow(36,   40);													// Skeleton Mage - top
		addShadow(363,  321);													// Skeleton Mage - body
		/* Flying Unit */
		//addShadow(102,  83,   SHW_FLYING_UNIT);								// Gargoyle fly - top
		//addShadow(485,  385,  SHW_FLYING_UNIT);								// Gargoyle fly - body
		//addShadow(53,   64,   SHW_FLYING_UNIT);								// Destroyer - top
		//addShadow(500,  549,  SHW_FLYING_UNIT);								// Destroyer - body
		//addShadow(89,   56,   SHW_FLYING_UNIT);								// Frost Wyrm - top
		//addShadow(125,  110,  SHW_FLYING_UNIT);								// Frost Wyrm - rib
		//addShadow(358,  279,  SHW_FLYING_UNIT);								// Frost Wyrm - body
		#pragma endregion

		#pragma region Naga
		/* Heroes */
		addShadow(90,   83);													// Naga Sea Witch - top
		addShadow(1073, 760);													// Naga Sea Witch - body
		//addShadow(90,   52);												// Enchantress - top (performance)
		//addShadow(52,   190);												// Enchantress - wraps (performance)
		//addShadow(755,  3880);												// Enchantress - body (performance)
		addShadow(2046, 2128);												// Murloc Hero - body
		addShadow(252,  408);													// Tidal Baron - top
		addShadow(948,  808);													// Tidal Baron - body
		//addShadow(369,  190);												// Tidal Baron - fin
		addShadow(214,  356,  SHW_USE_TRANSFORMATION);						// Tidal Baron - weapon
		//addShadow(326,  381);												// Illidan - wing (performance)
		//addShadow(534,  823);												// Illidan - hand (performance)
		//addShadow(574,  724);												// Illidan - face (performance)
		//addShadow(1221, 1513);												// Illidan - lower body (performance)
		//addShadow(1566, 2078);												// Illidan - upper body (performance)
		//addShadow(538,  740,  SHW_USE_TRANSFORMATION);						// Illidan - weapon (performance)
		/* Units */
		addShadow(77,   80);													// Couatl - top
		addShadow(90,   52);													// Naga Siren - top
		addShadow(543,  552);													// Naga Siren - body
		addShadow(95,   74);													// Snap Dragon - top
		addShadow(361,  378);													// Snap Dragon - body
		addShadow(41,   46);													// Naga Myrmidon - top
		addShadow(395,  425);													// Naga Myrmidon - body
		//addShadow(39,   36);												// Naga Myrmidon - spikes
		addShadow(92,   56);													// Naga Myrmidon - sword
		addShadow(36,   34);													// Naga Loyal Guard - top
		addShadow(412,  453);													// Naga Loyal Guard - body
		//addShadow(94,   58);												// Naga Loyal Guard - spikes
		addShadow(90,   83);													// Murloc Slave - top
		addShadow(238,  207);													// Murloc Slave - body
		addShadow(21,   7);													// Murloc Catapult - basket
		addShadow(273,  210);													// Murloc Catapult - body
		//addShadow(68,   88);												// Hunting Shark - body (performance)
		//addShadow(35,   64);												// Hunting Shark - legs (performance)
		//addShadow(40,   90);												// Hunting Shark - arms (performance)
		//addShadow(182,  222);												// Hunting Shark - head (performance)
		#pragma endregion

		#pragma region IceTroll
		/* Heroes */
		addShadow(1141, 1460);												// Shadow Warlock - top
		addShadow(69,   118,  SHW_USE_TRANSFORMATION);						// Shadow Warlock - top rod
		addShadow(58,   57,   SHW_USE_TRANSFORMATION);						// Shadow Warlock - top skull
		addShadow(473,  565);													// Bloodrager - top
		addShadow(154,  110,  SHW_USE_TRANSFORMATION);						// Bloodrager - weapon
		addShadow(506,  469);													// Bloodrager - body
		addShadow(59,   34);													// Voodoo Priest - top
		addShadow(390,  321);													// Voodoo Priest - body
		addShadow(197,  209,  SHW_USE_TRANSFORMATION);						// Voodoo Priest - weapon
		/* Units */
		addShadow(542,  418);													// Voodoo Doll - top
		//addShadow(20,   12,   SHW_USE_TRANSFORMATION);						// Gold Digger - hair
		addShadow(176,  156);													// Gold Digger - body
		addShadow(156,  166);													// Gold Digger - axe
		addShadow(18,   24);													// Voodoo Wishman - top
		addShadow(240,  217,  SHW_USE_TRANSFORMATION);						// Voodoo Wishman - body
		addShadow(328,  261,  SHW_USE_TRANSFORMATION);						// Voodoo Wishman - head
		//addShadow(49,   40,   SHW_USE_TRANSFORMATION);						// Totemist - top
		//addShadow(40,   25,   SHW_USE_TRANSFORMATION);						// Totemist - top hair
		//addShadow(57,   24,   SHW_USE_TRANSFORMATION);						// Totemist - top gen
		//addShadow(59,   72,   SHW_USE_TRANSFORMATION);						// Totemist - top rod
		//addShadow(42,   30,   SHW_USE_TRANSFORMATION);						// Totemist - face
		//addShadow(435,  262,  SHW_USE_TRANSFORMATION);						// Totemist - upper body
		//addShadow(36,   32,   SHW_USE_TRANSFORMATION);						// Totemist - skirt edge
		//addShadow(30,   32,   SHW_USE_TRANSFORMATION);						// Totemist - skirt
		//addShadow(59,   46,   SHW_USE_TRANSFORMATION);						// Totemist - skull
		addShadow(18,   14);													// Catapult - top
		addShadow(368,  271);													// Catapult - body
		addShadow(22,   32,   SHW_USE_TRANSFORMATION);						// IceTroll Warrior - left axe
		addShadow(21,   32,   SHW_USE_TRANSFORMATION);						// IceTroll Warrior - right axe
		addShadow(23,   30,   SHW_USE_TRANSFORMATION);						// Mocking Totem
		addShadow(246,  282,  SHW_USE_TRANSFORMATION);						// Healing Ward
		addShadow(622,  562);													// Imp - body
		addShadow(66,   32);													// Imp - hair
		addShadow(243,  282,  SHW_USE_TRANSFORMATION);						// Statsis Trap
		#pragma endregion

		#pragma region BloodElf
		/* Heroes */
		addShadow(63,   136);													// BloodKnight - top
		addShadow(749,  430);													// BloodKnight - body
		addShadow(50,   75,   SHW_USE_TRANSFORMATION);						// BloodKnight - sword
		addShadow(116,  120);													// BloodKnight - hair
		//addShadow(102,  124);												// Arcanist - top [leak]
		//addShadow(887,  1368);												// Arcanist - body [leak]
		addShadow(63,   54);													// Arcane Ranger - hair
		addShadow(16,   16);													// Arcane Ranger - scarf1
		addShadow(36,   36);													// Arcane Ranger - scarf2
		addShadow(100,  104);													// Arcane Ranger - bow
		addShadow(42,   48,   SHW_USE_TRANSFORMATION);						// Arcane Ranger - boots
		addShadow(67,   68);													// Arcane Ranger - pants
		addShadow(32,   32,   SHW_USE_TRANSFORMATION);						// Arcane Ranger - sleeves
		//addShadow(34,   24);												// Arcane Ranger - top cloak
		addShadow(36,   24);													// Arcane Ranger - cloak
		addShadow(129,  68);													// Arcane Ranger - shoulder
		/* Units */
		addShadow(253,  241);													// Engineer - body
		addShadow(45,   64);													// Swordsman - top leg
		addShadow(46,   60);													// Swordsman - top waist
		addShadow(52,   56);													// Swordsman - top shoulder
		addShadow(303,  165);													// Swordsman - head
		addShadow(230,  231);													// Swordsman - sword
		addShadow(95,   67);													// Swordsman - helmet
		addShadow(12,   9);													// Shieldsman - shield
		addShadow(284,  279);													// Shieldsman - sword
		addShadow(90,   73);													// Peacemaker - top shoulder
		addShadow(111,  71);													// Peacemaker - top cloak
		addShadow(78,   26,   SHW_USE_TRANSFORMATION);						// Peacemaker - weapon
		addShadow(206,  90,   SHW_USE_TRANSFORMATION);						// Peacemaker - weapon handle
		addShadow(453,  354,  SHW_USE_TRANSFORMATION);						// Peacemaker - body
		addShadow(76,   67,   SHW_USE_TRANSFORMATION);						// Peacemaker - shield
		addShadow(22,   23);													// Archer - top cloak
		addShadow(112,  99);													// Archer - top shoulder
		addShadow(28,   30);													// Archer - thigh
		addShadow(70,   80);													// Archer - leg
		addShadow(135,  131);													// Archer - head
		addShadow(37,   34);													// Archer - bow
		addShadow(117,  69);													// Archer - hair
		addShadow(459,  483);													// Juggernaut - top
		addShadow(599,  601);													// Juggernaut - body
		//addShadow(211,  374);												// Blood Priest - top [leak]
		//addShadow(131,  220);												// Blood Priest - body [leak]
		//addShadow(323,  183);												// Blood Priest - head [leak]
		addShadow(24,   40);													// Arcane Golem - top shoulder
		addShadow(159,  96);													// Arcane Golem - hand
		addShadow(73,   32);													// Arcane Golem - feet
		addShadow(65,   80);													// Arcane Golem - body
		addShadow(77,   41,   SHW_USE_TRANSFORMATION);						// Arcane Golem - head
		addShadow(68,   52);													// Arcane Golem - arm
		addShadow(16,   8,    SHW_USE_TRANSFORMATION);						// Arcane Golem - center gem
		addShadow(26,   44);													// Arcane Golem - decoration
		addShadow(20,   18);													// Wrenched warrior - top
		addShadow(369,  350);													// Wrenched warrior - body
		addShadow(125,  123,  SHW_USE_TRANSFORMATION);						// Wrenched mage - head
		addShadow(164,  166);													// Wrenched mage - body
		addShadow(20,   22);													// Wrenched mage - cloth
		//addShadow(284,  488);												// Wraith small (performance)
		addShadow(271,  514);													// Wraith big
		addShadow(95,   90,   SHW_USE_TRANSFORMATION);						// Wraith big wrist
		addShadow(46,   48,   SHW_USE_TRANSFORMATION);						// Holy Knight weapon
		#pragma endregion

		#pragma region Neutral
		/* Heroes */
		addShadow(26,   28);													// Tinker - top
		addShadow(1080, 681);													// Tinker - body
		addShadow(38,   28);													// Alchemist - top
		addShadow(763,  606);													// Alchemist - body
		addShadow(60,   60);													// Alchemist - tusks
		addShadow(33,   39);													// BeastMaster - top
		addShadow(650,  563);													// BeastMaster - body
		addShadow(9,    4);													// Dark Ranger - top
		addShadow(505,  447);													// Dark Ranger - body
		addShadow(56,   40);													// Firelord - top
		addShadow(318,  308);													// Firelord - body
		addShadow(260,  256);													// Firelord - armor
		addShadow(12,   10);													// Brewmaster - top
		addShadow(568,  481);													// Brewmaster - body
		addShadow(72,   52);													// Brewmaster - barrel
		addShadow(451,  413);													// Earth - body
		addShadow(93,   62);													// Earth - stone
		addShadow(505,  429);													// Fire - body
		addShadow(48,   36);													// Fire - blades
		addShadow(528,  439);													// Air - body
		addShadow(20,   20);													// Pitlord - top
		addShadow(702,  635);													// Pitlord - body
		/* Small Animals */
		addShadow(75,   69);													// Sheep
		addShadow(209,  212);													// Deer
		addShadow(139,  98);													// Chicken
		addShadow(157,  105);													// Fog
		addShadow(91,   70);													// Pig
		addShadow(160,  107);													// Rabbit
		addShadow(291,  212);													// Racoon
		addShadow(353,  374);													// Crab
		addShadow(356,  374);													// Helmet Crab
		addShadow(251,  194);													// Lizard
		addShadow(132,  96);													// Sandworm
		addShadow(155,  168);													// Wolf
		addShadow(96,   72);													// Mouse
		addShadow(69,   52);													// Seal
		addShadow(157,  156);													// Penguin
		addShadow(394,  325);													// Villager Lady
		addShadow(232,  277);													// Villager Man - body
		addShadow(49,   34);													// Villager Man - head
		addShadow(185,  216);													// Villager Kid
		/* Units */
		addShadow(102,  122);													// Nerubian warrior - top
		addShadow(121,  106);													// Nerubian warrior - body
		addShadow(269,  140);													// Nerubian warrior - claws
		addShadow(111,  71);													// Ice Revenant - top
		addShadow(209,  215);													// Ice Revenant - body
		addShadow(24,   16,   SHW_USE_TRANSFORMATION);						// Doom Guard - top
		addShadow(652,  507);													// Doom Guard - body
		addShadow(688,  566);													// Sea Giant - body
		addShadow(92,   72);													// Sea Giant - hat
		addShadow(30,   32);													// Skeletal Orc - top
		addShadow(273,  299);													// Skeletal Orc - body
		addShadow(35,   34);													// Gul'dan - top
		addShadow(536,  569);													// Gul'dan - body
		addShadow(30,   21);													// Orge Mauler - top
		addShadow(565,  473);													// Orge Mauler - body
		addShadow(521,  328);													// Boulder Golem - body
		//addShadow(37,   62);												// Boulder Golem - head
		addShadow(286,  272);													// Forest Troll Priest - body
		addShadow(361,  373);													// Forest Troll Hunter - body
		addShadow(257,  183);													// Murloc Reaver - top
		addShadow(218,  176);													// Murloc Reaver - body
		addShadow(116,  58);													// Dragon Turtle - top
		addShadow(566,  513);													// Dragon Turtle - body
		addShadow(117,  113);													// Kobos mage - top
		addShadow(136,  124);													// Kobos mage - body
		addShadow(90,   81);													// Kobos warrior - top
		addShadow(19,   22);													// Kobos warrior - weapon
		addShadow(165,  152);													// Kobos warrior - weapon
		addShadow(566,  513);													// Dragon Turtle - body
		addShadow(132,  146);													// Gnoll archer - top
		addShadow(281,  256);													// Gnoll archer - body
		addShadow(90,   110);													// Gnoll warrior - top
		addShadow(296,  268);													// Gnoll warrior - body
		addShadow(105,  62);													// Bandit warrior - top
		addShadow(369,  268);													// Bandit warrior - body
		addShadow(78,   62);													// Bandit archer - top
		addShadow(299,  228);													// Bandit archer - body
		addShadow(14,   18);													// Skeleton archer - top
		addShadow(321,  316);													// Skeleton archer - body
		addShadow(57,   44);													// Sasquatch - top
		addShadow(380,  371);													// Sasquatch - body
		addShadow(58,   54);													// Crab - top
		addShadow(298,  321);													// Crab - body
		addShadow(317,  292);													// Hydra - top
		addShadow(160,  136);													// Hydra - body
		addShadow(34,   38);													// Makrura - top
		addShadow(476,  524);													// Makrura - body
		addShadow(71,   72);													// Tuskarr - top
		addShadow(366,  424);													// Tuskarr - body
		addShadow(426,  486);													// Tuskarr - body2
		addShadow(34,   48);													// Mammoth - top
		addShadow(541,  515);													// Mammoth - body
		addShadow(40,   20,   SHW_USE_TRANSFORMATION);						// Arachnathid - top
		addShadow(617,  518);													// Arachnathid - body
		addShadow(52,   52);													// Magnataur - top
		addShadow(733,  741);													// Magnataur - body
		addShadow(17,   14);													// Spider - top
		addShadow(392,  334);													// Spider - body
		addShadow(56,   46,   SHW_USE_TRANSFORMATION);						// Bear - top
		addShadow(457,  396);													// Bear - body
		addShadow(46,   42);													// Clockwreck Goblin - top
		addShadow(350,  219);													// Clockwreck Goblin - top
		addShadow(164,  74);													// Goblin Shredder - top
		addShadow(593,  318);													// Goblin Shredder - body
		addShadow(13,   10);													// Goblin Sapper - top
		addShadow(742,  536);													// Goblin Sapper - body
		addShadow(82,   84);													// Lava Spawn - top
		addShadow(419,  378);													// Lava Spawn - body
		addShadow(52,   50);													// Quilbeast - top
		addShadow(398,  403);													// Quilbeast - body
		addShadow(43,   42);													// Furbolg mage - top
		addShadow(282,  230);													// Furbolg mage - body
		addShadow(139,  84);													// Furbolg mage - top
		addShadow(287,  230);													// Furbolg mage - body
		addShadow(155,  96);													// Furbolg mage - top
		addShadow(335,  246);													// Furbolg mage - body
		addShadow(26,   16,   SHW_USE_TRANSFORMATION);						// Furbolg warrior - top
		addShadow(325,  272);													// Furbolg warrior - body
		addShadow(80,   48,   SHW_USE_TRANSFORMATION);						// Lightning Lizard - top
		addShadow(528,  485);													// Lightning Lizard - body
		addShadow(85,   93);													// Satyr - top
		addShadow(350,  311);													// Satyr - body
		addShadow(53,   44);													// Centaur archer - top
		addShadow(209,  222);													// Centaur archer - body
		addShadow(30,   29);													// Centaur warrior - top
		addShadow(233,  238);													// Centaur warrior - body
		addShadow(38,   34);													// Wildkin - top
		addShadow(617,  520);													// Wildkin - body
		addShadow(66,   53);													// Razormane - top
		addShadow(450,  349);													// Razormane warrior - body
		addShadow(434,  349);													// Razormane archer - body
		addShadow(40,   38);													// Draenei warrior - top
		addShadow(541,  431);													// Draenei warrior - body
		addShadow(577,  470);													// Draenei mage - body
		addShadow(78,   61);													// Felguard - top
		addShadow(529,  538);													// Felguard - body
		addShadow(56,   42);													// Diabolist - top
		addShadow(375,  379);													// Diabolist - body
		addShadow(183,  108);													// Diabolist - cloak
		addShadow(539,  509);													// Fel Beast - body
		addShadow(31,   23);													// Inferno Contraption - top
		addShadow(605,  596);													// Inferno Contraption - body
		addShadow(60,   30,   SHW_USE_TRANSFORMATION);						// Succubus - top
		addShadow(548,  586);													// Succubus - body
		addShadow(68,   65);													// Apprentice Wizard - top
		addShadow(315,  322);													// Apprentice Wizard - body
		addShadow(48,   39);													// Reject - top
		addShadow(290,  228);													// Reject - body
		addShadow(303,  283);													// Zombie - body
		addShadow(48,   40,   SHW_USE_TRANSFORMATION);						// Dragonspawn - top
		addShadow(571,  526);													// Dragonspawn - body
		addShadow(104,  110);													// Dragonspawn - tail
		addShadow(21,   36,   SHW_USE_TRANSFORMATION);						// Dragonspawn - weapon
		addShadow(60,   28);													// Faceless - top
		addShadow(545,  412);													// Faceless - body
		addShadow(22,   15);													// Centaur small - top
		addShadow(251,  252);													// Centaur small - body
		addShadow(18,   27,   SHW_USE_TRANSFORMATION);						// Centaur small - body
		addShadow(93,   78);													// Poisonous TreeAnt - top
		addShadow(282,  399);													// Poisonous TreeAnt - body
		addShadow(422,  265);													// War Golem
		addShadow(299,  172);													// Nerubian - body2
		addShadow(91,   74);													// Nerubian - body2 claws
		#pragma endregion

		#pragma region Misc
		/* Item */
		addShadow(178,  116,  SHW_USE_TRANSFORMATION);						// Book
		addShadow(76,   48,   SHW_USE_TRANSFORMATION);						// Treasure Box
		#pragma endregion

		#ifdef _DEBUG
		writeKeysToFile();
		#endif
	}
}