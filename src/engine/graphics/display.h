/* OpenHoW
 * Copyright (C) 2017-2020 TalonBrave.info and Others (see CONTRIBUTORS)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <PL/pl_graphics_camera.h>

#define MIN_DISPLAY_WIDTH   640
#define MIN_DISPLAY_HEIGHT  480

struct VideoPreset {
	VideoPreset( int w, int h ) : width( w ), height( h ) {}

	int width{ 0 };
	int height{ 0 };
};

void Display_Initialize( void );
void Display_Shutdown( void );
void Display_UpdateState( void );

bool Display_AppendVideoPreset( int width, int height );
int Display_GetNumVideoPresets();
const VideoPreset *Display_GetVideoPreset( unsigned int idx );

void Display_UpdateViewport( int x, int y, int width, int height );

// debugging
void Display_GetFramesCount( unsigned int *fps, unsigned int *ms );

void Display_Draw( double delta );
void Display_Flush( void );

extern const char *supportedTextureFormats[];
