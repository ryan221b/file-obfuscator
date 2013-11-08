// Crypto.cpp
//
// Copyright (C) 2013 - Ryan Babb
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "Crypto.h"
#include "BinaryData.h"

/* xor_scrabmle():
 *  Performe bit-wise XOR encryption on a
 *  file acoording to a key
 */
void xor_scramble(const std::string &key,
                  const std::string &fname,
                  const std::string &fname_out = "")
{
	BinaryData binData;

	// Read data:
	binData.readData(fname);

	// xor loop:
	for (int b = 0, k = 0; b < binData.getSize(); ++b, ++k)
	{
		if (k >= key.size()) k = 0;
		binData[b] ^= key[k];
	}

	// Write data:
	std::string lfname_out = fname_out ? fname_out : fname + ".obf";
	binData.writeData(lfname_out);

	return;
}