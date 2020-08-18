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

#include "Resource.h"

namespace ohw {
	class TextureResource : public Resource {
	public:
		IMPLEMENT_RESOURCE_CLASS( TextureResource )

		explicit TextureResource( const std::string &path, unsigned int flags = 0, bool persist = false, bool abortOnFail = false );
		~TextureResource();

		PLTexture *GetInternalTexture() { return texturePtr; }

		PL_INLINE unsigned int GetWidth() const { return texturePtr->w; }
		PL_INLINE unsigned int GetHeight() const { return texturePtr->h; }

		PL_INLINE size_t GetTextureSize() const { return texturePtr->size; }

		enum {
			FLAG_DISCARD        = ( 1 << 0 ),   // Convert the background colour to alpha
			FLAG_NOMIPS         = ( 1 << 1 ),   // Will not generate mipmaps
			FLAG_NEAREST        = ( 1 << 2 ),   // Will use nearest filtering
		};

	private:
		PLTexture *texturePtr{ nullptr };
	};

	using SharedTextureResourcePointer = SharedResourcePointer< TextureResource >;
}
