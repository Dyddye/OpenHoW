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

/************************************************************/
/* Hir Skeleton Format */

PL_PACKED_STRUCT_START( HirBone )
	int32_t parent;
	int16_t coords[ 3 ];
	int8_t unknown[ 10 ];
PL_PACKED_STRUCT_END( HirBone )

typedef enum HirSkeletonBone {
	PELVIS = 0,
	SPINE,
	HEAD,

	UPPER_ARM_L,
	LOWER_ARM_L,
	HAND_L,

	UPPER_ARM_R,
	LOWER_ARM_R,
	HAND_R,

	UPPER_LEG_L,
	LOWER_LEG_L,
	FOOT_L,

	UPPER_LEG_R,
	LOWER_LEG_R,
	FOOT_R,

	MAX_BONES
} HirSkeletonBone;

typedef struct HirHandle {
	PLModelBone *bones;
	unsigned int num_bones;
} HirHandle;
HirHandle *Hir_LoadFile( const char *path );
void Hir_DestroyHandle( HirHandle *handle );
