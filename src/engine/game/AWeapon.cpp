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

#include "App.h"
#include "AWeapon.h"

AWeapon::AWeapon() : SuperClass() {}
AWeapon::~AWeapon() = default;

void AWeapon::Tick() {
	SuperClass::Tick();

	Actor *parent = GetParent();
	if ( parent != nullptr ) {
		SetPosition( parent->GetPosition() );
		SetAngles( parent->GetAngles() );
	}
}

void AWeapon::Fire( const PLVector3 &pos, const PLVector3 &dir ) {}

void AWeapon::Deploy() {
	ShowModel( true );

	/* todo: make deploy sound */

	isWeaponDeployed = true;
}

void AWeapon::Holster() {
	ShowModel( false );

	/* todo: make holster sound */

	isWeaponDeployed = false;
}
