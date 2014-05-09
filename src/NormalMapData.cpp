#include "NormalMapHandler.h"

namespace NP {
	const ExceptionalMeshKeys g_exceptionalMeshes[MAX_EXCEPTIONAL_MESH_COUNT] = {
		/* 
		 * Format:
		 * NumVertices, PrimCount, SrcBlend, DestBlend, AlphaRef (0 is the wildcard here)
		 */
		{ 466, 295,  5, 0, 0 },			// Orc Watch Tower - body
		{ 384, 249,  5, 0, 0 },			// Orc Stronghold - body
		EMK_END(),
	};

	void InitTextureTable(TextureTable &texTable)
	{
		texTable.cleanup();
		/*
		 * Format: 
		 * Stride, NumVertices, PrimCount, Width, Height, Inverted, IsMask(optional), NormalAlphaRef(optional), TransplantAlphaRef(optional)
		 */
		texTable.addTextureEntry(32,  1053, 511,  256, 256, false);								// Human Construction Set
		//texTable.addTextureEntry(32,  20,   10,   256, 256, false, true, 192, 4);				// Human Farm - top
		texTable.addTextureEntry(32,  320,  153,  256, 256, false);								// Human Farm - body
		texTable.addTextureEntry(32,  8,    6,    256, 256, false);								// Human Townhall - base
		texTable.addTextureEntry(32,  18,   10,   512, 512, false, true, 192, 4);				// Human Townhall - top
		texTable.addTextureEntry(32,  454,  209,  512, 512, false);								// Human Townhall - body
		texTable.addTextureEntry(32,  37,   19,   512, 512, false, true, 192, 4);				// Human Keep - top
		texTable.addTextureEntry(32,  405,  200,  512, 512, false);								// Human Keep - body
		texTable.addTextureEntry(32,  177,  83,   512, 512, false, true, 192, 4);				// Human Castle - top
		texTable.addTextureEntry(32,  418,  352,  512, 512, false);								// Human Castle - body
		texTable.addTextureEntry(32,  90,   30,   256, 256, false);								// Human Castle - base
		//texTable.addTextureEntry(32,  52,   42,   256, 256, false, true, 192, 4);				// Human Altar - top (weird color)
		texTable.addTextureEntry(32,  359,  302,  256, 256, false);								// Human Altar - body
		texTable.addTextureEntry(32,  99,   46,   256, 256, false, true, 192, 4);				// Human Barracks - top
		texTable.addTextureEntry(32,  387,  209,  256, 256, false);								// Human Barracks - body
		texTable.addTextureEntry(32,  14,   8,    256, 256, false, true, 192, 4);				// Human Lumber Mill - top
		texTable.addTextureEntry(32,  386,  224,  256, 256, false);								// Human Lumber Mill - body
		texTable.addTextureEntry(32,  20,   28,   256, 256, false);								// Human Lumber Mill - base
		texTable.addTextureEntry(32,  22,   14,   256, 256, false, true, 192, 4);				// Human BlackSmith - top
		texTable.addTextureEntry(32,  605,  343,  256, 256, false);								// Human BlackSmith - body
		texTable.addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);				// Human Arcane Vault - top
		texTable.addTextureEntry(32,  85,   40,   256, 256, false);								// Human Arcane Vault - gem
		texTable.addTextureEntry(32,  96,   48,   256, 256, false);								// Human Arcane Vault - pole
		texTable.addTextureEntry(32,  500,  266,  256, 256, false);								// Human Arcane Vault - chain
		//texTable.addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);				// Human Arcane Sanctum - top
		texTable.addTextureEntry(32,  923,  578,  256, 256, false);								// Human Arcane Sanctum - body
		//texTable.addTextureEntry(32,  25,   17,   256, 256, false, true, 192, 4);				// Human Gryphon Aviary - top
		texTable.addTextureEntry(32,  414,  309,  256, 256, true);								// Human Gryphon Aviary - body
		//texTable.addTextureEntry(32,  20,   26,   256, 256, false, true, 192, 4);				// Human Workshop - top
		texTable.addTextureEntry(32,  310,  266,  256, 256, false);								// Human Workshop - body
		//texTable.addTextureEntry(32,  27,   15,   256, 128, true, true, 192, 4);				// Human Scout Tower - top
		texTable.addTextureEntry(32,  251,  149,  256, 128, true);								// Human Scout Tower - body
		//texTable.addTextureEntry(32,  216,  123,  256, 128, true, true, 192, 4);				// Human Arcane Tower - top (conflict)
		//texTable.addTextureEntry(32,  88,   56,   256, 128, true);							// Human Arcane Tower - body (conflict)
		texTable.addTextureEntry(32,  97,   48,   256, 128, true);								// Human Arcane Tower - tower
		//texTable.addTextureEntry(32,  51,   27,   256, 128, true, true, 192, 4);				// Human Guard Tower - top
		texTable.addTextureEntry(32,  216,  123,  256, 128, true);								// Human Guard Tower - body
		//texTable.addTextureEntry(32,  32,   20,   256, 128, true, true, 192, 4);				// Human Cannon Tower - top
		texTable.addTextureEntry(32,  300,  189,  256, 128, true);								// Human Cannon Tower - body

		texTable.addTextureEntry(32,  300,  252,  256, 256, false);								// Orc Construction Set - large fence
		texTable.addTextureEntry(32,  264,  228,  256, 256, false);								// Orc Construction Set - medium fence
		texTable.addTextureEntry(32,  198,  164,  256, 256, false);								// Orc Construction Set - small fence
		texTable.addTextureEntry(32,  64,   64,   256, 256, false);								// Orc Construction Set - small roof (conflict)
		texTable.addTextureEntry(32,  96,   96,   256, 256, false);								// Orc Construction Set - medium roof
		texTable.addTextureEntry(32,  36,   48,   256, 256, false);								// Orc Construction Set - medium pole
		texTable.addTextureEntry(32,  48,   72,   256, 256, false);								// Orc Construction Set - large stick
		//texTable.addTextureEntry(32,  48,   24,   256, 256, false);							// Orc Construction Set - large cover (conflict)
		texTable.addTextureEntry(32,  160,  104,  256, 256, true);								// Orc Structure - base
		texTable.addTextureEntry(32,  124,  80,   256, 256, false);								// Orc Structure Spike
		texTable.addTextureEntry(32,  192,  144,  128, 128, false);								// Orc Structure Barricade

		texTable.addTextureEntry(32,  191,  214,  256, 256, false, true, 192, 4);				// Orc Great Hall - top	
		texTable.addTextureEntry(32,  290,  164,  256, 256, false);								// Orc Great Hall - body
		texTable.addTextureEntry(32,  183,  188,  256, 256, false, true, 192, 4);				// Orc Stronghold - top
		texTable.addTextureEntry(32,  384,  249,  256, 256, false);								// Orc Stronghold - body
		texTable.addTextureEntry(32,  226,  149,  256, 256, false, true, 192, 4);				// Orc Fortress - top
		texTable.addTextureEntry(32,  516,  498,  256, 256, false);								// Orc Fortress - body
		texTable.addTextureEntry(32,  95,   59,   256, 256, false, true, 192, 4);				// Orc Altar - top
		texTable.addTextureEntry(32,  291,  264,  256, 256, false);								// Orc Altar - body
		texTable.addTextureEntry(32,  265,  206,  128, 128, false);								// Orc Burrow - body
		//texTable.addTextureEntry(32,  36,   28,   128, 128, false, true, 192, 4);				// Orc Burrow - top
		texTable.addTextureEntry(32,  309,  317,  256, 256, false);								// Orc War Mill - body
		texTable.addTextureEntry(32,  125,  81,   256, 256, false);								// Orc War Mill - saw
		texTable.addTextureEntry(32,  42,   48,   256, 256, false, true, 192, 4);				// Orc War Mill - top
		texTable.addTextureEntry(32,  466,  295,  256, 256, false);								// Orc Watch Tower - body
		texTable.addTextureEntry(32,  17,   12,   256, 256, false, true, 192, 4);				// Orc Watch Tower - top
		texTable.addTextureEntry(32,  255,  195,  256, 256, false);								// Orc Barracks - body
		texTable.addTextureEntry(32,  73,   56,   256, 256, false, true, 192, 4);				// Orc Barracks - top
		//texTable.addTextureEntry(32,  19,   20,   256, 256, false);							// Orc Voodoo Lounge - funnel
		texTable.addTextureEntry(32,  66,   54,   256, 256, false);								// Orc Voodoo Lounge - tusk
		texTable.addTextureEntry(32,  145,  78,   256, 256, false);								// Orc Voodoo Lounge - body
		texTable.addTextureEntry(32,  211,  207,  256, 256, false, true, 192, 4);				// Orc Voodoo Lounge - top
		texTable.addTextureEntry(32,  327,  260,  256, 256, true);								// Orc Beastiary - body
		texTable.addTextureEntry(32,  69,   92,   256, 256, false, true, 192, 4);				// Orc Beastiary - top
		texTable.addTextureEntry(32,  414,  295,  256, 256, true);								// Orc Spirit Lounge - body
		texTable.addTextureEntry(32,  52,   26,   256, 256, true,  true, 192, 4);				// Orc Spirit Lounge - top
		texTable.addTextureEntry(32,  323,  221,  256, 256, false);								// Orc Tauren Totem - body
		texTable.addTextureEntry(32,  57,   67,   256, 256, false, true, 192, 4);				// Orc Tauren Totem - top

		//texTable.addTextureEntry(32,  294,  211,  64,  128, false);							// Undead Construction Set [trouble display]
		//texTable.addTextureEntry(32,  52,   32,   256, 256, false, true, 192, 4);				// Undead Necropolis - top [trouble display]
		texTable.addTextureEntry(32,  350,  246,  256, 256, false);								// Undead Necropolis - body
		texTable.addTextureEntry(32,  578,  294,  256, 256, false);								// Undead Haunted Gold Mine - body
		texTable.addTextureEntry(32,  291,  249,  256, 256, false);								// Undead Haunted Gold Mine - mine
		//texTable.addTextureEntry(32,  16,   8,    256, 256, false, true, 192, 4);				// Undead Ziggurat - top [conflict]
		texTable.addTextureEntry(32,  425,  283,  256, 256, false);								// Undead Ziggurat - body
		//texTable.addTextureEntry(32,  106,  53,   256, 256, false, true, 192, 4);				// Undead Altar of Darkness - top [trouble display]
		texTable.addTextureEntry(32,  468,  305,  256, 256, false);								// Undead Altar of Darkness - body
		texTable.addTextureEntry(32,  39,   23,   256, 256, false, true, 192, 4);				// Undead Graveyard - top
		texTable.addTextureEntry(32,  445,  336,  256, 256, false);								// Undead Graveyard - body
		texTable.addTextureEntry(32,  504,  437,  256, 256, false);								// Undead Graveyard - corpses
		texTable.addTextureEntry(32,  198,  191,  256, 256, false);								// Undead Graveyard - poles
		texTable.addTextureEntry(32,  80,   30,   256, 256, false, true, 192, 4);				// Undead Crypt - top
		texTable.addTextureEntry(32,  769,  443,  256, 256, false);								// Undead Crypt - body
		//texTable.addTextureEntry(32,  36,   18,   256, 256, false);							// Undead Hall of Dead - water [conflict]
		texTable.addTextureEntry(32,  580,  358,  256, 256, false);								// Undead Hall of Dead - body
		//texTable.addTextureEntry(32,  42,   20,   256, 256, false, true, 192, 4);				// Undead Tomb of Relics - top [trouble display]
		texTable.addTextureEntry(32,  578,  342,  256, 256, false);								// Undead Tomb of Relics - body
		texTable.addTextureEntry(32,  614,  492,  256, 256, false);								// Undead Black Citadel - body
		texTable.addTextureEntry(32,  114,  67,   256, 256, false, true, 192, 4);				// Undead Slaughterhouse - top
		texTable.addTextureEntry(32,  528,  280,  256, 256, false);								// Undead Slaughterhouse - body
		texTable.addTextureEntry(32,  58,   30,   256, 256, false, true, 192, 4);				// Undead Temple of the Damned - top
		texTable.addTextureEntry(32,  569,  486,  256, 256, false);								// Undead Temple of the Damned - body
		texTable.addTextureEntry(32,  31,   18,   256, 256, false, true, 192, 4);				// Undead Sacrificial Pit - top [conflict]
		texTable.addTextureEntry(32,  364,  311,  256, 256, false);								// Undead Sacrificial Pit - body
		texTable.addTextureEntry(32,  44,   22,   256, 256, false, true, 192, 4);				// Undead Boneyard - top
		texTable.addTextureEntry(32,  582,  436,  256, 256, false);								// Undead Boneyard - body

		texTable.addTextureEntry(32,  88,   60,   512, 256, false);								// NightElf Base - root
		texTable.addTextureEntry(32,  247,  162,  256, 64,  false);								// NightElf Base - lv3 root
		texTable.addTextureEntry(32,  165,  132,  512, 256, false);								// NightElf Base - leaves
		texTable.addTextureEntry(32,  832,  680,  512, 256, true);								// NightElf Base - body
		texTable.addTextureEntry(32,  24,   18,   512, 256, false, true, 192, 4);				// NightElf Base - top
		texTable.addTextureEntry(32,  81,   72,   128, 128, false);								// NightElf Entangled Gold Mine - leaves
		texTable.addTextureEntry(32,  374,  256,  256, 64,  false);								// NightElf Entangled Gold Mine - roots
		texTable.addTextureEntry(32,  421,  267,  256, 256, false);								// NightElf Chinaera Roost - body
		texTable.addTextureEntry(32,  54,   42,   256, 256, false, true, 192, 4);				// NightElf Chinaera Roost - top
		texTable.addTextureEntry(32,  54,   28,   256, 256, false, true, 192, 4);				// NightElf Chinaera Roost - base
		texTable.addTextureEntry(32,  422,  259,  256, 256, false);								// NightElf Moon Well - body
		//texTable.addTextureEntry(32,  16,   8,    256, 256, false, true, 192, 4);				// NightElf Moon Well - top [conflict]
		texTable.addTextureEntry(32,  609,  360,  256, 256, true);								// NightElf Altar of Elders - body
		//texTable.addTextureEntry(32,  136,  88,   256, 256, true, true, 192, 4);				// NightElf Altar of Elders - top [trouble display]
		texTable.addTextureEntry(32,  495,  285,  256, 256, true);								// NightElf Hunter's Hall - body
		texTable.addTextureEntry(32,  60,   30,   256, 256, true);								// NightElf Hunter's Hall - base [conflict]
		texTable.addTextureEntry(32,  80,   48,   256, 256, false, true, 192, 4);				// NightElf Hunter's Hall - top [conflict]
		texTable.addTextureEntry(32,  572,  464,  256, 256, false);								// NightElf Acient of War - body
		texTable.addTextureEntry(32,  49,   56,   256, 256, false);								// NightElf Acient of War - body2
		texTable.addTextureEntry(32,  316,  230,  256, 128, false);								// NightElf Acient of War - roots
		texTable.addTextureEntry(32,  185,  176,  256, 256, false);								// NightElf Acient of War - feet
		texTable.addTextureEntry(32,  55,   36,   256, 256, true, true, 192, 4);				// NightElf Acient of War - top
		texTable.addTextureEntry(32,  594,  642,  512, 512, false);								// NightElf Acient of Wonders - body
		//texTable.addTextureEntry(32,  509,  472,  512, 512, false, true, 192, 4);				// NightElf Acient of Wonders - portrait
		texTable.addTextureEntry(32,  65,   33,   512, 512, false);								// NightElf Acient of Wonders - leaves
		texTable.addTextureEntry(32,  74,   74,   512, 512, true);								// NightElf Acient of Wonders - feet
		texTable.addTextureEntry(32,  71,   76,   512, 512, true, true, 192, 4);				// NightElf Acient of Wonders - top
		texTable.addTextureEntry(32,  617,  474,  256, 256, false);								// NightElf Acient of Wind - body
		texTable.addTextureEntry(32,  14,   12,   256, 256, false);								// NightElf Acient of Wind - leaves
		texTable.addTextureEntry(32,  169,  113,  256, 256, false);								// NightElf Acient of Wind - feets
		texTable.addTextureEntry(32,  217,  139,  256, 128, false);								// NightElf Acient of Wind - roots
		texTable.addTextureEntry(32,  48,   32,   256, 256, false, true, 192, 4);				// NightElf Acient of Wind - top
		texTable.addTextureEntry(32,  718,  543,  512, 256, true);								// NightElf Acient of Lore - body
		texTable.addTextureEntry(32,  245,  161,  256, 128, false);								// NightElf Acient of Lore - roots
		texTable.addTextureEntry(32,  98,   74,   512, 256, true);								// NightElf Acient of Lore - feet
		texTable.addTextureEntry(32,  15,   12,   512, 256, true);								// NightElf Acient of Lore - leaves
		texTable.addTextureEntry(32,  28,   29,   512, 256, true, true, 192, 4);				// NightElf Acient of Lore - top
		texTable.addTextureEntry(32,  312,  257,  256, 256, false);								// NightElf Acient Protector - body
		texTable.addTextureEntry(32,  88,   84,   256, 256, false);								// NightElf Acient Protector - roots
		texTable.addTextureEntry(32,  104,  70,   256, 256, false);								// NightElf Acient Protector - roots2
		texTable.addTextureEntry(32,  136,  92,   256, 256, false);								// NightElf Acient Protector - feets
		texTable.addTextureEntry(32,  115,  64,   256, 256, false);								// NightElf Acient Protector - leaves
		texTable.addTextureEntry(32,  92,   87,   256, 256, false, true, 192, 4);				// NightElf Acient Protector - top

		//texTable.addTextureEntry(32,  12,   6,    256, 256, false);							// Nage Temple of Tides - pearls [conflict]
		//texTable.addTextureEntry(32,  24,   12,   256, 256, false);							// Nage Temple of Tides - pearls2 [conflict]
		texTable.addTextureEntry(32,  22,   20,   256, 256, false);								// Nage Temple of Tides - body
		texTable.addTextureEntry(32,  114,  114,  256, 256, false);								// Nage Temple of Tides - dragon
		texTable.addTextureEntry(32,  194,  252,  256, 256, false);								// Nage Temple of Tides - pole
		texTable.addTextureEntry(32,  86,   90,   256, 256, false);								// Nage Temple of Tides - moon
		texTable.addTextureEntry(32,  201,  112,  256, 256, false, true, 192, 4);				// Nage Temple of Tides - top
		///texTable.addTextureEntry(32,  24,   24,   256, 256, false);							// Nage Coral Bed - coral [conflict]
		texTable.addTextureEntry(32,  402,  359,  256, 256, false);								// Nage Coral Bed - body
		texTable.addTextureEntry(32,  34,   27,   256, 256, false, true, 192, 4);				// Nage Coral Bed - top
		texTable.addTextureEntry(32,  698,  706,  256, 256, true, true, 192, 4);				// Nage Amphibian Bivouac - top
		texTable.addTextureEntry(32,  13,   12,   32,  32,  false);								// Nage Tidal Guardian - water
		texTable.addTextureEntry(32,  269,  277,  256, 256, false);								// Nage Tidal Guardian - body
		texTable.addTextureEntry(32,  346,  384,  256, 256, false);								// Nage Tidal Guardian - head
		texTable.addTextureEntry(32,  72,   72,   256, 256, false, true, 192, 4);				// Nage Tidal Guardian - top

		texTable.addTextureEntry(32,  180,  94,   256, 256, true);								// IceTroll Barracks - body [messy]
		texTable.addTextureEntry(32,  356,  182,  256, 256, false);								// IceTroll Barracks - roof
		//texTable.addTextureEntry(32,  80,    32,  256, 256, false, true, 192, 4);				// IceTroll Barracks - tusks [display issue]
		texTable.addTextureEntry(32,  128,  68,   256, 256, false, true, 192, 4);				// IceTroll Barracks - top
		texTable.addTextureEntry(32,  20,   23,   256, 256, false);								// IceTroll Altar - skull
		texTable.addTextureEntry(32,  70,   75,   256, 256, false);								// IceTroll Altar - skull2
		texTable.addTextureEntry(32,  70,   70,   256, 256, false);								// IceTroll Altar - stair
		texTable.addTextureEntry(32,  20,   16,   256, 256, false);								// IceTroll Altar - body
		texTable.addTextureEntry(32,  177,  104,  256, 256, false);								// IceTroll Altar - water
		texTable.addTextureEntry(32,  231,  231,  256, 256, false);								// IceTroll Altar - thorns
		texTable.addTextureEntry(32,  176,  52,   256, 256, false);								// IceTroll Altar - torches
		texTable.addTextureEntry(32,  286,  336,  256, 256, false);								// IceTroll Altar - dragon
		texTable.addTextureEntry(32,  28,   16,   256, 256, false, true, 192, 4);				// IceTroll Altar - top1
		texTable.addTextureEntry(32,  94,   68,   256, 256, false, true, 192, 4);				// IceTroll Altar - top2
		texTable.addTextureEntry(32,  598,  496,  256, 256, false);								// IceTroll Dragon Roost
		texTable.addTextureEntry(32,  120,  126,  256, 256, false, true, 192, 4);				// IceTroll Igloo - tusks
		texTable.addTextureEntry(32,  161,  175,  256, 256, false, true, 192, 4);				// IceTroll Igloo - top
		texTable.addTextureEntry(32,  424,  350,  256, 256, false);								// IceTroll War Mill - body
		texTable.addTextureEntry(32,  22,   17,   256, 256, true);								// IceTroll War Mill - top

		texTable.addTextureEntry(32,  271,  239,  256, 256, false);								// Gold Mine - mine
		texTable.addTextureEntry(32,  84,   51,   64,  64,  false);								// Gold Mine - gold
		texTable.addTextureEntry(32,  123,  60,   256, 256, false);								// Gold Mine - base
		texTable.addTextureEntry(32,  132,  68,   256, 64,  false, true, 192, 4);				// Goblin Merchant - top
		texTable.addTextureEntry(32,  474,  274,  256, 256, false);								// Goblin Merchant - body
		texTable.addTextureEntry(32,  547,  442,  256, 256, false);								// Tarven
		texTable.addTextureEntry(32,  132,  48,   24,  64,  false, true, 192, 4);				// Tarven - top
		texTable.addTextureEntry(32,  331,  346,  512, 256, false);								// Fountain of Health
		texTable.addTextureEntry(32,  491,  348,  256, 256, false);								// Goblin Laboratory
		texTable.addTextureEntry(32,  571,  394,  256, 256, false);								// Mercenary Camp
		texTable.addTextureEntry(32,  407,  347,  256, 256, false);								// Marketplace - body
		texTable.addTextureEntry(32,  94,   46,   256, 256, false, true, 192, 4);				// Marketplace - top
		texTable.addTextureEntry(32,  305,  222,  256, 256, false);								// Way Gate - body
		texTable.addTextureEntry(32,  58,   44,   256, 256, false, true, 192, 4);				// Way Gate - top

		texTable.addTextureEntry(32,  328,  316,  256, 256, false);								// Swordsman Statue
		texTable.addTextureEntry(32,  178,  116,  256, 256, false);								// Item book
		texTable.addTextureEntry(32,  76,   48,   256, 256, false);								// Item treasure box

		//texTable.addTextureEntry(32,  36,   28,  256, 256, false);								// Tree
		//texTable.addTextureEntry(32,  247,  336, 256, 256, false);								// Test Subject

		//texTable.addTextureEntry(32,  1065, 1143,256, 256, false);								// Main Screen
		// TODO: add more...
	}
}