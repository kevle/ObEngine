/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_THEME_LOADER_HPP
#define TGUI_THEME_LOADER_HPP


#include <TGUI/Config.hpp>
#include <SFML/System/String.hpp>
#include <memory>
#include <string>
#include <vector>
#include <map>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Base class for theme loader implementations
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API BaseThemeLoader
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Virtual destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual ~BaseThemeLoader() = default;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Optionally already do some work when only the primary parameter is known yet
        ///
        /// @param primary    Primary parameter of the loader (filename of the theme file in DefaultThemeLoader)
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void preload(const std::string& primary);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the property-value pairs from the theme
        ///
        /// @param primary    Primary parameter of the loader
        /// @param secondary  Secondary parameter of the loader
        ///
        /// For the default loader, the primary parameter is the filename while the secondary parameter is the section name.
        ///
        /// @return Map op property-value pairs
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual const std::map<sf::String, sf::String>& load(const std::string& primary, const std::string& secondary) = 0;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief Default implementation for theme loading
    ///
    /// Themes are stored on disk in files which contain sections with a syntax similar to CSS.
    /// This loader will be able to extract the data from these files.
    ///
    /// On first access, the entire file will be cached, the next times the cached map is simply returned.
    ///
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API DefaultThemeLoader : public BaseThemeLoader
    {
    public:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the theme file in cache
        ///
        /// @param filename  Filename of the theme file to load
        ///
        /// @exception Exception when finding syntax errors in the file
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void preload(const std::string& filename) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the property-value pairs from the theme file
        ///
        /// @param filename   Filename of the theme file
        /// @param section    Name of the section inside the theme file
        ///
        /// @return Map of property-value pairs
        ///
        /// @exception Exception when finding syntax errors in the file
        /// @exception Exception when file did not contain requested class name
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const std::map<sf::String, sf::String>& load(const std::string& filename, const std::string& section) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Empties the caches and force files to be reloaded.
        ///
        /// @param filename  File to remove from cache.
        ///                  If no filename is given, the entire cache is cleared.
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void flushCache(const std::string& filename = "");


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Reads and return the contents of the entire file
        ///
        /// @param filename  Filename of the file to read
        /// @param contents  Reference to a stringstream that should be filled with the contents of the file by this function
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        virtual void readFile(const std::string& filename, std::stringstream& contents) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:
        static std::map<std::string, std::map<std::string, std::map<sf::String, sf::String>>> m_propertiesCache;

        friend struct DefaultThemeLoaderTest; // Used for testing m_propertiesCache
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_THEME_LOADER_HPP
