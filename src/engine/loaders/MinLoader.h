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

PL_EXTERN_C

PL_PACKED_STRUCT_START( MinTriangle )
#if 0
	int8_t uv_coords[ 6 ];
	uint16_t vertex_indices[ 3 ];
	uint16_t normal_indices[ 3 ];
	uint16_t unknown0;
	uint32_t texture_index;
	uint16_t unknown1[ 4 ];
#else
	char u0[ 24 ];
#endif
PL_PACKED_STRUCT_END( MinTriangle )

typedef struct MinHandle {
	unsigned int blah;
} MinHandle;
MinHandle *Min_LoadFile( const char *path );

PL_EXTERN_C_END
