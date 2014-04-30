#include "NormalMapData.h"

namespace NP {
	void Input(TextureTable &texTable)
	{
		texTable.Cleanup();
		/*
		 * Format: 
		 * Stride, NumVertices, PrimCount, Width, Height, Inverted, IsMask(optional), NormalAlphaRef(optional), TransplantAlphaRef(optional)
		 */
		texTable.addTextureEntry(32,  1053, 511,  256, 256, false);								// Human Construction Set
		//texTable.addTextureEntry(32,  20,   10,   256, 256, false, true, 192, 4);					// Human Farm - top
		texTable.addTextureEntry(32,  320,  153,  256, 256, false);								// Human Farm - body
		texTable.addTextureEntry(32,  8,    6,    256, 256, false);								// Human Townhall - base
		texTable.addTextureEntry(32,  18,   10,   512, 512, false, true, 192, 4);					// Human Townhall - top
		texTable.addTextureEntry(32,  454,  209,  512, 512, false);								// Human Townhall - body
		texTable.addTextureEntry(32,  37,   19,   512, 512, false, true, 192, 4);					// Human Keep - top
		texTable.addTextureEntry(32,  405,  200,  512, 512, false);								// Human Keep - body
		texTable.addTextureEntry(32,  177,  83,   512, 512, false, true, 192, 4);					// Human Castle - top
		texTable.addTextureEntry(32,  418,  352,  512, 512, false);								// Human Castle - body
		texTable.addTextureEntry(32,  90,   30,   256, 256, false);								// Human Castle - base
		//texTable.addTextureEntry(32,  52,   42,   256, 256, false, true, 192, 4);					// Human Altar - top (weird color)
		texTable.addTextureEntry(32,  359,  302,  256, 256, false);								// Human Altar - body
		texTable.addTextureEntry(32,  99,   46,   256, 256, false, true, 192, 4);					// Human Barracks - top
		texTable.addTextureEntry(32,  387,  209,  256, 256, false);								// Human Barracks - body
		texTable.addTextureEntry(32,  14,   8,    256, 256, false, true, 192, 4);					// Human Lumber Mill - top
		texTable.addTextureEntry(32,  386,  224,  256, 256, false);								// Human Lumber Mill - body
		texTable.addTextureEntry(32,  20,   28,   256, 256, false);								// Human Lumber Mill - base
		texTable.addTextureEntry(32,  22,   14,   256, 256, false, true, 192, 4);					// Human BlackSmith - top
		texTable.addTextureEntry(32,  605,  343,  256, 256, false);								// Human BlackSmith - body
		texTable.addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);					// Human Arcane Vault - top
		texTable.addTextureEntry(32,  85,   40,   256, 256, false);								// Human Arcane Vault - gem
		texTable.addTextureEntry(32,  96,   48,   256, 256, false);								// Human Arcane Vault - pole
		texTable.addTextureEntry(32,  500,  266,  256, 256, false);								// Human Arcane Vault - chain
		//texTable.addTextureEntry(32,  39,   24,   256, 256, false, true, 192, 4);					// Human Arcane Sanctum - top
		texTable.addTextureEntry(32,  923,  578,  256, 256, false);								// Human Arcane Sanctum - body
		//texTable.addTextureEntry(32,  25,   17,   256, 256, false, true, 192, 4);					// Human Gryphon Aviary - top
		texTable.addTextureEntry(32,  414,  309,  256, 256, true);								// Human Gryphon Aviary - body
		//texTable.addTextureEntry(32,  20,   26,   256, 256, false, true, 192, 4);					// Human Workshop - top
		texTable.addTextureEntry(32,  310,  266,  256, 256, false);								// Human Workshop - body
		//texTable.addTextureEntry(32,  27,   15,   256, 128, true, true, 192, 4);					// Human Scout Tower - top
		texTable.addTextureEntry(32,  251,  149,  256, 128, true);								// Human Scout Tower - body
		//texTable.addTextureEntry(32,  216,  123,  256, 128, true, true, 192, 4);					// Human Arcane Tower - top (conflict)
		//texTable.addTextureEntry(32,  88,   56,   256, 128, true);								// Human Arcane Tower - body (conflict)
		texTable.addTextureEntry(32,  97,   48,   256, 128, true);								// Human Arcane Tower - tower
		//texTable.addTextureEntry(32,  51,   27,   256, 128, true, true, 192, 4);					// Human Guard Tower - top
		texTable.addTextureEntry(32,  216,  123,  256, 128, true);								// Human Guard Tower - body
		//texTable.addTextureEntry(32,  32,   20,   256, 128, true, true, 192, 4);					// Human Cannon Tower - top
		texTable.addTextureEntry(32,  300,  189,  256, 128, true);								// Human Cannon Tower - body

		texTable.addTextureEntry(32,  300,  252,  256, 256, false);								// Orc Construction Set - large
		texTable.addTextureEntry(32,  264,  228,  256, 256, false);								// Orc Construction Set - medium
		texTable.addTextureEntry(32,  198,  164,  256, 256, false);								// Orc Construction Set - small
		//texTable.addTextureEntry(32,  64,   64,   256, 256, false, true, 192, 4);					// Orc Construction Set - top (conflict)
		texTable.addTextureEntry(32,  160,  104,  256, 256, true);								// Orc Structure - base
		texTable.addTextureEntry(32,  124,  80,   256, 256, false);								// Orc Structure Spike
		texTable.addTextureEntry(32,  192,  144,  128, 128, false);								// Orc Structure Barricade

		texTable.addTextureEntry(32,  191,  214,  256, 256, false, true, 192, 4);					// Orc Great Hall - top	
		texTable.addTextureEntry(32,  290,  164,  256, 256, false);								// Orc Great Hall - body
		texTable.addTextureEntry(32,  183,  188,  256, 256, false, true, 192, 4);					// Orc Stronghold - top
		texTable.addTextureEntry(32,  384,  249,  256, 256, false);								// Orc Stronghold - body
		texTable.addTextureEntry(32,  226,  149,  256, 256, false, true, 192, 4);					// Orc Fortress - top
		texTable.addTextureEntry(32,  516,  498,  256, 256, false);								// Orc Fortress - body
		texTable.addTextureEntry(32,  95,   59,   256, 256, false, true, 192, 4);					// Orc Altar - top
		texTable.addTextureEntry(32,  291,  264,  256, 256, false);								// Orc Altar - body
		texTable.addTextureEntry(32,  265,  206,  128, 128, false);								// Orc Burrow - body
		//texTable.addTextureEntry(32,  36,   28,   128, 128, false, true, 192, 4);					// Orc Burrow - top
		texTable.addTextureEntry(32,  309,  317,  256, 256, false);								// Orc War Mill - body
		texTable.addTextureEntry(32,  125,  81,   256, 256, false);								// Orc War Mill - saw
		texTable.addTextureEntry(32,  42,   48,   256, 256, false, true, 192, 4);					// Orc War Mill - top
		texTable.addTextureEntry(32,  466,  295,  256, 256, false);								// Orc Watch Tower - body
		texTable.addTextureEntry(32,  17,   12,   256, 256, false, true, 192, 4);					// Orc Watch Tower - top
		texTable.addTextureEntry(32,  255,  195,  256, 256, false);								// Orc Barracks - body
		texTable.addTextureEntry(32,  73,   56,   256, 256, false, true, 192, 4);					// Orc Barracks - top
		//texTable.addTextureEntry(32,  19,   20,   256, 256, false);								// Orc Voodoo Lounge - funnel
		texTable.addTextureEntry(32,  66,   54,   256, 256, false);								// Orc Voodoo Lounge - tusk
		texTable.addTextureEntry(32,  145,  78,   256, 256, false);								// Orc Voodoo Lounge - body
		texTable.addTextureEntry(32,  211,  207,  256, 256, false, true, 192, 4);					// Orc Voodoo Lounge - top
		texTable.addTextureEntry(32,  327,  260,  256, 256, true);								// Orc Beastiary - body
		texTable.addTextureEntry(32,  69,   92,   256, 256, false, true, 192, 4);					// Orc Beastiary - top
		texTable.addTextureEntry(32,  414,  295,  256, 256, true);								// Orc Spirit Lounge - body
		texTable.addTextureEntry(32,  52,   26,   256, 256, true,  true, 192, 4);					// Orc Spirit Lounge - top
		texTable.addTextureEntry(32,  323,  221,  256, 256, false);								// Orc Tauren Totem - body
		texTable.addTextureEntry(32,  57,   67,   256, 256, false, true, 192, 4);					// Orc Tauren Totem - top

		texTable.addTextureEntry(32,  271,  239,  256, 256, false);								// Gold Mine - mine
		texTable.addTextureEntry(32,  84,   51,   64,  64,  false);								// Gold Mine - gold
		texTable.addTextureEntry(32,  123,  60,   256, 256, false);								// Gold Mine - base
		texTable.addTextureEntry(32,  132,  68,   256, 64,  false, true, 192, 4);					// Goblin Merchant - top
		texTable.addTextureEntry(32,  474,  274,  256, 256, false);								// Goblin Merchant - body
		texTable.addTextureEntry(32,  547,  442,  256, 256, false);								// Tarven
		texTable.addTextureEntry(32,  331,  346,  512, 256, false);								// Fountain of Health
		texTable.addTextureEntry(32,  491,  348,  256, 256, false);								// Goblin Laboratory
		texTable.addTextureEntry(32,  571,  394,  256, 256, false);								// Mercenary Camp
		texTable.addTextureEntry(32,  407,  347,  256, 256, false);								// Marketplace - body
		texTable.addTextureEntry(32,  94,   46,   256, 256, false, true, 192, 4);					// Marketplace - top

		//texTable.addTextureEntry(32,  36,   28,  256, 256, false);								// Tree
		//texTable.addTextureEntry(32,  247,  336, 256, 256, false);								// Test Subject

		//texTable.addTextureEntry(32,  1065, 1143,256, 256, false);								// Main Screen
		// TODO: add more...
	}
}