#pragma once

#include <math.h>
#include <d3dx9.h>

void cry_sincos(float angle, float* pSin, float* pCos);
void sincos(float angle, float* pSin, float* pCos);
float isqrt_tpl(float op);

typedef unsigned int EntityId;
struct Quat;
struct QuatT;
struct SRWIParams;
struct IPhysicalEntity;
struct Matrix34;
struct Matrix33;
struct ray_hit;
struct AABB;

struct VecToScreen
{
public:
	float toX;
	float toY;
	float toZ;
	float* outX;
	float* outY;
	float* outZ;
};

struct AABB
{
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
};

struct Quat
{
	D3DXVECTOR3 v;
	float w;

	friend float operator | (const Quat& q, const Quat& p)
	{
		return (q.v.x*p.v.x + q.v.y*p.v.y + q.v.z*p.v.z + q.w*p.w);
	}

	friend Quat operator - (const Quat &q, const Quat &p)
	{
		Quat ret;
		ret.w = q.w - p.w;

		ret.v.x = q.v.x - p.v.x;
		ret.v.y = q.v.y - p.v.y;
		ret.v.z = q.v.z - p.v.z;

		return ret;
	}

	void Normalize(void)
	{
		float d = isqrt_tpl(w*w + v.x*v.x + v.y*v.y + v.z*v.z);

		w *= d;

		v.x *= d;
		v.y *= d;
		v.z *= d;
	}

	void SetNlerp(const Quat &p, const Quat &tq, float t)
	{
		Quat q = tq;

		if((p | q) < 0)
		{
			float qx = -q.v.x;
			float qy = -q.v.y;
			float qz = -q.v.z;

			q.v.x = qx;
			q.v.y = qy;
			q.v.z = qz;
		}

		v.x = p.v.x*(1.0f - t) + q.v.x*t;
		v.y = p.v.y*(1.0f - t) + q.v.y*t;
		v.z = p.v.z*(1.0f - t) + q.v.z*t;

		w = p.w  *(1.0f - t) + q.w  *t;

		Normalize();
	}

	void SetSlerp(const Quat &tp, const Quat &tq, float t)
	{
		Quat p, q;
		p = tp;
		q = tq;
		Quat q2;

		float cosine = (p | q);

		if(cosine < 0.0f)
		{
			float qx = -q.v.x;
			float qy = -q.v.y;
			float qz = -q.v.z;

			cosine = -cosine;

			q.v.x = qx;
			q.v.y = qy;
			q.v.z = qz;
		}

		if(cosine > 0.9999f)
		{
			SetNlerp(p, q, t);
			return;
		}

		q2.w = q.w - p.w*cosine;
		q2.v.x = q.v.x - p.v.x*cosine;
		q2.v.y = q.v.y - p.v.y*cosine;
		q2.v.z = q.v.z - p.v.z*cosine;

		float sine = (float)sqrt(q2 | q2);
		float s, c;

		sincos((float)atan2(sine, cosine)*t, &s, &c);

		w = (p.w*c + q2.w*s / sine);
		v.x = (p.v.x*c + q2.v.x*s / sine);
		v.y = (p.v.y*c + q2.v.y*s / sine);
		v.z = (p.v.z*c + q2.v.z*s / sine);
	}

	static Quat CreateSlerp(const Quat &p, const Quat &tq, float t)
	{
		Quat d;
		d.SetSlerp(p, tq, t);
		return d;
	}

	Quat(const Matrix33& m);

	Quat()
	{
	}
};

struct QuatT
{
	Quat q;
	D3DXVECTOR3 t;
};

#define COLLISION_RAY_PIERCABILITY 10
#define RWI_RAY_PIERCABILITY_MASK  0x0F

struct ray_hit
{
	float dist;
	IPhysicalEntity *pCollider;
	int ipart;
	int partid;
	short surface_idx;
	short idmatOrg;
	int foreignIdx;
	int iNode;
	D3DXVECTOR3 pt;
	D3DXVECTOR3 n;
	int bTerrain;
	int iPrim;
	ray_hit *next;
};

struct ray_hit_cached : ray_hit
{
	ray_hit_cached()
	{
		pCollider = 0; ipart = 0;
	}
	ray_hit_cached(const ray_hit &hit)
	{
		pCollider = hit.pCollider; ipart = hit.ipart;
		iNode = hit.iNode;
	}
	ray_hit_cached &operator=(const ray_hit &hit)
	{
		pCollider = hit.pCollider; ipart = hit.ipart;
		iNode = hit.iNode; return *this;
	}
};


struct Matrix34
{
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;

	D3DXVECTOR3 GetPosition()
	{
		return D3DXVECTOR3(m03, m13, m23);
	}

	Matrix34()
	{
	}

	Matrix34(const QuatT& q)
	{
		D3DXVECTOR3 v2;
		v2.x = (q.q.v.x) + (q.q.v.x);
		float xx = 1 - v2.x*q.q.v.x; float yy = v2.y*q.q.v.y; float xw = v2.x*q.q.w;
		float xy = v2.y*q.q.v.x;   float yz = v2.z*q.q.v.y; float  yw = v2.y*q.q.w;
		float xz = v2.z*q.q.v.x;   float zz = v2.z*q.q.v.z; float  zw = v2.z*q.q.w;
		m00 = float(1 - yy - zz);     m01 = float(xy - zw);     m02 = float(xz + yw);   m03 = float(q.t.x);
		m10 = float(xy + zw);      m11 = float(xx - zz);     m12 = float(yz - xw);   m13 = float(q.t.y);
		m20 = float(xz - yw);      m21 = float(yz + xw);     m22 = float(xx - yy);   m23 = float(q.t.z);
	}

	friend Matrix34 operator * (const Matrix34& l, const Matrix34& r)
	{
		Matrix34 m = r;
		m.m00 = l.m00*r.m00 + l.m01*r.m10 + l.m02*r.m20;
		m.m10 = l.m10*r.m00 + l.m11*r.m10 + l.m12*r.m20;
		m.m20 = l.m20*r.m00 + l.m21*r.m10 + l.m22*r.m20;
		m.m01 = l.m00*r.m01 + l.m01*r.m11 + l.m02*r.m21;
		m.m11 = l.m10*r.m01 + l.m11*r.m11 + l.m12*r.m21;
		m.m21 = l.m20*r.m01 + l.m21*r.m11 + l.m22*r.m21;
		m.m02 = l.m00*r.m02 + l.m01*r.m12 + l.m02*r.m22;
		m.m12 = l.m10*r.m02 + l.m11*r.m12 + l.m12*r.m22;
		m.m22 = l.m20*r.m02 + l.m21*r.m12 + l.m22*r.m22;
		m.m03 = l.m00*r.m03 + l.m01*r.m13 + l.m02*r.m23 + l.m03;
		m.m13 = l.m10*r.m03 + l.m11*r.m13 + l.m12*r.m23 + l.m13;
		m.m23 = l.m20*r.m03 + l.m21*r.m13 + l.m22*r.m23 + l.m23;
		return m;
	}

};

struct Matrix33
{
	float m00, m01, m02;
	float m10, m11, m12;
	float m20, m21, m22;

	Matrix33()
	{
	}

	Matrix33(const Matrix34& input)
	{
		m00 = input.m00;
		m01 = input.m01;
		m02 = input.m02;
		m10 = input.m10;
		m11 = input.m11;
		m12 = input.m12;
		m20 = input.m20;
		m21 = input.m21;
		m22 = input.m22;
	}

	void SetRotationVDir(const D3DXVECTOR3& vdir)
	{
		m00 = 1;
		m01 = 0;
		m02 = 0;

		m10 = 0;
		m11 = 0;
		m12 = -vdir.z;

		m20 = 0;
		m21 = vdir.z;
		m22 = 0;

		float l = (float)sqrt(vdir.x*vdir.x + vdir.y*vdir.y);

		if(l > 0.0001)
		{
			float xl = -vdir.x / l; float yl = vdir.y / l;

			m00 = (yl);
			m01 = (vdir.x);
			m02 = (xl*vdir.z);

			m10 = (xl);
			m11 = (vdir.y);
			m12 = (-vdir.z*yl);

			m20 = 0;
			m21 = (vdir.z);
			m22 = (l);
		}
	}
};

float GetDistance2D(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB);
float GetDistance3D(D3DXVECTOR3 VecA, D3DXVECTOR3 VecB);
D3DXVECTOR3 *VectorNormalize(D3DXVECTOR3 *pOut, const D3DXVECTOR3 *pV);