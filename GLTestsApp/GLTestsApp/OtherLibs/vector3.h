/**
 * @file vector3.h
 *
 * C_VECTOR3 class declaration.
 * 
 * ©Copyright Pie Medical Imaging B.V.
 * All rights are reserved. Reproduction or transmission in whole or in part, in
 * any form or by any means, electronic, mechanical or otherwise, is prohibited
 * without the prior written consent of the copyright owner
 */

/*
 * $Revision: 1 $
 * $Author: NetRom $
 * $Date:  10/02/2012$
 */

/*
 * Prevent multiple inclusion.
 */
#pragma once

/*
 * Include files
 */

/************************************************************************
* CLASS_DEFINITION
************************************************************************/

/*
 * This class contains a three dimensional vector components and math operations with this
 * type of structure (cross and scalar products, multiplication with numbers,...)
 */
class C_VECTOR3
{
/************************************************************************ 
*      LIFECYCLE 
************************************************************************/
public:
	/**
	 * Default constructor.
	 */
	C_VECTOR3(void);

	/**
	  * Copy constructor                                                                    
	  */
	C_VECTOR3(const C_VECTOR3&);

	/**
	  * Custom constructor                                                                    
	  */
	C_VECTOR3(const float& x, const float& y, const float &z);

	/**
	 * Destructor.
	 */
	~C_VECTOR3(void);

/************************************************************************ 
*      OPERATIONS 
************************************************************************/

public:
	/**
	 * Cross product                                                                    
	 */
	C_VECTOR3 operator*(const C_VECTOR3& v) const;

	/**
	 * Scalar (dot) product                                                                    
	 */
	float dot(const C_VECTOR3& v) const;

	/**
	  * Multiplication with a number                                                                    
	  */
	C_VECTOR3 operator*(const float& n) const;

	/**
	 * Vector addition                                                                    
	 */
	C_VECTOR3 operator+(const C_VECTOR3& v) const;

	/**
	 * Normalize operation.
	 * @return bool shows if vector can be normalized (norm is bigger than zero).
	  */
	bool normalize();

	/**
	 * @brief test equality
	 */
	bool operator==(const C_VECTOR3& v) const;

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
	const float&	x() const {return m_x;}
	const float&	y() const {return m_y;}
	const float&	z() const {return m_z;}

	/**
	 * Access to vector storage                                                                    
	 */
	float*		Vector3V()	 {return m_v;}
	const float*	Vector3V() const {return m_v;}

	/**
	  * Access operator                                                                    
	  */
	float&		operator[](int i) {return m_v[i];}
	const float&	operator[](int i) const{return m_v[i];}

	/**
	  * Equal operator                                                                    
	  */
	C_VECTOR3&	operator=(const C_VECTOR3& v);

	/**
	  * Vector norm.                                                                    
	  */
	float		norm();


/************************************************************************ 
*      MEMBER VARIABLES 
************************************************************************/

protected:	
	/*
	 * C_VECTOR3 values can be accessed either by separate components on coordinate axes,
	 * or through a float pointer
	 */
	union
	{
		struct  
		{
			float m_x;	//x component
			float m_y;	//y component
			float m_z;	//z component
		};
		float m_v[3];		//vector values
	};
};//end class C_VECTOR3

/**
 * Vector multiplication with a number
 */
C_VECTOR3 operator*(const float& n, const C_VECTOR3& v);