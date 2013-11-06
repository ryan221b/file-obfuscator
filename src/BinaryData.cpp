/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * BinaryData.cpp
 * Copyright (C) 2013 Ryan Babb <ryan221b@gmail.com>
 * 
 * FileObfuscator is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FileObfuscator is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "BinaryData.h"
#include <cassert>
using namespace std;

/* readData():
 * 	Opens file 'filename', allocates space for 'size' bytes
 *  on heap and reads binary contents into 'data' member.
 * 
 *  May throw BinDataError !
 */
void BinaryData::readData(const string &filename, const int &size)
{
	// Open file
	in_fileHnd.open(filename.c_str(), ios::in|ios::binary|ios::ate);

	// Check if open was succesfull
	if (!in_fileHnd.is_open())
	{
		BinaryData::BinDataError err("Unable to open "+filename);
		//err.setInfo("Unable to open "+filename);
		throw(err);
	}

	// Allocate size: if size = 0, read entire file
	d_size = size ? size : int(in_fileHnd.tellg()); 
	if (data != NULL) delete[] data;	// Free space if data if full
	data = new byte[d_size];
	
	// Set cursor at begining of file and read data
	in_fileHnd.seekg(0, ios::beg);
	in_fileHnd.read(data, d_size);

	// Close file
	in_fileHnd.close();
}


/* writeData():
 *	Opens file 'filename', and writes 'size' bytes to it
 * 
 *  May throw BinDataError !
 */
void BinaryData::writeData(const string &filename, const int &size)
{
	// Open file
	out_fileHnd.open(filename.c_str(), ios::out|ios::binary);
	
	// Check if open was succesfull
	if (!out_fileHnd.is_open())
	{
		BinaryData::BinDataError err("Unable to open "+filename);
		//err.setInfo("Unable to open "+filename);
		throw(err);
	}
	
	// If size = 0, write entire data
	int lsize = size ? size : d_size;
	out_fileHnd.write(data, lsize);
	
	// Close file
	out_fileHnd.close();
}


/* getData():
 *	Returns pointer to 'data'
 */
byte *BinaryData::getData() const
{
	return data;
}

/* operator[]():
 *  Return reference to 'i'th element of
 *  underlying data array
 */
byte &operator [](int i)
{
	assert(i < d_size);
	return data[i];
}

/* getSize():
 *	Returns size of 'data'
 */
const int BinaryData::getSize() const
{
	return d_size;
}
