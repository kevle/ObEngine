#include <algorithm>

#include <Utils/ExecUtils.hpp>

namespace obe
{
    namespace Utils
    {
        namespace Exec 
        {
            RunArgsParser::RunArgsParser(char** start, int size)
            {
                this->start = start;
                this->size = size;
            }

            bool RunArgsParser::argumentExists(const std::string& arg) const
            {
                return std::find(start, start + size, arg) != (start + size);
            }

            std::string RunArgsParser::getArgumentValue(const std::string& arg) const
            {
                char** itr = std::find(start, start + size, arg);
                if (itr != (start + size) && ++itr != (start + size))
                {
                    return std::string(*itr);
                }
                return "";
            }
        }
    }
}