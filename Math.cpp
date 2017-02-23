#include "Math.h"

void cry_sincos(float angle, float* pSin, float* pCos)
{
	*pSin = (float)(sin(angle));  *pCos = (float)(cos(angle));
}

void sincos(float angle, float* pSin, float* pCos)
{
	cry_sincos(angle, pSin, pCos);
}

float isqrt_tpl(float op)
{
	return 1.0f / (float)sqrt(op);
}

Quat::Quat(const Matrix33& m)
{
	float s, p, tr = m.m00 + m.m11 + m.m22;
	w = 1, v.x = 0, v.y = 0, v.z = 0;

	if(tr > 0)
		s = (float)sqrt(tr + 1.0f), p = 0.5f / s, w = s*0.5f, v.x = (m.m21 - m.m12)*p, v.y = (m.m02 - m.m20)*p, v.z = (m.m10 - m.m01)*p;
	else if((m.m00 >= m.m11) && (m.m00 >= m.m22))
		s = (float)sqrt(m.m00 - m.m11 - m.m22 + 1.0f), p = 0.5f / s, w = (m.m21 - m.m12)*p, v.x = s*0.5f, v.y = (m.m10 + m.m01)*p, v.z = (m.m20 + m.m02)*p;
	else if((m.m11 >= m.m00) && (m.m11 >= m.m22))
		s = (float)sqrt(m.m11 - m.m22 - m.m00 + 1.0f), p = 0.5f / s, w = (m.m02 - m.m20)*p, v.x = (m.m01 + m.m10)*p, v.y = s*0.5f, v.z = (m.m21 + m.m12)*p;
	else if((m.m22 >= m.m00) && (m.m22 >= m.m11))
		s = (float)sqrt(m.m22 - m.m00 - m.m11 + 1.0f), p = 0.5f / s, w = (m.m10 - m.m01)*p, v.x = (m.m02 + m.m20)*p, v.y = (m.m12 + m.m21)*p, v.z = s*0.5f;
}

float GetDistance2D(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return (float)sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)));
}

float GetDistance3D(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB)
{
	return (float)sqrt(((VecA.x - VecB.x) * (VecA.x - VecB.x)) +
		((VecA.y - VecB.y) * (VecA.y - VecB.y)) +
					   ((VecA.z - VecB.z) * (VecA.z - VecB.z)));
}

D3DXVECTOR3 *VectorNormalize(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV)
{
	float length = (pV->x * pV->x +
					pV->z * pV->z +
					pV->y * pV->y);

	if(length > 0.0f)
	{
		length = sqrtf(length);
		pOut->x = pV->x / length;
		pOut->y = pV->y / length;
		pOut->z = pV->z / length;
		return pOut;
	}
	else
		return pOut;
}