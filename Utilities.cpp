/*   Bridge Command 5.0 Ship Simulator
     Copyright (C) 2014 James Packer

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License version 2 as
     published by the Free Software Foundation

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY Or FITNESS For A PARTICULAR PURPOSE.  See the
     GNU General Public License For more details.

     You should have received a copy of the GNU General Public License along
     with this program; if not, write to the Free Software Foundation, Inc.,
     51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#include "Utilities.hpp"
#include "Constants.hpp"

#include <algorithm>
#include <locale>
#include <sstream>
#include <sys/stat.h>

#ifndef _WIN32
    #ifdef __APPLE__
        //Apple
        #include <CoreServices/CoreServices.h>
    #else
        //Other posix
        #include <unistd.h>
        #include <sys/types.h>
        #include <pwd.h>
    #endif // __APPLE__
#endif // _WIN32

namespace Utilities
{
    void to_lower(std::string& toConvert) {
        //A simple version of boost::to_lower.
        //ToDo: Test effect on internationalisation

        //convert to lower case
        //std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(),
        //               std::bind2nd(std::ptr_fun(&std::tolower<char>), std::locale("")));

        std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::tolower);

    }

    void to_lower(std::wstring& toConvert) {
        //A simple version of boost::to_lower.
        //ToDo: Test effect on internationalisation

        //convert to lower case
        //std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(),
        //               std::bind2nd(std::ptr_fun(&std::tolower<char>), std::locale("")));

        std::transform(toConvert.begin(), toConvert.end(), toConvert.begin(), ::tolower);

    }

    std::string trim(std::string inString) {
        //Based on http://codereview.stackexchange.com/questions/40124/trim-white-space-from-string, Loki Astari answer
        if(inString.empty()) {
            return inString;
        }

        std::size_t firstScan = inString.find_first_not_of(" \f\n\r\t\v");
        std::size_t first     = firstScan == std::string::npos ? inString.length() : firstScan;
        std::size_t last      = inString.find_last_not_of(" \f\n\r\t\v");
        return inString.substr(first, last-first+1);
    }

    signed int round(float numberIn) {
        //Implements round away from zero

        signed int result;
        if (numberIn > 0) {
            result = numberIn + 0.5;
        } else {
            result = numberIn - 0.5;
        }
        return result;
    }

    time_t dmyToTimestamp(int day, int month, int year) {
        tm timeInfo;
        timeInfo.tm_year = year-1900;
        timeInfo.tm_mon = month-1;
        timeInfo.tm_mday = day;
        timeInfo.tm_hour=0; timeInfo.tm_min=0; timeInfo.tm_sec=0; timeInfo.tm_isdst=0; //Set all others to zero
        return(mktime(&timeInfo));
    }

    std::string timestampToString(time_t timestamp, std::string format) {
        char buffer[80];
        tm * timeinfo;

        timeinfo = gmtime(&timestamp);
        strftime(buffer,80,format.c_str(),timeinfo);
        std::string returnString(buffer);
        return(returnString);
    }

    std::string timestampToString(time_t timestamp) {
        return timestampToString(timestamp, "%d %b %Y %H:%M:%S"); //Default date/time format
    }

    std::vector<std::string> split(const std::string &inputString, char delim) {
        //from http://stackoverflow.com/questions/236129/split-a-string-in-c, Evan Teran answer
        std::vector<std::string> splitStrings;

        std::stringstream ss(inputString);
        std::string item;
        while (std::getline(ss, item, delim)) {
            splitStrings.push_back(item);
        }
        return splitStrings;
    }

    std::string getUserDirBase() {
        // Return the user directory (eg %appdata%/Bridge Command/ on Windows,
        // ~/.Bridge Command/ on Linux
        // and
        // ~/Library/Application Support/Bridge Command/on Mac)

        std::string userFolder;

        #ifdef _WIN32
            char* appdataLocation;
            appdataLocation = getenv("APPDATA"); //TODO: Check this works on windows XP-10
            if (appdataLocation!=NULL) {
                userFolder = appdataLocation;
                userFolder.append("/Bridge Command/");
            }
        #else
            #ifdef __APPLE__
                //Apple
                FSRef ref;
                OSType folderType = kApplicationSupportFolderType;
                char path[PATH_MAX];
                FSFindFolder( kUserDomain, folderType, kCreateFolder, &ref );
                FSRefMakePath( &ref, (UInt8*)&path, PATH_MAX );
                // You now have ~/Library/Application Support stored in 'path'
                if (path!=NULL) {
                    userFolder = path;
                    userFolder.append("/Bridge Command/");
                }
            #else
                //Other posix
                struct passwd *pw = getpwuid(getuid());
                const char *path = pw->pw_dir;
                if (path!=NULL) {
                    userFolder = path;
                    userFolder.append("/.Bridge Command/");
                }
            #endif // __APPLE__

        #endif // _WIN32

        return userFolder;
    }

    std::string getUserDir() {
        // Return the user directory (eg %appdata%/Bridge Command/version on Windows,
        // ~/.Bridge Command/version on Linux
        // and
        // ~/Library/Application Support/Bridge Command/version on Mac)

        std::string userFolder = getUserDirBase();

        if (userFolder.length() > 0) {
            userFolder.append(VERSION);
            userFolder.append("/");
        }

        return userFolder;
    }

    bool pathExists(std::string filePath) {

        if (filePath.empty()) {
            return false;
        }

        //Strip trailing slashes
        while(!filePath.empty() && (*filePath.rbegin() == '/' || *filePath.rbegin() == '\\')) {
            std::string::iterator it = filePath.end() - 1;
            filePath.erase(it);
        }

        struct stat buffer;
        if (stat(filePath.c_str(),&buffer)==0) { //File exists
            return true;
        } else {
            return false;
        }
    }

    //Note for dir check - strip trailing slash

}
