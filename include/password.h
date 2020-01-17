/** 
 *  password v1.0.0 Cryptographically-secure password utility
 *  Copyright (C) 2020 Jose Fernando Lopez Fernandez
 *  
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#ifndef PROJECT_INCLUDES_PASSWORD_H
#define PROJECT_INCLUDES_PASSWORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include <sys/random.h>

#ifndef PROGRAM_NAME
#define PROGRAM_NAME "password"
#endif

#ifndef DEFAULT_LENGTH
#define DEFAULT_LENGTH (16)
#endif

#ifndef DEFAULT_NUMBER
#define DEFAULT_NUMBER (1)
#endif

#include "str.h"

#endif /* PROJECT_INCLUDES_PASSWORD_H */
