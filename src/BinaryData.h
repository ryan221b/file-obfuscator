/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * BinaryData.h
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

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#ifndef BINARYDATA_H
#define BINARYDATA_H

// Byte type
typedef char byte;

class BinaryData
{
	public:
		BinaryData() : data(NULL), d_size(0) {}
		~BinaryData()
		{
			delete[] data;
			in_fileHnd.close();
			out_fileHnd.close();
		}

		// Data I/O Exception class:
		class BinDataError : public std::runtime_error
		{
		public:
			BinDataError(const std::string &msg) : std::runtime_error(msg) {}
		};

		// May throw BinDataExceptions
		void readData(std::string filename, const int &size = 0);
		void writeData(std::string filename, const int &size = 0);

		byte *getData() const;
		const int getSize() const;


	private:
		// Pointer to data
		byte *data;		
		// Size of data
		int d_size;
		// File handlers
		std::ifstream in_fileHnd;
		std::ofstream out_fileHnd;
};

#endif // BINARYDATA_H

