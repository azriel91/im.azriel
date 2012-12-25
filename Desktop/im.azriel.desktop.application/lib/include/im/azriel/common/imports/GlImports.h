/*
 * GlImports.h
 *
 *  Created on: 6/05/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_COMMON_IMPORTS__GLIMPORTS_H_
#define __IM_AZRIEL_COMMON_IMPORTS__GLIMPORTS_H_

#ifdef __WIN32__
	#include <gl/gl.h>
#else
	#ifdef __linux__
		#include <GL/gl.h>
		#include <GL/glut.h>
	#endif // end #ifdef __linux__
#endif // end #ifdef _WIN32

#endif /* __IM_AZRIEL_COMMON_IMPORTS__GLIMPORTS_H_ */
