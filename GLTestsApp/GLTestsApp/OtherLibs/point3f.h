/**
 * @file point3f.h
 *
 * This file contains the declaration of the 3D point structure.
 *
 * ©Copyright Pie Medical Imaging B.V.
 * All rights are reserved. Reproduction or transmission in whole or in part, in
 * any form or by any means, electronic, mechanical or otherwise, is prohibited
 * without the prior written consent of the copyright owner
 */

/*
 * $Revision: 1 $
 * $Author: Netrom $
 * $Date: 26/01/2012 $
 */

/*
 * Prevent multiple inclusion.
 */
#pragma once

/************************************************************************
* CLASS_DEFINITION
************************************************************************/

/*
 * This class is used to store a 3D point coordinates.
 */
class C_POINT3F
{
/************************************************************************ 
*      LIFECYCLE 
************************************************************************/
public:
	/**
	 * Default constructor
	 */
	C_POINT3F(void);

	/**
	 * Destructor
	 */
	~C_POINT3F(void);

/************************************************************************ 
*      ACCESS MEMBERS 
************************************************************************/
public:
	/**
	 * Inline get the x coordinate value.
	 * @return float x coordinate
	 */
	float x() const { return p[0]; }

	/**
	 * Inline get the y coordinate value.
	 * @return float y coordinate
	 */
	float y() const { return p[1]; }

	/**
	 * Inline get the z coordinate value.
	 * @return float z coordinate
	 */
	float z() const { return p[2]; }

	/**
	 * Inline get a reference to x coordinate.
	 * @return float& x coordinate
	 */
	float& x() { return p[0]; }
	
	/**
	 * Inline get a reference to y coordinate.
	 * @return float& y coordinate
	 */
	float& y() { return p[1]; }

	/**
	 * Inline get a reference to z coordinate.
	 * @return float& z coordinate
	 */
	float& z() { return p[2]; }

	/**
	 * Inline get a constant reference to coordinates vector.
	 * @return const float* coordinates vector
	 */
	const float * get() const { return p; }
	
	/**
	 * Inline get a reference to coordinates vector.
	 * @return float* coordinates vector
	 */
	float * get() { return p; }

/************************************************************************ 
*      MEMBER VARIABLES 
************************************************************************/
private:
	float p[3]; //point coordinates

};

