/*
 * Crypto.h
 *
 * Copyright (C) 2013 - Ryan Babb
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CRYPTO_H
#define CRYPTO_H

// Helper functions to assit encryption/decryption operations

#include <string>

/* xor_scrabmle():
 *  Performe bit-wise XOR encryption on a
 *  file acoording to a key
 */
void xor_scramble(const char *key,
                  const std::string &fname,
                  const std::string &fname_out = "")

#endif // CRYPTO_H