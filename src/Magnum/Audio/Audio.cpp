/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <type_traits>
#include <al.h>

#include "Magnum/Types.h"

namespace Magnum { namespace Audio {

/* Verify types */
static_assert(std::is_same<ALubyte, UnsignedByte>::value, "ALubyte is not the same as UnsignedByte");
/** @todo Why `ALbyte` is defined as `char` and not `signed char` on OSX? */
#ifndef __APPLE__
static_assert(std::is_same<ALbyte, Byte>::value, "ALbyte is not the same as Byte");
#else
static_assert(std::is_signed<ALbyte>::value && sizeof(ALbyte) == 1, "ALbyte does not have the same characteristics as Byte");
#endif
static_assert(std::is_same<ALushort, UnsignedShort>::value, "ALushort is not the same as UnsignedShort");
static_assert(std::is_same<ALshort, Short>::value, "ALshort is not the same as Short");
static_assert(std::is_same<ALuint, UnsignedInt>::value, "ALuint is not the same as UnsignedInt");
static_assert(std::is_same<ALint, Int>::value, "ALint is not the same as Int");
static_assert(std::is_same<ALsizei, Int>::value, "ALsizei is not the same as Int");
static_assert(std::is_same<ALfloat, Float>::value, "ALfloat is not the same as Float");
#ifndef MAGNUM_TARGET_GLES
static_assert(std::is_same<ALdouble, Double>::value, "ALdouble is not the same as Double");
#endif

/* Verify boolean values */
static_assert(AL_FALSE == false, "AL_FALSE is not the same as false");
static_assert(AL_TRUE == true, "AL_TRUE is not the same as true");

}}
