/*
 * SdlImports.h
 *
 *  Created on: 5/05/2012
 *      Author: Azriel
 */

#ifndef __IM_AZRIEL_COMMON_IMPORTS__SDLIMPORTS_H_
#define __IM_AZRIEL_COMMON_IMPORTS__SDLIMPORTS_H_

#ifdef __WIN32__
	#include "SDL.h"
	#include "SDL_image.h"
#else
	#ifdef __linux__
		#include "SDL/SDL.h"
		#include "SDL/SDL_image.h"
	#endif // end #ifdef __linux__
#endif // end #ifdef __WIN32__

#endif /* __IM_AZRIEL_COMMON_IMPORTS__SDLIMPORTS_H_ */
