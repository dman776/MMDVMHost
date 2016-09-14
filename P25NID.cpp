/*
*   Copyright (C) 2016 by Jonathan Naylor G4KLX
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation; either version 2 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "P25NID.h"
#include "P25Defines.h"
#include "P25Utils.h"

#include <cstdio>
#include <cassert>

CP25NID::CP25NID() :
m_duid(0U),
m_nac(0U)
{
}

CP25NID::~CP25NID()
{
}

void CP25NID::process(unsigned char* data)
{
	assert(data != NULL);

	unsigned char nid[P25_NID_LENGTH_BYTES];

	CP25Utils::decode(data, nid, 48U, 114U);

	// XXX Process FEC here

	m_duid = nid[1U] & 0x0FU;

	m_nac  = (nid[0U] << 4) & 0xFF0U;
	m_nac |= (nid[1U] >> 4) & 0x00FU;

	CP25Utils::encode(nid, data, 48U, 114U);
}

unsigned char CP25NID::getDUID() const
{
	return m_duid;
}

unsigned int CP25NID::getNAC() const
{
	return m_nac;
}