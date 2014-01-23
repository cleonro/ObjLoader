/**
 * @file matrix4.h
 *
 * C_MATRIX4 class (a four dimensional square matrix) declaration.
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
#include "vector4.h"
#include "quaternion.h"

/************************************************************************
* CLASS_DEFINITION
************************************************************************/

/*
 * Class description
 */
class C_MATRIX4
{
/************************************************************************ 
*      LIFECYCLE 
************************************************************************/
public:
	/**
	 * Default constructor.
	 */
	C_MATRIX4(void);

	/**
	  * Copy constructor                                                                    
	  */
	C_MATRIX4(const C_MATRIX4& m);

	/**
	  * Constructor from matrix columns                                                                    
	  */
	C_MATRIX4(const C_VECTOR4& c0, const C_VECTOR4& c1, const C_VECTOR4& c2, const C_VECTOR4& c3);

	/**
	 * Destructor.
	 */
	~C_MATRIX4(void);

/************************************************************************ 
*      OPERATIONS 
************************************************************************/
public:
	/**
	  * Transform a rotation matrix in an unitary quaternion.                                                                    
	  * @return C_QUATERNION
	  */
	C_QUATERNION to_quaternion();

	/**
	 * Matrix multiplication operator
	 */
	C_MATRIX4 operator*(const C_MATRIX4& m) const;

	/**
	 * Transpose operation
	 */
	C_MATRIX4 transpose() const;

/************************************************************************ 
*      ACCESS MEMBERS 
************************************************************************/
	
	/**
	  * Equal operator                                                                    
	  */
	C_MATRIX4&	operator=(const C_MATRIX4& m);

	/**
	  * Access operator                                                                    
	  */
	float&		operator()(unsigned int row, unsigned int column);
	const float&	operator()(unsigned int row, unsigned int column) const;

	/**
	  * Access to vector storage                                                                    
	  */
	float*		matrix_v() {return m_v;}
	const float*	matrix_v() const {return m_v;}

/************************************************************************ 
*      MEMBER VARIABLES 
************************************************************************/

protected:
	/*
	 * Matrix is considered to be column major.
	 * C_MATRIX4 values can be accessed individual, or through column vectors,
	 * or through a float pointer.
	 */
	union 
	{
		struct  
		{
			float m_00, m_10, m_20, m_30;	//first column
			float m_01, m_11, m_21, m_31;	//second column
			float m_02, m_12, m_22, m_32;	//first column
			float m_03, m_13, m_23, m_33;	//second column
		};

		struct  
		{
			C_VECTOR4 m_c0;			//first column
			C_VECTOR4 m_c1;			//second column
			C_VECTOR4 m_c2;			//third column
			C_VECTOR4 m_c3;			//fourth column
		};

		float m_v[16];				//matrix values arranged in a 16 dim float vector
	};	
};//end class C_CLASS_NAME