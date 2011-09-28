/*
 *	(c) LSIIT, UMR CNRS/UdS
 *	Authors: O. Génevaux, F. Larue, G.Gilet.
 *
 *	See licence.txt for additional information.
 */


#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <stdio.h>
#include "vector.h"

/** Single precision floating point 4x4 matrix.
 *	\ingroup Common
 */
class Matrix4Df
{
public:

	
		float v[16];
	
	// Constructors

	/** Empty constructor. */
	inline Matrix4Df();
	/** Element-by-element matrix initialization. */
	inline Matrix4Df(const float m00, const float m10, const float m20, const float m30,
					const float m01, const float m11, const float m21, const float m31,
					const float m02, const float m12, const float m22, const float m32,
					const float m03, const float m13, const float m23, const float m33);
	inline Matrix4Df(const Vector& vecX, const Vector& vecY, const Vector& vecZ, const Vector& vecT);
	/** Matrix initialization from an array of scalars (column-first order). */
	inline Matrix4Df(const float* val);
	inline Matrix4Df(const Matrix4Df& m);

	

	/** Assignment. */
	inline Matrix4Df& operator=(const Matrix4Df& m);


	/** Indexed access to the matrix elements.
	 *	\param[in]	l	Row number in [0,3].
	 *	\param[in]	c	Column number in [0,3].
	 */
	inline       float& operator()(const unsigned int l, const unsigned int c);
	/** Indexed access to the matrix elements (read-only version).
	 *	\param[in]	l	Row number in [0,3].
	 *	\param[in]	c	Column number in [0,3].
	 */
	inline const float& operator()(const unsigned int l, const unsigned int c) const;


	/** Elementwise addition assignement. */
	inline Matrix4Df& operator+=(const Matrix4Df& m);
	/** Elementwise substraction assignement. */
	inline Matrix4Df& operator-=(const Matrix4Df& m);
	/** Matrix product (multiplication assignement). */
	inline Matrix4Df& operator*=(const Matrix4Df& m);
	/** Multiplication assignement by a scalar. */
	inline Matrix4Df& operator*=(const float f);


	/** Elementwise addition. */
	
	friend Matrix4Df operator+(const Matrix4Df& m1, const Matrix4Df& m2);
	/** Elementwise substraction. */
	
	friend Matrix4Df operator-(const Matrix4Df& m1, const Matrix4Df& m2);
	/** Matrix product. */
	
	friend Matrix4Df operator*(const Matrix4Df& m1, const Matrix4Df& m2);


	/** Negation. */
	
	friend Matrix4Df operator-(const Matrix4Df& m);


	/** Multiplication by a scalar. */
	
	friend Matrix4Df operator*(const float f, const Matrix4Df& m);
	/** Multiplication by a scalar. */
	
	friend Matrix4Df operator*(const Matrix4Df& m, const float f);


	// Mixed matrix vector ops

	inline Vector Mul(const Vector& v, const float w) const;
	/** Matrix/vector product.
	 *	The matrix is supposed to be an homogeneous transform in 3D space (composition of scale/rotation/translation),
	 *	and the vector is supposed to be a point in 3D space.
	 */
	inline Vector MulPt(const Vector& v) const;
	/** Matrix/vector product.
	 *	The matrix is supposed to be an homogeneous transform in 3D space (composition of scale/rotation/translation),
	 *	and the vector is supposed to be a direction in 3D space, which is then not affected by the translational part
	 *	of the transform.
	 */
	inline Vector MulDir(const Vector& v) const;


	/** Matrix transposition. */
	inline Matrix4Df& Transpose();

	/** Recovery of matrix invert. */
	
	inline Matrix4Df Invert(const Matrix4Df& m);
	/** Matrix inversion. */
	inline void Invert();

	/** Recovery of matrix trace. */
	inline float Trace() const;
	/** Recovery of matrix determinant. */
	inline float Determinant() const;


	/** Initialization to null matrix. */
	inline void SetZero();
	/** Initialization to identity matrix. */
	inline void SetIdentity();
	/** Initialization by setting all matrix elements to the same scalar value. */
	inline void SetScalar(const float f);
	/** Initialization to a diagonal matrix. */
	inline void SetDiagonal(const float f1, const float f2, const float f3, const float f4);

	inline void Print();
};

/*
 *	Inversion
 */


inline Matrix4Df Matrix4Df::Invert(const Matrix4Df& m)
{
	Matrix4Df inv;

	inv.v[0]  = m.v[5]*(m.v[15]*m.v[10]-m.v[11]*m.v[14]) + m.v[6]*(m.v[11]*m.v[13]-m.v[15]*m.v[9]) + m.v[7]*(m.v[14]*m.v[9]-m.v[10]*m.v[13]);
	inv.v[1]  = m.v[1]*(m.v[11]*m.v[14]-m.v[15]*m.v[10]) + m.v[2]*(m.v[15]*m.v[9]-m.v[11]*m.v[13]) + m.v[3]*(m.v[10]*m.v[13]-m.v[14]*m.v[9]);	
	inv.v[2]  = m.v[1]*(m.v[15]*m.v[6]-m.v[14]*m.v[7])   + m.v[2]*(m.v[7]*m.v[13]-m.v[5]*m.v[15])  + m.v[3]*(m.v[14]*m.v[5]-m.v[6]*m.v[13]);
	inv.v[3]  = m.v[1]*(m.v[7]*m.v[10]-m.v[11]*m.v[6])   + m.v[2]*(m.v[11]*m.v[5]-m.v[9]*m.v[7])   + m.v[3]*(m.v[6]*m.v[9]-m.v[5]*m.v[10]);	
	inv.v[4]  = m.v[4]*(m.v[11]*m.v[14]-m.v[15]*m.v[10]) + m.v[6]*(m.v[8]*m.v[15]-m.v[11]*m.v[12]) + m.v[7]*(m.v[12]*m.v[10]-m.v[14]*m.v[8]);
	inv.v[5]  = m.v[0]*(m.v[15]*m.v[10]-m.v[11]*m.v[14]) + m.v[2]*(m.v[11]*m.v[12]-m.v[8]*m.v[15]) + m.v[3]*(m.v[14]*m.v[8]-m.v[12]*m.v[10]);
	inv.v[6]  = m.v[0]*(m.v[14]*m.v[7]-m.v[15]*m.v[6])   + m.v[2]*(m.v[4]*m.v[15]-m.v[12]*m.v[7])  + m.v[3]*(m.v[6]*m.v[12]-m.v[4]*m.v[14]);
	inv.v[7]  = m.v[0]*(m.v[11]*m.v[6]-m.v[7]*m.v[10])	 + m.v[2]*(m.v[8]*m.v[7]-m.v[4]*m.v[11])   + m.v[3]*(m.v[4]*m.v[10]-m.v[8]*m.v[6]);
	inv.v[8]  = m.v[4]*(m.v[15]*m.v[9]-m.v[11]*m.v[13])  + m.v[5]*(m.v[11]*m.v[12]-m.v[8]*m.v[15]) + m.v[7]*(m.v[8]*m.v[13]-m.v[9]*m.v[12]);
	inv.v[9]  = m.v[0]*(m.v[11]*m.v[13]-m.v[15]*m.v[9])  + m.v[1]*(m.v[8]*m.v[15]-m.v[11]*m.v[12]) + m.v[3]*(m.v[9]*m.v[12]-m.v[8]*m.v[13]);
	inv.v[10] = m.v[0]*(m.v[5]*m.v[15]-m.v[7]*m.v[13])   + m.v[1]*(m.v[12]*m.v[7]-m.v[4]*m.v[15])  + m.v[3]*(m.v[4]*m.v[13]-m.v[5]*m.v[12]);
	inv.v[11] = m.v[0]*(m.v[9]*m.v[7]-m.v[11]*m.v[5])    + m.v[1]*(m.v[4]*m.v[11]-m.v[8]*m.v[7])   + m.v[3]*(m.v[5]*m.v[8]-m.v[4]*m.v[9]);
	inv.v[12] = m.v[4]*(m.v[10]*m.v[13]-m.v[14]*m.v[9])  + m.v[5]*(m.v[14]*m.v[8]-m.v[12]*m.v[10]) + m.v[6]*(m.v[9]*m.v[12]-m.v[8]*m.v[13]);
	inv.v[13] = m.v[0]*(m.v[14]*m.v[9]-m.v[10]*m.v[13])  + m.v[1]*(m.v[12]*m.v[10]-m.v[14]*m.v[8]) + m.v[2]*(m.v[8]*m.v[13]-m.v[9]*m.v[12]);
	inv.v[14] = m.v[0]*(m.v[6]*m.v[13]-m.v[14]*m.v[5])   + m.v[1]*(m.v[4]*m.v[14]-m.v[6]*m.v[12])  + m.v[2]*(m.v[5]*m.v[12]-m.v[4]*m.v[13]);
	inv.v[15] = m.v[0]*(m.v[5]*m.v[10]-m.v[6]*m.v[9])    + m.v[1]*(m.v[8]*m.v[6]-m.v[4]*m.v[10])   + m.v[2]*(m.v[4]*m.v[9]-m.v[5]*m.v[8]);


	float det = m(0, 0) * inv(0, 0) + m(0, 1) * inv(1, 0) + m(0, 2) * inv(2, 0) + m(0, 3) * inv(3, 0);
	float oodet = 1.0/ det;
	inv.v[0]  *= oodet; 
	inv.v[1]  *= oodet;
	inv.v[2]  *= oodet;
	inv.v[3]  *= oodet; 
	inv.v[4]  *= oodet;
	inv.v[5]  *= oodet;
	inv.v[6]  *= oodet; 
	inv.v[7]  *= oodet;
	inv.v[8]  *= oodet;
	inv.v[9]  *= oodet; 
	inv.v[10] *= oodet;
	inv.v[11] *= oodet;
	inv.v[12] *= oodet; 
	inv.v[13] *= oodet;
	inv.v[14] *= oodet;
	inv.v[15] *= oodet;

	return inv;
}



/*
 *	Constructors
 */


inline Matrix4Df::Matrix4Df()
{
}



inline Matrix4Df::Matrix4Df(	const float m00, const float m10, const float m20, const float m30,
								const float m01, const float m11, const float m21, const float m31,
								const float m02, const float m12, const float m22, const float m32,
								const float m03, const float m13, const float m23, const float m33)
{
	v[0]  = m00;	v[1]  = m10;	v[2]  = m20;	v[3]  = m30;
	v[4]  = m01;	v[5]  = m11;	v[6]  = m21;	v[7]  = m31;
	v[8]  = m02;	v[9]  = m12;	v[10] = m22;	v[11] = m32;
	v[12] = m03;	v[13] = m13;	v[14] = m23;	v[15] = m33;
}



inline Matrix4Df::Matrix4Df(const Vector& vecX, const Vector& vecY, const Vector& vecZ, const Vector& vecT)
{

v[0] = vecX[0];
v[1] = vecX[1];
v[2] = vecX[2];
v[3] = 0.0;

v[4] = vecY[0];
v[5] = vecY[1];
v[6] = vecY[2];
v[7] = 0.0;

v[8] = vecZ[0];
v[9] = vecZ[1];
v[10] = vecZ[2];
v[11] = 0.0;

v[12] = vecT[0];
v[13] = vecT[1];
v[14] = vecT[2];
v[15] = 1.0;
}



inline Matrix4Df::Matrix4Df(const float* val)
{
	v[0]  = val[0];		v[1]  = val[1];		v[2]  = val[2];		v[3]  = val[3];
	v[4]  = val[4];		v[5]  = val[5];		v[6]  = val[6];		v[7]  = val[7];
	v[8]  = val[8];		v[9]  = val[9];		v[10] = val[10];	v[11] = val[11];
	v[12] = val[12];	v[13] = val[13];	v[14] = val[14];	v[15] = val[15];
}



inline Matrix4Df::Matrix4Df(const Matrix4Df& m)
{
	v[0]  = m.v[0];		v[1]  = m.v[1];		v[2]  = m.v[2];		v[3]  = m.v[3];
	v[4]  = m.v[4];		v[5]  = m.v[5];		v[6]  = m.v[6];		v[7]  = m.v[7];
	v[8]  = m.v[8];		v[9]  = m.v[9];		v[10] = m.v[10];	v[11] = m.v[11];
	v[12] = m.v[12];	v[13] = m.v[13];	v[14] = m.v[14];	v[15] = m.v[15];
}



// Assignment


inline Matrix4Df& Matrix4Df::operator=(const Matrix4Df& m)
{
	v[0]  = m.v[0];		v[1]  = m.v[1];		v[2]  = m.v[2];		v[3]  = m.v[3];
	v[4]  = m.v[4];		v[5]  = m.v[5];		v[6]  = m.v[6];		v[7]  = m.v[7];
	v[8]  = m.v[8];		v[9]  = m.v[9];		v[10] = m.v[10];	v[11] = m.v[11];
	v[12] = m.v[12];	v[13] = m.v[13];	v[14] = m.v[14];	v[15] = m.v[15];

	return *this;
}


// Indexed access


inline float& Matrix4Df::operator()(const unsigned int l, const unsigned int c)
{
	return v[4 * c + l];
}



inline const float& Matrix4Df::operator()(const unsigned int l, const unsigned int c) const
{
	return v[4 * c + l];
}


// Combined Op-Assignment

inline Matrix4Df& Matrix4Df::operator+=(const Matrix4Df& m)
{
	v[0]  += m.v[0];	v[1]  += m.v[1];	v[2]  += m.v[2];	v[3]  += m.v[3];
	v[4]  += m.v[4];	v[5]  += m.v[5];	v[6]  += m.v[6];	v[7]  += m.v[7];
	v[8]  += m.v[8];	v[9]  += m.v[9];	v[10] += m.v[10];	v[11] += m.v[11];
	v[12] += m.v[12];	v[13] += m.v[13];	v[14] += m.v[14];	v[15] += m.v[15];

	return *this;
}


inline Matrix4Df& Matrix4Df::operator-=(const Matrix4Df& m)
{
	v[0]  -= m.v[0];	v[1]  -= m.v[1];	v[2]  -= m.v[2];	v[3]  -= m.v[3];
	v[4]  -= m.v[4];	v[5]  -= m.v[5];	v[6]  -= m.v[6];	v[7]  -= m.v[7];
	v[8]  -= m.v[8];	v[9]  -= m.v[9];	v[10] -= m.v[10];	v[11] -= m.v[11];
	v[12] -= m.v[12];	v[13] -= m.v[13];	v[14] -= m.v[14];	v[15] -= m.v[15];

	return *this;
}



inline Matrix4Df& Matrix4Df::operator*=(const Matrix4Df& m)
{
	Matrix4Df tmp(*this * m);
	*this = tmp;

	return *this;
}



inline Matrix4Df& Matrix4Df::operator*=(const float f)
{
	v[0]  *= f;	v[1]  *= f;	v[2]  *= f;	v[3]  *= f;
	v[4]  *= f;	v[5]  *= f;	v[6]  *= f;	v[7]  *= f;
	v[8]  *= f;	v[9]  *= f;	v[10] *= f;	v[11] *= f;
	v[12] *= f;	v[13] *= f;	v[14] *= f;	v[15] *= f;

	return *this;
}



// Binary ops


inline Matrix4Df operator+(const Matrix4Df& m1, const Matrix4Df& m2)
{
	return Matrix4Df(	m1.v[0]  + m2.v[0],		m1.v[1]  + m2.v[1],		m1.v[2]  + m2.v[2],		m1.v[3]  + m2.v[3],
						m1.v[4]  + m2.v[4],		m1.v[5]  + m2.v[5],		m1.v[6]  + m2.v[6],		m1.v[7]  + m2.v[7],
						m1.v[8]  + m2.v[8],		m1.v[9]  + m2.v[9],		m1.v[10] + m2.v[10],	m1.v[11] + m2.v[11],
						m1.v[12] + m2.v[12],	m1.v[13] + m2.v[13],	m1.v[14] + m2.v[14],	m1.v[15] + m2.v[15]);
}



inline Matrix4Df operator-(const Matrix4Df& m1, const Matrix4Df& m2)
{
	return Matrix4Df(	m1.v[0]  - m2.v[0],		m1.v[1]  - m2.v[1],		m1.v[2]  - m2.v[2],		m1.v[3]  - m2.v[3],
						m1.v[4]  - m2.v[4],		m1.v[5]  - m2.v[5],		m1.v[6]  - m2.v[6],		m1.v[7]  - m2.v[7],
						m1.v[8]  - m2.v[8],		m1.v[9]  - m2.v[9],		m1.v[10] - m2.v[10],	m1.v[11] - m2.v[11],
						m1.v[12] - m2.v[12],	m1.v[13] - m2.v[13],	m1.v[14] - m2.v[14],	m1.v[15] - m2.v[15]);
}



inline Matrix4Df operator*(const Matrix4Df& m1, const Matrix4Df& m2)
{
	Matrix4Df out;

	out.v[0]  =  m2.v[3]*m1.v[12] + m2.v[2]*m1.v[8]  + m2.v[0]*m1.v[0]  + m1.v[4]*m2.v[1];
	out.v[1]  =  m2.v[2]*m1.v[9]  + m2.v[1]*m1.v[5]  + m1.v[13]*m2.v[3] + m2.v[0]*m1.v[1];
	out.v[2]  =  m2.v[2]*m1.v[10] + m2.v[3]*m1.v[14] + m2.v[0]*m1.v[2]  + m1.v[6]*m2.v[1];
	out.v[3]  =  m2.v[2]*m1.v[11] + m1.v[15]*m2.v[3] + m2.v[1]*m1.v[7]  + m2.v[0]*m1.v[3];
	out.v[4]  =  m2.v[4]*m1.v[0]  + m2.v[6]*m1.v[8]  + m2.v[7]*m1.v[12] + m2.v[5]*m1.v[4];
	out.v[5]  =  m1.v[9]*m2.v[6]  + m1.v[1]*m2.v[4]  + m1.v[13]*m2.v[7] + m2.v[5]*m1.v[5];
	out.v[6]  =  m2.v[4]*m1.v[2]  + m2.v[6]*m1.v[10] + m2.v[7]*m1.v[14] + m2.v[5]*m1.v[6];
	out.v[7]  =  m1.v[3]*m2.v[4]  + m1.v[11]*m2.v[6] + m2.v[5]*m1.v[7]  + m1.v[15]*m2.v[7];
	out.v[8]  =  m1.v[4]*m2.v[9]  + m2.v[8]*m1.v[0]  + m2.v[10]*m1.v[8] + m1.v[12]*m2.v[11];
	out.v[9]  =  m2.v[9]*m1.v[5]  + m1.v[1]*m2.v[8]  + m2.v[10]*m1.v[9] + m1.v[13]*m2.v[11];
	out.v[10] =  m1.v[6]*m2.v[9]  + m1.v[14]*m2.v[11]+ m2.v[8]*m1.v[2]  + m2.v[10]*m1.v[10];
	out.v[11] =  m2.v[9]*m1.v[7]  + m1.v[15]*m2.v[11]+ m1.v[3]*m2.v[8]  + m2.v[10]*m1.v[11];
	out.v[12] =  m2.v[14]*m1.v[8] + m1.v[4]*m2.v[13] + m2.v[15]*m1.v[12]+ m1.v[0]*m2.v[12];
	out.v[13] =  m1.v[13]*m2.v[15]+ m1.v[9]*m2.v[14] + m2.v[13]*m1.v[5] + m1.v[1]*m2.v[12];
	out.v[14] =  m1.v[6]*m2.v[13] + m2.v[14]*m1.v[10]+ m1.v[2]*m2.v[12] + m1.v[14]*m2.v[15];
	out.v[15] =  m1.v[3]*m2.v[12] + m2.v[13]*m1.v[7] + m1.v[15]*m2.v[15]+ m1.v[11]*m2.v[14];

	return out;
}




// Negation


inline Matrix4Df operator-(const Matrix4Df& m)
{
	return Matrix4Df(	- m.v[0],  - m.v[1],  - m.v[2],  - m.v[3],
						- m.v[4],  - m.v[5],  - m.v[6],  - m.v[7],
						- m.v[8],  - m.v[9],  - m.v[10], - m.v[11],
						- m.v[12], - m.v[13], - m.v[14], - m.v[15]);
}


// Mixed scalar-matrix ops


inline Matrix4Df operator*(const float f, const Matrix4Df& m)
{
	return Matrix4Df(	f * m.v[0],		f * m.v[1],		f * m.v[2],		f * m.v[3],
						f * m.v[4],		f * m.v[5],		f * m.v[6],		f * m.v[7],
						f * m.v[8],		f * m.v[9],		f * m.v[10],	f * m.v[11],
						f * m.v[12],	f * m.v[13],	f * m.v[14],	f * m.v[15]);
}



inline Matrix4Df operator*(const Matrix4Df& m, const float f)
{
	return Matrix4Df(	f * m.v[0],		f * m.v[1],		f * m.v[2],		f * m.v[3],
						f * m.v[4],		f * m.v[5],		f * m.v[6],		f * m.v[7],
						f * m.v[8],		f * m.v[9],		f * m.v[10],	f * m.v[11],
						f * m.v[12],	f * m.v[13],	f * m.v[14],	f * m.v[15]);
}



// Mixed matrix vector ops


Vector Matrix4Df::Mul(const Vector& vec, const float w) const
{
	float resW = (*this)(3, 0) * vec[0] + (*this)(3, 1) * vec[1] + (*this)(3, 2) * vec[2] + (*this)(3, 3) * w;

	if(resW)
	{
		float ooResW = float(1) / resW;

		return Vector(	((*this)(0, 0) * vec[0] + (*this)(0, 1) * vec[1] + (*this)(0, 2) * vec[2] + (*this)(0, 3) * w) * ooResW,
							((*this)(1, 0) * vec[0] + (*this)(1, 1) * vec[1] + (*this)(1, 2) * vec[2] + (*this)(1, 3) * w) * ooResW,
							((*this)(2, 0) * vec[0] + (*this)(2, 1) * vec[1] + (*this)(2, 2) * vec[2] + (*this)(2, 3) * w) * ooResW);
	}
	else
	{
		return Vector(	(*this)(0, 0) * vec[0] + (*this)(0, 1) * vec[1] + (*this)(0, 2) * vec[2],
							(*this)(1, 0) * vec[0] + (*this)(1, 1) * vec[1] + (*this)(1, 2) * vec[2],
							(*this)(2, 0) * vec[0] + (*this)(2, 1) * vec[1] + (*this)(2, 2) * vec[2]);
	}
}



Vector Matrix4Df::MulPt(const Vector& vec) const
{
	return Vector(	(*this)(0, 0) * vec[0] + (*this)(0, 1) * vec[1] + (*this)(0, 2) * vec[2] + (*this)(0, 3),
						(*this)(1, 0) * vec[0] + (*this)(1, 1) * vec[1] + (*this)(1, 2) * vec[2] + (*this)(1, 3),
						(*this)(2, 0) * vec[0] + (*this)(2, 1) * vec[1] + (*this)(2, 2) * vec[2] + (*this)(2, 3));
}



Vector Matrix4Df::MulDir(const Vector& vec) const
{
	return Vector(	(*this)(0, 0) * vec[0] + (*this)(0, 1) * vec[1] + (*this)(0, 2) * vec[2],
						(*this)(1, 0) * vec[0] + (*this)(1, 1) * vec[1] + (*this)(1, 2) * vec[2],
						(*this)(2, 0) * vec[0] + (*this)(2, 1) * vec[1] + (*this)(2, 2) * vec[2]);
}


// Matrix ops



Matrix4Df& Matrix4Df::Transpose()
{
	float t;

	t = (*this)(1, 0); (*this)(1, 0) = (*this)(0, 1); (*this)(0, 1) = t;
	t = (*this)(2, 0); (*this)(2, 0) = (*this)(0, 2); (*this)(0, 2) = t;
	t = (*this)(3, 0); (*this)(3, 0) = (*this)(0, 3); (*this)(0, 3) = t;

	t = (*this)(2, 1); (*this)(2, 1) = (*this)(1, 2); (*this)(1, 2) = t;
	t = (*this)(3, 1); (*this)(3, 1) = (*this)(1, 3); (*this)(1, 3) = t;

	t = (*this)(3, 2); (*this)(3, 2) = (*this)(2, 3); (*this)(2, 3) = t;

	return *this;
}




void Matrix4Df::Invert()
{
	Matrix4Df inv = Matrix4Df::Invert(*this);
	*this = inv;
}



float Matrix4Df::Trace() const
{
	return (*this)(0, 0) + (*this)(1, 1) + (*this)(2, 2) + (*this)(3, 3);
}



float Matrix4Df::Determinant() const
{
	float d[4];

	d[0]  = v[5]*(v[15]*v[10]-v[11]*v[14]) + v[6]*(v[11]*v[13]-v[15]*v[9]) + v[7]*(v[14]*v[9]-v[10]*v[13]);
	d[1]  = v[1]*(v[11]*v[14]-v[15]*v[10]) + v[2]*(v[15]*v[9]-v[11]*v[13]) + v[3]*(v[10]*v[13]-v[14]*v[9]);	
	d[2]  = v[1]*(v[15]*v[6]-v[14]*v[7])   + v[2]*(v[7]*v[13]-v[5]*v[15])  + v[3]*(v[14]*v[5]-v[6]*v[13]);
	d[3]  = v[1]*(v[7]*v[10]-v[11]*v[6])   + v[2]*(v[11]*v[5]-v[9]*v[7])   + v[3]*(v[6]*v[9]-v[5]*v[10]);	

	return v[0] * d[0] + v[4] * d[1] + v[8] * d[2] + v[12] * d[3];
}




void Matrix4Df::SetZero()
{
	v[0]  = float(0);	v[1]  = float(0);	v[2]  = float(0);	v[3]  = float(0);
	v[4]  = float(0);	v[5]  = float(0);	v[6]  = float(0);	v[7]  = float(0);
	v[8]  = float(0);	v[9]  = float(0);	v[10] = float(0);	v[11] = float(0);
	v[12] = float(0);	v[13] = float(0);	v[14] = float(0);	v[15] = float(0);
}


void Matrix4Df::SetIdentity()
{
	v[0]  = float(1);	v[1]  = float(0);	v[2]  = float(0);	v[3]  = float(0);
	v[4]  = float(0);	v[5]  = float(1);	v[6]  = float(0);	v[7]  = float(0);
	v[8]  = float(0);	v[9]  = float(0);	v[10] = float(1);	v[11] = float(0);
	v[12] = float(0);	v[13] = float(0);	v[14] = float(0);	v[15] = float(1);
}



void Matrix4Df::SetScalar(const float f)
{
	v[0]  = f;	v[1]  = f;	v[2]  = f;	v[3]  = f;
	v[4]  = f;	v[5]  = f;	v[6]  = f;	v[7]  = f;
	v[8]  = f;	v[9]  = f;	v[10] = f;	v[11] = f;
	v[12] = f;	v[13] = f;	v[14] = f;	v[15] = f;
}



void Matrix4Df::SetDiagonal(const float f1, const float f2, const float f3, const float f4)
{
	v[0]  = f1;		v[1]  = float(0);	v[2]  = float(0);	v[3]  = float(0);
	v[4]  = float(0);	v[5]  = f2;		v[6]  = float(0);	v[7]  = float(0);
	v[8]  = float(0);	v[9]  = float(0);	v[10] = f3;		v[11] = float(0);
	v[12] = float(0);	v[13] = float(0);	v[14] = float(0);	v[15] = f4;
}


void Matrix4Df::Print(){
	for(int i =0; i<4;i++){
		for(int j=0;j<4;j++){
			fprintf(stderr,"%f ",v[i*4+j]);
		}
		fprintf(stderr,"\n");
	}
	fprintf(stderr,"\n");
}



#endif
