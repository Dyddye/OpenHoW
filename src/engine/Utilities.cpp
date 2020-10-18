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

#include <PL/platform_filesystem.h>

#include "Utilities.h"

#if defined(COMPILE_ENGINE)
# include "../engine/engine.h"
#endif

/****************************************************/
/* Logs */

void u_init_logs( const char* log_path ) {

}

/****************************************************/
/* Memory */

unsigned long u_unmangle( void* source, void* destination ) {
	/* todo */

	return 0;
}

void* u_realloc( void* ptr, size_t new_size, bool abort_on_fail ) {
	void* mem = realloc( ptr, new_size );
	if ( mem == NULL && new_size > 0 ) {
		if ( abort_on_fail ) {
			Error( "Failed to allocate %u bytes!\n", new_size );
		}

		Warning( "Failed to allocate %u bytes!\n", new_size );
		return NULL;
	}

	return mem;
}

void* u_alloc( size_t num, size_t size, bool abort_on_fail ) {
	void* mem = calloc( num, size );
	if ( mem == NULL && abort_on_fail ) {
		Error( "Failed to allocate %u bytes!\n", size * num );
	}
	return mem;
}

/****************************************************/
/* Filesystem */

const char* u_scan( const char* path, const char** preference ) {
	static char find[PL_SYSTEM_MAX_PATH];
	while ( *preference != NULL ) {
		snprintf( find, sizeof( find ), "%s.%s", path, *preference );
		if ( plFileExists( find ) ) {
			//LogDebug( "Found \"%s\"\n", find );
			return find;
		}
		preference++;
	}

	LogDebug( "Failed to find \"%s\"\n", path );
	return "";
}

const char* u_find2( const char* path, const char** preference, bool abort_on_fail ) {
	static char out[PL_SYSTEM_MAX_PATH];
	memset( out, 0, sizeof( out ) );

	strncpy( out, u_scan( path, preference ), sizeof( out ) );
	if ( plIsEmptyString( out ) ) {
		if ( abort_on_fail ) {
			Error( "Failed to find \"%s\"!\n", path );
		}

		Warning( "Failed to find \"%s\"!\n", path );
		return NULL;
	}

	//LogDebug( "Found \"%s\"\n", out );
	return out;
}

char *u_new_filename( char *dst, const char *src, const char *ext ) {
	strncpy( dst, src, strlen( src ) - 3 );
	dst[ strlen( src ) - 3 ] = '\0';
	strcat( dst, ext );
	return dst;
}
