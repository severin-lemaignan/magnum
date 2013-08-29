#ifndef Magnum_Audio_AbstractImporter_h
#define Magnum_Audio_AbstractImporter_h
/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013 Vladimír Vondruš <mosra@centrum.cz>

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

/** @file Audio/AbstractImporter.h
 * @brief Class Magnum::Audio::AbstractImporter
 */

#include <PluginManager/AbstractPlugin.h>

#include "Magnum.h"
#include "Audio/Buffer.h"

namespace Magnum { namespace Audio {

/**
@brief Base for audio importer plugins

@section Audio-AbstractImporter-subclassing Subclassing

Plugin implements function doFeatures(), doIsOpened(), one of or both
doOpenData() and doOpenFile() functions, function doClose() and data access
functions doFormat(), doFrequency() and doData().

You don't need to do most of the redundant sanity checks, these things are
checked by the implementation:

-   Functions doOpenData() and doOpenFile() are called after the previous file
    was closed, function doClose() is called only if there is any file opened.
-   Function doOpenData() is called only if @ref Feature::OpenData is
    supported.
-   All `do*()` implementations working on opened file are called only if
    there is any file opened.
*/
class MAGNUM_AUDIO_EXPORT AbstractImporter: public PluginManager::AbstractPlugin {
    CORRADE_PLUGIN_INTERFACE("cz.mosra.magnum.Audio.AbstractImporter/0.1")

    public:
        /**
         * @brief Features supported by this importer
         *
         * @see Features, features()
         */
        enum class Feature: UnsignedByte {
            /** Opening files from raw data using openData() */
            OpenData = 1 << 0
        };

        /**
         * @brief Features supported by this importer
         *
         * @see features()
         */
        typedef Containers::EnumSet<Feature, UnsignedByte> Features;

        /** @brief Default constructor */
        explicit AbstractImporter();

        /** @brief Plugin manager constructor */
        explicit AbstractImporter(PluginManager::AbstractManager* manager, std::string plugin);

        /** @brief Features supported by this importer */
        Features features() const { return doFeatures(); }

        /** @brief Whether any file is opened */
        bool isOpened() const { return doIsOpened(); }

        /**
         * @brief Open raw data
         *
         * Closes previous file, if it was opened, and tries to open given
         * file. Available only if @ref Feature::OpenData is supported. Returns
         * `true` on success, `false` otherwise.
         * @see features(), openFile()
         */
        bool openData(Containers::ArrayReference<const unsigned char> data);

        /**
         * @brief Open file
         *
         * Closes previous file, if it was opened, and tries to open given
         * file. Returns `true` on success, `false` otherwise.
         * @see features(), openData()
         */
        bool openFile(const std::string& filename);

        /** @brief Close file */
        void close();

        /** @{ @name Data access */

        /** @brief Sample format */
        Buffer::Format format() const;

        /** @brief Sample frequency */
        UnsignedInt frequency() const;

        /** @brief Sample data */
        Containers::Array<unsigned char> data();

        /*@}*/

    #ifndef DOXYGEN_GENERATING_OUTPUT
    private:
    #else
    protected:
    #endif
        /** @brief Implementation for features() */
        virtual Features doFeatures() const = 0;

        /** @brief Implementation for isOpened() */
        virtual bool doIsOpened() const = 0;

        /** @brief Implementation for openData() */
        virtual void doOpenData(Containers::ArrayReference<const unsigned char> data);

        /**
         * @brief Implementation for openFile()
         *
         * If @ref Feature::OpenData is supported, default implementation opens
         * the file and calls @ref doOpenData() with its contents.
         */
        virtual void doOpenFile(const std::string& filename);

        /** @brief Implementation for close() */
        virtual void doClose() = 0;

        /** @brief Implementation for format() */
        virtual Buffer::Format doFormat() const = 0;

        /** @brief Implementation for frequency() */
        virtual UnsignedInt doFrequency() const = 0;

        /** @brief Implementation for data() */
        virtual Containers::Array<unsigned char> doData() = 0;
};

}}

#endif
