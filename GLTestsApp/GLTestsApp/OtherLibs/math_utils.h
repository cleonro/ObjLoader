/**
 * @file math_utils.h
 *
 * Math util operations.
 * 
 * ©Copyright Pie Medical Imaging B.V.
 * All rights are reserved. Reproduction or transmission in whole or in part, in
 * any form or by any means, electronic, mechanical or otherwise, is prohibited
 * without the prior written consent of the copyright owner
 */

/*
 * $Revision: 1 $
 * $Author: NetRom $
 * $Date: 13/02/2012 $
 */

/*
 * Prevent multiple inclusion.
 */
#pragma once

/*
 * Include files.
 */
#define _USE_MATH_DEFINES
#include <math.h>

#define deg2rad(x)	((float)M_PI * x / 180.0f)
#define rad2deg(x)	(180.0f * x / (float)M_PI )

