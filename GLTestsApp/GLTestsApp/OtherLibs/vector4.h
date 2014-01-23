/**
 * @file vector4.h
 *
 * C_VECTOR4 class declaration.
 * 
 * ©Copyright Pie Medical Imaging B.V.
 * All rights are reserved. Reproduction or transmission in whole or in part, in
 * any form or by any means, electronic, mechanical or otherwise, is prohibited
 * without the prior written consent of the copyright owner
 */

/*
 * $Revision: 1 $
 * $Author: NetRom $
 * $Date:  13/02/2012$
 */

/*
 * Prevent multiple inclusion.
 */
#pragma once

/*
 * Include files
 */
#include "vector3.h"

/************************************************************************
* CLASS_DEFINITION
************************************************************************/

/*
 * This class contains a four dimensional vector components and math operations with this
 * type of structure (multiplication with numbers, vector sum)
 */
class C_VECTOR4
{
/************************************************************************ 
*      LIFECYCLE 
************************************************************************/
public:
	/**
	 * Default constructor.
	 */
	C_VECTOR4(void);

	/**
	  * Copy constructor                                                                    
	  */
	C_VECTOR4(const C_VECTOR4&);

	/**
	  * Custom constructor                                                                    
	  */
	C_VECTOR4(const float& x, const float& y, const float &z, const float& w);

	/**
	  * Custom constructor, from a three dimensional vector and a scalar                                                                    
	  */
	C_VECTOR4(const C_VECTOR3&, const float& w);

	/**
	 * Destructor.
	 */
	~C_VECTOR4(void);

/************************************************************************ 
*      OPERATIONS 
************************************************************************/

public:
	/**
	  * Multiplication with a number                                                                    
	  */
	C_VECTOR4 operator*(const float& n);

	/**
	  * Vector addition                                                                    
	  */
	C_VECTOR4 operator+(const C_VECTOR4& v);

	/**
	  * Normalize operation.
	  * @return bool shows if vector can be normalized (norm is bigger than zero).
	  */
	bool normalize();

/************************************************************************ 
*      ACCESS MEMBERS 
************************************************************************/

public:
	/*
	 * Access functions to class members.
	 */
	float&		x() {return m_x;}
	float&		y() {return m_y;}
	float&		z() {return m_z;}
	float&		w() {return m_w;}
	const float&	x() const {return m_x;}
	const float&	y() const {return m_y;}
	const float&	z() const {return m_z;}
	const float&	w() const {return m_w;}

	C_VECTOR3&		vec3() {return m_v3;}
	const C_VECTOR3&	vec3() const {return m_v3;}

	/**
	  * Access operator                                                                    
	  */
	float&		operator[](int i) {return m_v[i];}
	const float&	operator[](int i) const{return m_v[i];}

	/**
	  * Equal operator                                                                    
	  */
	C_VECTOR4&	operator=(const C_VECTOR4& v);

	/**
	  * Vector norm.                                                                    
	  */
	float		norm();

/************************************************************************ 
*      MEMBER VARIABLES 
************************************************************************/

protected:	
	/*
	 * C_VECTOR4 values can be accessed either by separate components on coordinate axes,
	 * or through a three dimensional vector and a fourth component,
	 * or through a float pointer
	 */
	union
	{
		struct  
		{
			float m_x;		//x component
			float m_y;		//y component
			float m_z;		//z component
			float m_w;		//w component
		};

		struct  
		{
			C_VECTOR3	m_v3;	//three dimensional part
			float		m_w;	//fourth dimension
		};

		float m_v[4]; //vector values
	};
};//end class C_VECTOR4

/**
 * Vector multiplication with a number
 */
C_VECTOR4 operator*(const float& n, const C_VECTOR4& v);