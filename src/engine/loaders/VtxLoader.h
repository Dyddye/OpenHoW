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

#define VTX_MAX_VERTICES  4096

PL_EXTERN_C

PL_PACKED_STRUCT_START( VtxCoord )
	int16_t v[ 3 ];
	uint16_t bone_index;
PL_PACKED_STRUCT_END( VtxCoord )

typedef struct VtxHandle {
  struct PLVertex *vertices;
  unsigned int num_vertices;
} VtxHandle;

VtxHandle *Vtx_LoadFile(const char *path);
void Vtx_DestroyHandle(VtxHandle *handle);

PL_EXTERN_C_END
