/**
 * @file draw_utils.h
 *
 * C_DRAW_UTILS class definition.
 * 
 * ©Copyright Pie Medical Imaging B.V.
 * All rights are reserved. Reproduction or transmission in whole or in part, in
 * any form or by any means, electronic, mechanical or otherwise, is prohibited
 * without the prior written consent of the copyright owner
 */

/*
 * $Revision: 1 $
 * $Author: NetRom $
 * $Date: 9/2/2012 $
 */

/*
 * Prevent multiple inclusion.
 */
#pragma once

/*
 * Shortcut to singleton instance
 */
#define DrawUtils C_DRAW_UTILS::get_instance()

/*
 * Include files
 */
#include <windows.h>
#include <GL/GL.h>
#include "vector3.h"
#include "vector4.h"

/************************************************************************
* CLASS_DEFINITION
************************************************************************/

/*
 * C_DRAW_UTILS encapsulate utility operations related to opengl
 * like font creation and rendering, more complex draw primitives (circle,...),...
 */
class C_DRAW_UTILS
{
/************************************************************************ 
*      LIFECYCLE 
************************************************************************/
protected:
	/**
	 * Construct instance using a device context.
	 * Class is a singleton, so constructor and destructor are protected.
	 */
	C_DRAW_UTILS(void);

	/**
	 * Destructor.
	 */
	~C_DRAW_UTILS(void);

/************************************************************************ 
*      OPERATIONS 
************************************************************************/
public:
	/**
	 * Builds fonts opengl draw lists.
	 * @param input in: hdc Handle Device Context used for font creation.
	 */
	GLvoid build_font(HDC hdc);

	/**
	  * Delete fonts                                                                    
	  */
	GLvoid kill_font(GLvoid);

	/**
	  * Draws text at specified (raster) position on screen, coordinates are affected by opengl modelview matrix.
	  * @param input in: text to be rendered
	  *		 in: C_VECTOR3 3d position
	  *		 in: C_VECTOR4 text color	
	  */
	GLvoid draw_text2d(const char *text, const C_VECTOR3& position, const C_VECTOR4& color);

	/**
	 * Compute size in x, y coordinates for a text rendered with draw_text2d.
	 * @param [in] text to be rendered
	 * @param [out] x size
	 * @param [out] y size                                                            
	 */
	void draw_text2d_size(const char* text, float& xsize, float& ysize);

	/**
	  * Draw coordinates axes.
	  * @param input in: axis length
	  *		 in: axis line width
	  */
	void C_DRAW_UTILS::draw_axes(GLfloat length, GLfloat linewidth = 1.0f);

	/**
	  * Draw a cube with axis length 2, centered in origin                                                                    
	  */
	void draw_cube();

	/**
	  * Draw a box described by minimum and maximum coordinate vectors.
	  * @param input in: min vector with minimum coordinates
	  *		 in: max vector with maximum coordinates
	  */
	void draw_box(C_VECTOR3 min, C_VECTOR3 max);

/************************************************************************ 
*      ACCESS MEMBERS 
************************************************************************/
public:
	/**
	 * Get singleton instances count.
	 * @return instances counter                                                       
	 */
	static int		count() {return m_count;} 

	/**
	  * Get the singleton instance.
	  * @return C_DRAW_UTILS& reference.
	  */
	static C_DRAW_UTILS&	get_instance();

	/**
	 * Delete singleton instance.
	 *                                                             
	 */
	void			delete_instance();

/************************************************************************ 
*      MEMBER VARIABLES 
************************************************************************/
protected:
	GLuint			m_font_base;	//fonts drawing opengl lists
	GLYPHMETRICSFLOAT	m_gmf[256];	//storage for information about outline font characters
	GLfloat			m_cube[24];	//cube vertices

	static int		m_count;	//count singleton instances

};//end class C_DRAW_UTILS

#ifdef _DEBUG
//global functions
void generate_point(int n, int m, float& x, float& y, float& z,
	float& nx, float& ny, float& nz,
	float& red, float& green, float& blue, float& alpha);

void add_normals(int index, float nx0, float ny0, float nz0,
	float nx1, float ny1, float nz1,
	float nx2, float ny2, float nz2);

void add_colors(int index, float red0, float green0, float blue0, float alpha0,
	float red1, float green1, float blue1, float alpha1,
	float red2, float green2, float blue2, float alpha2);

void generate_data();

void draw_util_mesh();

void draw_axis(C_VECTOR3 origin, C_VECTOR3 direction, float length);

void draw_axes(float length);
//end global functions
#endif // _DEBUG