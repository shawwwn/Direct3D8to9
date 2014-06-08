#include "../NormalMapHandler.h"
//#include "NormalTable.h"

namespace NP {
	const NormalExceptionKey g_exceptionalMeshes[MAX_EXCEPTIONAL_MESH_COUNT] = {
		/* 
		 * Format:
		 * NumVertices, PrimCount, SrcBlend, DestBlend, AlphaRef (0 is the wildcard here)
		 */
		{ 466, 295,  5, 0, 0 },			// Orc Watch Tower - body
		{ 384, 249,  5, 0, 0 },			// Orc Stronghold - body
		EMK_END(),
	};

	void NormalTable::InitNormalTable()
	{
		cleanup();
		/*
		 * Format: 
		 * Stride, NumVertices, PrimCount, Width, Height, Inverted, IsMask(optional), NormalAlphaRef(optional), TransplantAlphaRef(optional)
		 */
		#pragma region Human
		addTextureEntry(32,  1053, 511,  256, 256, false);								// Human Construction Set
		//addTextureEntry(32,  20,   10,   256, 256, false, true, 192, 4);				// Human Farm - top
		addTextureEntry(32,  320,  153,  256, 256, false);								// Human Farm - body
		addTextureEntry(32,  8,    6,    256, 256, false);								// Human Townhall - base
		addTextureEntry(32,  18,   10,   512, 512, false, true, 192, 4);				// Human Townhall - top
		addTextureEntry(32,  454,  209,  512, 512, false);								// Human Townhall - body
		addTextureEntry(32,  37,   19,   512, 512, false, true, 192, 4);				// Human Keep - top
		addTextureEntry(32,  405,  200,  512, 512, false);								// Human Keep - body
		addTextureEntry(32,  177,  83,   512, 512, false, true, 192, 4);				// Human Castle - top
		addTextureEntry(32,  418,  352,  512, 512, false);								// Human Castle - body
		addTextureEntry(32,  90,   30,   256, 256, false);								// Human Castle - base
		//addTextureEntry(32,  52,   42,   256, 256, false, true, 192, 4);				// Human Altar - top (weird color)
		addTextureEntry(32,  359,  302,  256, 256, false);								// Human Altar - body
		addTextureEntry(32,  99,   46,   256, 256, false, true, 192, 4);				// Human Barracks - top
		addTextureEntry(32,  387,  209,  256, 256, false);								// Human Barracks - body
		addTextureEntry(32,  14,   8,    256, 256, false, true, 192, 4);				// Human Lumber Mill - top
		addTextureEntry(32,  386,  224,  256, 256, false);								// Human Lumber Mill - body
		addTextureEntry(32,  20,   28,   256, 256, false);								// Human Lumber Mill - base
		addTextureEntry(32,  22,   14,   256, 256, false, true, 192, 4);				// Human BlackSmith - top
		addTextureEntry(32,  605,  343,  256, 256, false);								// Human BlackSmith - body
		addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);				// Human Arcane Vault - top
		addTextureEntry(32,  85,   40,   256, 256, false);								// Human Arcane Vault - gem
		addTextureEntry(32,  96,   48,   256, 256, false);								// Human Arcane Vault - pole
		addTextureEntry(32,  500,  266,  256, 256, false);								// Human Arcane Vault - chain
		//addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);				// Human Arcane Sanctum - top
		addTextureEntry(32,  923,  578,  256, 256, false);								// Human Arcane Sanctum - body
		//addTextureEntry(32,  25,   17,   256, 256, false, true, 192, 4);				// Human Gryphon Aviary - top
		addTextureEntry(32,  414,  309,  256, 256, true);								// Human Gryphon Aviary - body
		//addTextureEntry(32,  20,   26,   256, 256, false, true, 192, 4);				// Human Workshop - top
		addTextureEntry(32,  310,  266,  256, 256, false);								// Human Workshop - body
		//addTextureEntry(32,  27,   15,   256, 128, true, true, 192, 4);				// Human Scout Tower - top
		addTextureEntry(32,  251,  149,  256, 128, true);								// Human Scout Tower - body
		//addTextureEntry(32,  216,  123,  256, 128, true, true, 192, 4);				// Human Arcane Tower - top (conflict)
		//addTextureEntry(32,  88,   56,   256, 128, true);							// Human Arcane Tower - body (conflict)
		addTextureEntry(32,  97,   48,   256, 128, true);								// Human Arcane Tower - tower
		//addTextureEntry(32,  51,   27,   256, 128, true, true, 192, 4);				// Human Guard Tower - top
		addTextureEntry(32,  216,  123,  256, 128, true);								// Human Guard Tower - body
		//addTextureEntry(32,  32,   20,   256, 128, true, true, 192, 4);				// Human Cannon Tower - top
		addTextureEntry(32,  300,  189,  256, 128, true);								// Human Cannon Tower - body
		#pragma endregion

		#pragma region Orc
		addTextureEntry(32,  300,  252,  256, 256, false);								// Orc Construction Set - large fence
		addTextureEntry(32,  264,  228,  256, 256, false);								// Orc Construction Set - medium fence
		addTextureEntry(32,  198,  164,  256, 256, false);								// Orc Construction Set - small fence
		addTextureEntry(32,  64,   64,   256, 256, false);								// Orc Construction Set - small roof (conflict)
		addTextureEntry(32,  96,   96,   256, 256, false);								// Orc Construction Set - medium roof
		addTextureEntry(32,  36,   48,   256, 256, false);								// Orc Construction Set - medium pole
		addTextureEntry(32,  48,   72,   256, 256, false);								// Orc Construction Set - large stick
		//addTextureEntry(32,  48,   24,   256, 256, false);							// Orc Construction Set - large cover (conflict)
		addTextureEntry(32,  160,  104,  256, 256, true);								// Orc Structure - base
		addTextureEntry(32,  124,  80,   256, 256, false);								// Orc Structure Spike
		addTextureEntry(32,  192,  144,  128, 128, false);								// Orc Structure Barricade

		addTextureEntry(32,  191,  214,  256, 256, false, true, 192, 4);				// Orc Great Hall - top	
		addTextureEntry(32,  290,  164,  256, 256, false);								// Orc Great Hall - body
		addTextureEntry(32,  183,  188,  256, 256, false, true, 192, 4);				// Orc Stronghold - top
		addTextureEntry(32,  384,  249,  256, 256, false);								// Orc Stronghold - body
		addTextureEntry(32,  226,  149,  256, 256, false, true, 192, 4);				// Orc Fortress - top
		addTextureEntry(32,  516,  498,  256, 256, false);								// Orc Fortress - body
		addTextureEntry(32,  95,   59,   256, 256, false, true, 192, 4);				// Orc Altar - top
		addTextureEntry(32,  291,  264,  256, 256, false);								// Orc Altar - body
		addTextureEntry(32,  265,  206,  128, 128, false);								// Orc Burrow - body
		//addTextureEntry(32,  36,   28,   128, 128, false, true, 192, 4);				// Orc Burrow - top
		addTextureEntry(32,  309,  317,  256, 256, false);								// Orc War Mill - body
		addTextureEntry(32,  125,  81,   256, 256, false);								// Orc War Mill - saw
		addTextureEntry(32,  42,   48,   256, 256, false, true, 192, 4);				// Orc War Mill - top
		addTextureEntry(32,  466,  295,  256, 256, false);								// Orc Watch Tower - body
		addTextureEntry(32,  17,   12,   256, 256, false, true, 192, 4);				// Orc Watch Tower - top
		addTextureEntry(32,  255,  195,  256, 256, false);								// Orc Barracks - body
		addTextureEntry(32,  73,   56,   256, 256, false, true, 192, 4);				// Orc Barracks - top
		//addTextureEntry(32,  19,   20,   256, 256, false);							// Orc Voodoo Lounge - funnel
		addTextureEntry(32,  66,   54,   256, 256, false);								// Orc Voodoo Lounge - tusk
		addTextureEntry(32,  145,  78,   256, 256, false);								// Orc Voodoo Lounge - body
		addTextureEntry(32,  211,  207,  256, 256, false, true, 192, 4);				// Orc Voodoo Lounge - top
		addTextureEntry(32,  327,  260,  256, 256, true);								// Orc Beastiary - body
		addTextureEntry(32,  69,   92,   256, 256, false, true, 192, 4);				// Orc Beastiary - top
		addTextureEntry(32,  414,  295,  256, 256, true);								// Orc Spirit Lounge - body
		addTextureEntry(32,  52,   26,   256, 256, true,  true, 192, 4);				// Orc Spirit Lounge - top
		addTextureEntry(32,  323,  221,  256, 256, false);								// Orc Tauren Totem - body
		addTextureEntry(32,  57,   67,   256, 256, false, true, 192, 4);				// Orc Tauren Totem - top
		#pragma endregion

		#pragma region Undead
		//addTextureEntry(32,  294,  211,  64,  128, false);							// Undead Construction Set [trouble display]
		//addTextureEntry(32,  52,   32,   256, 256, false, true, 192, 4);				// Undead Necropolis - top [trouble display]
		addTextureEntry(32,  350,  246,  256, 256, false);								// Undead Necropolis - body
		addTextureEntry(32,  578,  294,  256, 256, false);								// Undead Haunted Gold Mine - body
		addTextureEntry(32,  291,  249,  256, 256, false);								// Undead Haunted Gold Mine - mine
		//addTextureEntry(32,  16,   8,    256, 256, false, true, 192, 4);				// Undead Ziggurat - top [conflict]
		addTextureEntry(32,  425,  283,  256, 256, false);								// Undead Ziggurat - body
		//addTextureEntry(32,  106,  53,   256, 256, false, true, 192, 4);				// Undead Altar of Darkness - top [trouble display]
		addTextureEntry(32,  468,  305,  256, 256, false);								// Undead Altar of Darkness - body
		addTextureEntry(32,  39,   23,   256, 256, false, true, 192, 4);				// Undead Graveyard - top
		addTextureEntry(32,  445,  336,  256, 256, false);								// Undead Graveyard - body
		addTextureEntry(32,  504,  437,  256, 256, false);								// Undead Graveyard - corpses
		addTextureEntry(32,  198,  191,  256, 256, false);								// Undead Graveyard - poles
		addTextureEntry(32,  80,   30,   256, 256, false, true, 192, 4);				// Undead Crypt - top
		addTextureEntry(32,  769,  443,  256, 256, false);								// Undead Crypt - body
		//addTextureEntry(32,  36,   18,   256, 256, false);							// Undead Hall of Dead - water [conflict]
		addTextureEntry(32,  580,  358,  256, 256, false);								// Undead Hall of Dead - body
		//addTextureEntry(32,  42,   20,   256, 256, false, true, 192, 4);				// Undead Tomb of Relics - top [trouble display]
		addTextureEntry(32,  578,  342,  256, 256, false);								// Undead Tomb of Relics - body
		addTextureEntry(32,  614,  492,  256, 256, false);								// Undead Black Citadel - body
		addTextureEntry(32,  114,  67,   256, 256, false, true, 192, 4);				// Undead Slaughterhouse - top
		addTextureEntry(32,  528,  280,  256, 256, false);								// Undead Slaughterhouse - body
		addTextureEntry(32,  58,   30,   256, 256, false, true, 192, 4);				// Undead Temple of the Damned - top
		addTextureEntry(32,  569,  486,  256, 256, false);								// Undead Temple of the Damned - body
		addTextureEntry(32,  31,   18,   256, 256, false, true, 192, 4);				// Undead Sacrificial Pit - top [conflict]
		addTextureEntry(32,  364,  311,  256, 256, false);								// Undead Sacrificial Pit - body
		addTextureEntry(32,  44,   22,   256, 256, false, true, 192, 4);				// Undead Boneyard - top
		addTextureEntry(32,  582,  436,  256, 256, false);								// Undead Boneyard - body
		#pragma endregion

		#pragma region NightElf
		addTextureEntry(32,  229,  143,  256, 256, false);								// NightElf Construction Set - Medium
		addTextureEntry(32,  431,  234,  256, 256, false);								// NightElf Construction Set - Large
		addTextureEntry(32,  424,  231,  256, 256, false);								// NightElf Construction Set - Large
		addTextureEntry(32,  94,   50,   256, 256, false);								// NightElf Construction Set - rocks
		addTextureEntry(32,  17,   24,   256, 256, false);								// NightElf Construction Set - base
		addTextureEntry(32,  222,  180,  256, 64,  true);								// NightElf Construction Set - cirrus
		addTextureEntry(32,  88,   60,   512, 256, false);								// NightElf Base - root
		addTextureEntry(32,  247,  162,  256, 64,  false);								// NightElf Base - lv3 root
		addTextureEntry(32,  165,  132,  512, 256, false);								// NightElf Base - leaves
		addTextureEntry(32,  832,  680,  512, 256, true);								// NightElf Base - body
		addTextureEntry(32,  24,   18,   512, 256, false, true, 192, 4);				// NightElf Base - top
		addTextureEntry(32,  81,   72,   128, 128, false);								// NightElf Entangled Gold Mine - leaves
		addTextureEntry(32,  374,  256,  256, 64,  false);								// NightElf Entangled Gold Mine - roots
		addTextureEntry(32,  421,  267,  256, 256, false);								// NightElf Chinaera Roost - body
		addTextureEntry(32,  54,   42,   256, 256, false, true, 192, 4);				// NightElf Chinaera Roost - top
		addTextureEntry(32,  54,   28,   256, 256, false, true, 192, 4);				// NightElf Chinaera Roost - base
		addTextureEntry(32,  422,  259,  256, 256, false);								// NightElf Moon Well - body
		//addTextureEntry(32,  16,   8,    256, 256, false, true, 192, 4);				// NightElf Moon Well - top [conflict]
		addTextureEntry(32,  609,  360,  256, 256, true);								// NightElf Altar of Elders - body
		//addTextureEntry(32,  136,  88,   256, 256, true, true, 192, 4);				// NightElf Altar of Elders - top [trouble display]
		addTextureEntry(32,  495,  285,  256, 256, true);								// NightElf Hunter's Hall - body
		addTextureEntry(32,  60,   30,   256, 256, true);								// NightElf Hunter's Hall - base [conflict]
		addTextureEntry(32,  80,   48,   256, 256, false, true, 192, 4);				// NightElf Hunter's Hall - top [conflict]
		addTextureEntry(32,  572,  464,  256, 256, false);								// NightElf Acient of War - body
		addTextureEntry(32,  49,   56,   256, 256, false);								// NightElf Acient of War - body2
		addTextureEntry(32,  316,  230,  256, 128, false);								// NightElf Acient of War - roots
		addTextureEntry(32,  185,  176,  256, 256, false);								// NightElf Acient of War - feet
		addTextureEntry(32,  55,   36,   256, 256, true, true, 192, 4);				// NightElf Acient of War - top
		addTextureEntry(32,  594,  642,  512, 512, false);								// NightElf Acient of Wonders - body
		//addTextureEntry(32,  509,  472,  512, 512, false, true, 192, 4);				// NightElf Acient of Wonders - portrait
		addTextureEntry(32,  65,   33,   512, 512, false);								// NightElf Acient of Wonders - leaves
		addTextureEntry(32,  74,   74,   512, 512, true);								// NightElf Acient of Wonders - feet
		addTextureEntry(32,  71,   76,   512, 512, true, true, 192, 4);				// NightElf Acient of Wonders - top
		addTextureEntry(32,  617,  474,  256, 256, false);								// NightElf Acient of Wind - body
		addTextureEntry(32,  14,   12,   256, 256, false);								// NightElf Acient of Wind - leaves
		addTextureEntry(32,  169,  113,  256, 256, false);								// NightElf Acient of Wind - feets
		addTextureEntry(32,  217,  139,  256, 128, false);								// NightElf Acient of Wind - roots
		addTextureEntry(32,  48,   32,   256, 256, false, true, 192, 4);				// NightElf Acient of Wind - top
		addTextureEntry(32,  718,  543,  512, 256, true);								// NightElf Acient of Lore - body
		addTextureEntry(32,  245,  161,  256, 128, false);								// NightElf Acient of Lore - roots
		addTextureEntry(32,  98,   74,   512, 256, true);								// NightElf Acient of Lore - feet
		addTextureEntry(32,  15,   12,   512, 256, true);								// NightElf Acient of Lore - leaves
		addTextureEntry(32,  28,   29,   512, 256, true, true, 192, 4);				// NightElf Acient of Lore - top
		addTextureEntry(32,  312,  257,  256, 256, false);								// NightElf Acient Protector - body
		addTextureEntry(32,  88,   84,   256, 256, false);								// NightElf Acient Protector - roots
		addTextureEntry(32,  104,  70,   256, 256, false);								// NightElf Acient Protector - roots2
		addTextureEntry(32,  136,  92,   256, 256, false);								// NightElf Acient Protector - feets
		addTextureEntry(32,  115,  64,   256, 256, false);								// NightElf Acient Protector - leaves
		addTextureEntry(32,  92,   87,   256, 256, false, true, 192, 4);				// NightElf Acient Protector - top
		#pragma endregion

		#pragma region Naga
		addTextureEntry(32,  61,   108,  256, 256, true);								// Nage Construction Set - base
		//addTextureEntry(32,  173,  186,  32,  32,  true);							// Nage Construction Set - water big
		//addTextureEntry(32,  246,  222,  32,  32,  true);							// Nage Construction Set - water big tentacle
		//addTextureEntry(32,  168,  165,  32,  32,  true);							// Nage Construction Set - water small
		//addTextureEntry(32,  229,  198,  32,  32,  true);							// Nage Construction Set - water small tentacle
		//addTextureEntry(32,  12,   6,    256, 256, false);							// Nage Temple of Tides - pearls [conflict]
		//addTextureEntry(32,  24,   12,   256, 256, false);							// Nage Temple of Tides - pearls2 [conflict]
		addTextureEntry(32,  22,   20,   256, 256, false);								// Nage Temple of Tides - body
		addTextureEntry(32,  114,  114,  256, 256, false);								// Nage Temple of Tides - dragon
		addTextureEntry(32,  194,  252,  256, 256, false);								// Nage Temple of Tides - pole
		addTextureEntry(32,  86,   90,   256, 256, true);								// Nage Temple of Tides - moon
		addTextureEntry(32,  201,  112,  256, 256, false, true, 192, 4);				// Nage Temple of Tides - top
		addTextureEntry(32,  501,  464,  256, 256, false, true, 192, 4);				// Nage Temple of Tides - lever
		addTextureEntry(32,  91,   48,   256, 256, false);								// Nage Temple of Tides - center part
		///addTextureEntry(32,  24,   24,   256, 256, false);							// Nage Coral Bed - coral [conflict]
		addTextureEntry(32,  402,  359,  256, 256, false);								// Nage Coral Bed - body
		addTextureEntry(32,  34,   27,   256, 256, false, true, 192, 4);				// Nage Coral Bed - top
		addTextureEntry(32,  698,  706,  256, 256, true, true, 192, 4);				// Nage Amphibian Bivouac - top
		addTextureEntry(32,  13,   12,   32,  32,  false);								// Nage Tidal Guardian - water
		addTextureEntry(32,  269,  277,  256, 256, false);								// Nage Tidal Guardian - body
		addTextureEntry(32,  346,  384,  256, 256, false);								// Nage Tidal Guardian - head
		addTextureEntry(32,  72,   72,   256, 256, false, true, 192, 4);				// Nage Tidal Guardian - top
		addTextureEntry(32,  80,   42,   256, 256, false);								// Nage Murloc Camp - body
		addTextureEntry(32,  36,   32,   128, 128, false);								// Nage Murloc Camp - shell [conflict]
		//addTextureEntry(32,  28,   46,   256, 256, false);							// Nage Murloc Camp - anchor [display issue]
		addTextureEntry(32,  23,   20,   64,  64,  false);								// Nage Murloc Camp - fish
		//addTextureEntry(32,  8,    7,    64,  64,  false);							// Nage Murloc Camp - water [conflict]
		addTextureEntry(32,  333,  186,  256, 256, false, true, 192, 4);				// Nage Murloc Camp - top
		//addTextureEntry(32,  13,   20,   256, 256, false, true, 192, 4);				// Nage Murloc Camp - tusk [display issue]
		addTextureEntry(32,  23,   18,   256, 256, true, true, 192, 4);				// Nage Altar - top
		addTextureEntry(32,  682,  482,  256, 256, true);								// Nage Altar - body
		addTextureEntry(32,  300,  349,  256, 256, true);								// Nage Altar - statue
		addTextureEntry(32,  27,   9,    256, 256, false, true, 192, 4);				// Nage Spawning Ground - top
		addTextureEntry(32,  959,  735,  256, 256, false);								// Nage Spawning Ground - body
		addTextureEntry(32,  195,  126,  256, 256, true, true, 192, 4);				// Nage Temple of Azarah - top
		addTextureEntry(32,  1092, 613,  256, 256, true);								// Nage Temple of Azarah - body
		addTextureEntry(32,  15,   14,   256, 256, false, true, 192, 4);				// Nage Abyss Portal - top
		addTextureEntry(32,  408,  204,  256, 256, false);								// Nage Abyss Portal - ring
		addTextureEntry(32,  157,  190,  256, 256, false);								// Nage Abyss Portal - rock
		addTextureEntry(32,  1035, 830,  256, 256, false);								// Nage Abyss Portal - body
		addTextureEntry(32,  76,   54,   32,  64,  true, true, 192, 4);				// Nage Reef Ruin - top1
		addTextureEntry(32,  162,  128,  32,  128, true, true, 192, 4);				// Nage Reef Ruin - top2
		addTextureEntry(32,  240,  416,  128, 256, true);								// Nage Reef Ruin - sea star
		addTextureEntry(32,  72,   64,   256, 256, true);								// Nage Reef Ruin - reef
		addTextureEntry(32,  130,  240,  256, 256, false);								// Nage Reef Ruin - bubble
		addTextureEntry(32,  72,   144,  256, 256, true);								// Nage Reef Ruin - sea weed bottom
		addTextureEntry(32,  398,  372,  512, 512, true);								// Nage Reef Ruin - sea weed top
		addTextureEntry(32,  207,  184,  256, 256, true);								// Nage Reef Ruin - sea weed middle
		addTextureEntry(32,  829,  922,  512, 512, true);								// Nage Reef Ruin - wood
		addTextureEntry(32,  16,   12,   128, 256, true);								// Nage Reef Ruin - banner [conflict]
		addTextureEntry(32,  107,  160,  128, 256, true);								// Nage Reef Ruin - shell
		addTextureEntry(32,  1502, 2306, 512, 512, false);								// Nage Reef Ruin - murloc
		#pragma endregion

		#pragma region IceTroll
		addTextureEntry(32,  180,  94,   256, 256, true);								// IceTroll Barracks - body [messy]
		addTextureEntry(32,  356,  182,  256, 256, false);								// IceTroll Barracks - roof
		//addTextureEntry(32,  80,    32,  256, 256, false, true, 192, 4);				// IceTroll Barracks - tusks [display issue]
		addTextureEntry(32,  128,  68,   256, 256, false, true, 192, 4);				// IceTroll Barracks - top
		addTextureEntry(32,  20,   23,   256, 256, false);								// IceTroll Altar - skull
		addTextureEntry(32,  70,   75,   256, 256, false);								// IceTroll Altar - skull2
		addTextureEntry(32,  70,   70,   256, 256, false);								// IceTroll Altar - stair
		addTextureEntry(32,  20,   16,   256, 256, false);								// IceTroll Altar - body
		addTextureEntry(32,  177,  104,  256, 256, false);								// IceTroll Altar - water
		addTextureEntry(32,  231,  231,  256, 256, false);								// IceTroll Altar - thorns
		addTextureEntry(32,  176,  52,   256, 256, false);								// IceTroll Altar - torches
		addTextureEntry(32,  286,  336,  256, 256, false);								// IceTroll Altar - dragon
		addTextureEntry(32,  28,   16,   256, 256, false, true, 192, 4);				// IceTroll Altar - top1
		addTextureEntry(32,  94,   68,   256, 256, false, true, 192, 4);				// IceTroll Altar - top2
		addTextureEntry(32,  598,  496,  256, 256, false);								// IceTroll Dragon Roost
		addTextureEntry(32,  120,  126,  256, 256, false, true, 192, 4);				// IceTroll Igloo - tusks
		addTextureEntry(32,  161,  175,  256, 256, false, true, 192, 4);				// IceTroll Igloo - top
		addTextureEntry(32,  424,  350,  256, 256, false);								// IceTroll War Mill - body
		addTextureEntry(32,  22,   17,   256, 256, true);								// IceTroll War Mill - top
		#pragma endregion

		#pragma region BloodElf
		addTextureEntry(32,  942,  70,   256, 256, false);								// BloodElf Structure - base
		addTextureEntry(32,  460,  205,  256, 256, true);								// BloodElf Structure - home
		addTextureEntry(32,  30,   14,   128, 128, false);								// BloodElf Structure - cube
		addTextureEntry(32,  60,   28,   128, 128, false);								// BloodElf Structure - cube aviary
		addTextureEntry(32,  205,  99,   256, 256, false);								// BloodElf Structure - sun vault
		addTextureEntry(32,  304,  142,  256, 256, false);								// BloodElf Structure - house wooden plank
		addTextureEntry(32,  334,  162,  256, 256, false);								// BloodElf Structure - sun vault
		addTextureEntry(32,  383,  176,  256, 256, false);								// BloodElf Structure - forge
		addTextureEntry(32,  556,  229,  256, 256, false);								// BloodElf Structure - home wooden plank
		addTextureEntry(32,  302,  152,  256, 256, false);								// BloodElf Structure - tower wooden plank
		addTextureEntry(32,  600,  288,  256, 256, false);								// BloodElf Structure - tower upgrade wooden plank
		addTextureEntry(32,  423,  187,  256, 256, false);								// BloodElf Structure - arcane workshop wooden plank
		addTextureEntry(32,  430,  198,  256, 256, false);								// BloodElf Structure - saw mill/farstrider lodge
		addTextureEntry(32,  1041, 887,  256, 256, true);								// BloodElf Haven - top
		addTextureEntry(32,  984,  840,  256, 128, false);								// BloodElf Haven - flowers
		addTextureEntry(32,  525,  312,  256, 256, false);								// BloodElf Haven - body
		addTextureEntry(32,  1488, 1273, 256, 256, true);								// BloodElf Sanctuary - top
		addTextureEntry(32,  608,  450,  256, 256, false);								// BloodElf Sanctuary - body1
		addTextureEntry(32,  3172, 290,  256, 256, false);								// BloodElf Sanctuary - body2
		addTextureEntry(32,  1842, 1741, 256, 256, true);								// BloodElf Temple - top
		//addTextureEntry(32,  122,  56,   8,   8,   false);							// BloodElf Temple - gems [conflict]
		addTextureEntry(32,  663,  518,  256, 256, false);								// BloodElf Temple - body1
		addTextureEntry(32,  7564, 678,  256, 256, false);								// BloodElf Temple - body2
		addTextureEntry(32,  138,  180,  256, 256, true, true, 192, 4);				// BloodElf House - top
		addTextureEntry(32,  127,  41,   256, 256, true);								// BloodElf House - lantern
		addTextureEntry(32,  409,  191,  256, 256, false);								// BloodElf House - body
		addTextureEntry(32,  484,  374,  256, 256, true);								// BloodElf Mage Spire - top
		addTextureEntry(32,  751,  248,  256, 256, false);								// BloodElf Mage Spire - body
		//addTextureEntry(32,  12,   6,    256, 256, false);							// BloodElf Mage Spire - plate [conflict]
		//addTextureEntry(32,  4,    2,    256, 256, false);							// BloodElf Mage Spire - balls [conflict]
		addTextureEntry(32,  719,  696,  256, 256, true);								// BloodElf Arcane Workshop - top
		addTextureEntry(32,  574,  224,  256, 256, false);								// BloodElf Arcane Workshop - body
		addTextureEntry(32,  300,  122,  256, 256, true);								// BloodElf Arcane Workshop - lantern
		addTextureEntry(32,  597,  638,  256, 256, true);								// BloodElf Aviary - top
		//addTextureEntry(32,  31,   24,   256, 256, false);							// BloodElf Aviary - nest [conflict with trees]
		addTextureEntry(32,  786,  262,  256, 256, false);								// BloodElf Aviary - body
		addTextureEntry(32,  52,   22,   256, 256, true, true, 192, 4);				// BloodElf Altar - top
		addTextureEntry(32,  72,   48,   256, 256, true);								// BloodElf Altar - ring
		addTextureEntry(32,  242,  194,  256, 256, false);								// BloodElf Altar - status
		addTextureEntry(32,  330,  155,  256, 256, true);								// BloodElf Altar - body
		addTextureEntry(32,  130,  112,  256, 256, true);								// BloodElf Saw Mill - top
		addTextureEntry(32,  227,  60,   256, 256, true);								// BloodElf Saw Mill - body
		addTextureEntry(32,  301,  171,  256, 256, false);								// BloodElf Saw Mill - base
		addTextureEntry(32,  198,  122,  256, 256, false);								// BloodElf Saw Mill - tree
		addTextureEntry(32,  484,  480,  256, 256, true);								// BloodElf Barracks - top
		addTextureEntry(32,  882,  308,  256, 256, true);								// BloodElf Barracks - body
		addTextureEntry(32,  144,  80,   256, 256, false);								// BloodElf Forge - top
		addTextureEntry(32,  936,  104,  256, 256, true);								// BloodElf Forge - furnace
		addTextureEntry(32,  594,  172,  256, 256, true);								// BloodElf Forge - body
		addTextureEntry(32,  78,   118,  128, 128, true);								// BloodElf Forge - eagle head
		addTextureEntry(32,  110,  32,   256, 256, true, true, 192, 4);				// BloodElf Tower - top
		addTextureEntry(32,  108,  144,  256, 256, true);								// BloodElf Tower - roof
		addTextureEntry(32,  1220, 98,   256, 256, false);								// BloodElf Tower - wall
		addTextureEntry(32,  2372, 162,  256, 256, false);								// BloodElf Tower - advanced wall
		addTextureEntry(32,  308,  80,   256, 256, false);								// BloodElf Tower - body
		addTextureEntry(32,  108,  60,   256, 256, false);								// BloodElf Tower - arrow
		addTextureEntry(32,  121,  80,   256, 256, false);								// BloodElf Tower - mage tower
		addTextureEntry(32,  201,  54,   256, 256, false, true, 192, 4);				// BloodElf Arcane Vault - top
		addTextureEntry(32,  661,  130,  256, 256, false);								// BloodElf Arcane Vault - body
		#pragma endregion

		#pragma region FelOrc
		addTextureEntry(32,  6,    4,    256, 256, false);								// FelOrc Structure Base fence
		addTextureEntry(32,  99,   55,   256, 256, false);								// FelOrc Structure Base stake
		addTextureEntry(32,  198,  131,  256, 256, false, true, 192, 4);				// FelOrc Fortress - top
		addTextureEntry(32,  48,   37,   256, 256, false);								// FelOrc Fortress - fence
		//addTextureEntry(32,  116,  158,  256, 256, false);							// FelOrc Stronghold - top tusk
		addTextureEntry(32,  32,   13,   256, 256, false, true, 192, 4);				// FelOrc Stronghold - top
		addTextureEntry(32,  35,   17,   256, 256, true, true, 192, 4);				// FelOrc Stronghold - top roof
		addTextureEntry(32,  271,  198,  256, 256, false);								// FelOrc Stronghold - body roof
		//addTextureEntry(32,  176,  120,  256, 256, false);							// FelOrc Stronghold - body skull
		//addTextureEntry(32,  180,  270,  256, 256, false);							// FelOrc Stronghold - body tusk
		addTextureEntry(32,  54,   56,   256, 256, true);								// FelOrc Stronghold - body
		addTextureEntry(32,  65,   44,   256, 256, true);								// FelOrc Stronghold - body2
		addTextureEntry(32,  168,  72,   256, 256, false);								// FelOrc Stronghold - spire
		addTextureEntry(32,  45,   35,   256, 256, false);								// FelOrc Stronghold - fence
		addTextureEntry(32,  76,   38,   256, 256, false, true, 192, 4);				// FelOrc Great Hall - top
		//addTextureEntry(32,  135,  184,  256, 256, false);							// FelOrc Great Hall - top tusk
		addTextureEntry(32,  146,  74,   256, 256, false, true, 192, 4);				// FelOrc Great Hall - top acne
		addTextureEntry(32,  47,   37,   256, 256, false);								// FelOrc Great Hall - fence
		addTextureEntry(32,  144,  90,   256, 256, false);								// FelOrc Great Hall - spire
		addTextureEntry(32,  32,   16,   256, 256, false);								// FelOrc Great Hall - body
		addTextureEntry(32,  57,   30,   256, 256, false, true, 192, 4);				// FelOrc PigFarm - top
		addTextureEntry(32,  112,  48,   256, 256, false);								// FelOrc PigFarm - spire
		addTextureEntry(32,  311,  202,  256, 256, false);								// FelOrc PigFarm - body
		//addTextureEntry(32,  205,  151,  256, 256, false);							// FelOrc PigFarm - flower
		//addTextureEntry(32,  816,  56,   256, 256, false);							// FelOrc Watch Tower - top
		//addTextureEntry(32,  816,  64,   256, 256, false);							// FelOrc Watch Tower - top fringe
		//addTextureEntry(32,  408,  26,   256, 256, false);							// FelOrc Watch Tower - top fringe2
		addTextureEntry(32,  205,  9,    256, 256, false);								// FelOrc Watch Tower - top panel
		addTextureEntry(32,  222,  16,   256, 256, false, true, 192, 4);				// FelOrc Watch Tower - top roof
		//addTextureEntry(32,  21,   24,   256, 256, false);							// FelOrc Shadowmoon Faire - top entrance
		addTextureEntry(32,  408,  26,   256, 256, false);								// FelOrc Shadowmoon Faire - top fringe
		addTextureEntry(32,  666,  48,   256, 256, false);								// FelOrc Shadowmoon Faire - top
		addTextureEntry(32,  24,   16,   256, 256, false, true, 192, 4);				// FelOrc War Mill - top
		addTextureEntry(32,  279,  293,  256, 256, false);								// FelOrc War Mill - body
		//addTextureEntry(32,  50,   70,   256, 256, false);							// FelOrc War Mill - body tusk
		addTextureEntry(32,  56,   24,   256, 256, false);								// FelOrc War Mill - body spire
		addTextureEntry(32,  144,  74,   256, 256, false);								// FelOrc War Mill - body furnace
		addTextureEntry(32,  308,  132,  256, 256, false);								// FelOrc Warlock Monument - body
		addTextureEntry(32,  132,  79,   256, 256, false);								// FelOrc Warlock Monument - base
		//addTextureEntry(32,  56,   96,   256, 256, false);							// FelOrc Warlock Monument - skull
		addTextureEntry(32,  106,  48,   256, 256, false);								// FelOrc Warlock Monument - wall
		//addTextureEntry(32,  2090, 1692, 256, 256, false);							// FelOrc Blood Furnace - body
		addTextureEntry(32,  433,  432,  256, 256, false);								// FelOrc Blood Furnace - fence
		//addTextureEntry(32,  388,  328,  256, 256, false);							// FelOrc Blood Furnace - throns
		addTextureEntry(32,  56,   46,   256, 256, false);								// FelOrc Blood Furnace - ring
		addTextureEntry(32,  137,  96,   256, 256, true);								// FelOrc Dungeon - entrance
		addTextureEntry(32,  22,   16,   256, 256, true);								// FelOrc Dungeon - entrance
		addTextureEntry(32,  170,  76,   256, 256, false);								// FelOrc Dungeon - fence
		addTextureEntry(32,  282,  449,  256, 256, true);								// FelOrc Dungeon - mountain
		addTextureEntry(32,  46,   37,   256, 256, false);								// FelOrc Barracks - fence
		//addTextureEntry(32,  192,  88,   256, 256, false);							// FelOrc Altar - torch
		//addTextureEntry(32,  39,   23,   256, 256, false);							// FelOrc Altar - body
		//addTextureEntry(32,  97,   51,   256, 256, false);							// FelOrc Altar - body2
		addTextureEntry(32,  60,   90,   256, 256, false);								// FelOrc Altar - tusk
		addTextureEntry(32,  65,   62,   64,  64,  false);								// FelOrc Altar - skull
		#pragma endregion

		#pragma region Neutral
		addTextureEntry(32,  271,  239,  256, 256, false);								// Gold Mine - mine
		addTextureEntry(32,  84,   51,   64,  64,  false);								// Gold Mine - gold
		addTextureEntry(32,  123,  60,   256, 256, false);								// Gold Mine - base
		addTextureEntry(32,  132,  68,   256, 64,  false);								// Goblin Merchant - rooftop
		addTextureEntry(32,  474,  274,  256, 256, false);								// Goblin Merchant - body
		addTextureEntry(32,  547,  442,  256, 256, false);								// Tarven
		addTextureEntry(32,  132,  48,   24,  64,  false, true, 192, 4);				// Tarven - top
		addTextureEntry(32,  331,  346,  512, 256, false);								// Fountain of Health
		addTextureEntry(32,  491,  348,  256, 256, false);								// Goblin Laboratory
		addTextureEntry(32,  571,  394,  256, 256, false);								// Mercenary Camp
		addTextureEntry(32,  407,  347,  256, 256, true);								// Marketplace - body
		addTextureEntry(32,  94,   46,   256, 256, true, true, 192, 4);				// Marketplace - top
		addTextureEntry(32,  305,  222,  256, 256, false);								// Way Gate - body
		addTextureEntry(32,  58,   44,   256, 256, false,true, 192, 4);				// Way Gate - top
		#pragma endregion

		#pragma region Terrain Decoration
		addTextureEntry(32,  328,  316,  256, 256, false);								// Swordsman Statue1
		//addTextureEntry(32,  36,   28,  256, 256, false);							// Tree
		//addTextureEntry(32,  247,  336, 256, 256, false);							// Test Subject
		#pragma endregion

		#ifdef _DEBUG
		writeKeysToFile();
		#endif
	}
}