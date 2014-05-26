#include "ShadowVolumeHandler.h"

namespace SV {
	void InitShadowTable(ShadowTable& table)
	{
		table.addShadow(46,   60);													// Peasant - body
		table.addShadow(302,  270);													// Peasant - top
		table.addShadow(120,  48,  SHW_USE_TRANSFORMATION);							// Peasant - lumber
		table.addShadow(36,   35);													// Peasant - gold
		table.addShadow(377,  397);													// Demon Hunter	- body
		table.addShadow(30,   36);													// Demon Hunter - top
	}
}