/**
 * @file quaternion.h
 *
 * C_QUATERNION class definition.
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

/*
 * Forward declarations.
 */
class C_MATRIX4;

/************************************************************************
* CLASS_DEFINITION
************************************************************************/

/*
 * Class description
 */
class C_QUATERNION : public C_VECTOR4
{
/************************************************************************ 
*      LIFECYCLE 
************************************************************************/

public:
	/**
	 * Default constructor.
	 */
	C_QUATERNION(void);

	/**
	  * Copy constructor                                                                    
	  */
	C_QUATERNION(const C_QUATERNION&);

	/**
	  * Custom constructor                                                                    
	  */
	C_QUATERNION(const float& x, const float& y, const float &z, const float& w);

	/**
	  * Custom constructor, from a three dimensional vector and a scalar                                                                    
	  */
	C_QUATERNION(const C_VECTOR3&, const float& w);

	/**
	 * Destructor.
	 */
	~C_QUATERNION(void);

/************************************************************************ 
*      OPERATIONS 
************************************************************************/
	
public:
	/**
	  * Quaternion multiplication                                                                    
	  */
	C_QUATERNION	operator*(const C_QUATERNION& q) const;

	/**
	  * Quaternion transpose operation (vector part is multiplied with -1).                                                                    
	  */
	C_QUATERNION	transpose() const;

	/**
	  * Transform an unitary quaternion in a rotation matrix                                                                    
	  * @return C_MATRIX4 rotation matrix 
	  */
	C_MATRIX4	to_matrix() const;

	/**
	 * Construct a quaternion that describe the shortest rotation of an axis over the second axis.
	 * @param input in: axis_1
	 * @param input in: axis_2 
	 * @return bool shows if rotation is possible.
	 */
	bool		shortest_rotation(C_VECTOR3 axis_1, C_VECTOR3 axis_2);

/************************************************************************ 
*      ACCESS MEMBERS 
************************************************************************/

/************************************************************************ 
*      MEMBER VARIABLES 
************************************************************************/
	
};//end class C_QUATERNION