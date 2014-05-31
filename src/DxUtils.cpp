#include "DxUtils.h"

// Get Z/Y/X rotation angle
void GetRotation(D3DMATRIX* pMatrix, float& Yaw, float& Pitch, float& Roll)
{
	if (pMatrix->_11 == 1.0f)
	{
		Yaw = atan2f(pMatrix->_13, pMatrix->_34);
		Pitch = 0;
		Roll = 0;
	}
	else if (pMatrix->_11 == -1.0f)
	{
		Yaw = atan2f(pMatrix->_13, pMatrix->_34);
		Pitch = 0;
		Roll = 0;
	}
	else 
	{
		Yaw = atan2(-pMatrix->_31, pMatrix->_11);
		Pitch = atan2(-pMatrix->_32, pMatrix->_33);
		Roll = atan2(-pMatrix->_23, pMatrix->_22);
	}
}