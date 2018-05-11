#ifndef UTILS_H
#define UTILS_H

#include <climits>
#include <string>
#include <string.h>
#include <sstream>
#include <libgen.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <unistd.h>
#include <ctype.h>
#include <list>
#include <cassert>

namespace Utils
{
#define TO_STRING(x) #x

template <class T>
int setValueInLimit(T &dst, const T &src, const T &minLimit, const T &maxLimit)
{
    int res = 0;
    dst += src;
    dst = (dst < minLimit) ? res = -1, minLimit : dst;
    dst = (dst > maxLimit) ? res = 1, maxLimit : dst;
    return res;
}

inline std::string parseFileName(const char *fullPath)
{
    std::string value;
    if(!fullPath && *fullPath == '\0')
    {
        return value;
    }
    char *lineDup = strdup(fullPath);
    if(!lineDup)
    {
        return value;
    }
    char *file = basename(lineDup);
    char* extPtr = strchr(file, '.');

    value.append(file, 0, extPtr ? extPtr - file : strlen(file));
    free(lineDup);
    return value;
}

inline void removeTokensFromString(std::string &inStr, const char *tokens)
{
    inStr.erase(std::remove_if(inStr.begin(), inStr.end(),
            [tokens](const std::string::value_type &symbol)
            {
                return strchr(tokens, symbol) != NULL;
            }), inStr.end());
}

inline std::string parseFileName(const std::string &fullPath)
{
    return parseFileName(fullPath.c_str());
}

inline std::string parseConfigRow(const char *row, size_t rowSize,
        const char *parameterName, size_t parameterNameSize)
{
    //find parameter Name
    std::string value;
    const char *pFind = strstr(row, parameterName);
    if(!pFind)
    {
        return value;
    }

    if((pFind - row) + parameterNameSize >= rowSize)
    {
        return value;
    }

    pFind += parameterNameSize;
    while(*pFind && isspace(*pFind))
    {
    ++pFind;
    }
    const char *pNameEnd = strchr(pFind, '\n');
    if(!pNameEnd)
    {
        //to '\0'
        pNameEnd = pFind;
        while(*pNameEnd)
        {
            pNameEnd ++;
        }
    }
    std::copy(pFind, pNameEnd, std::back_inserter(value));
    return value;
}

#define MAX_CHAR_TO_DIGIT_CONVERTION    256
template <typename T>
inline std::string convertDigit2String(T value)
{
    double count = log10(value);
    size_t size =
        static_cast<std::string::size_type>(
            round(value) + value > 0 ? 0. : 1.);
    //TODO
    size = MAX_CHAR_TO_DIGIT_CONVERTION;
    //ret.reserve(size);
    std::string ret;
    char r[MAX_CHAR_TO_DIGIT_CONVERTION];

    static const char digits[] =
    {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    };
    static const size_t  digits_cout = sizeof(digits)/sizeof(digits[0]);

    snprintf(r, size, "%d", value);
    ret = r;
    return ret;
}

template <>
inline std::string convertDigit2String<char>(char value)
{
    std::string ret;
    size_t size = 4; //255 + sign
    ret.reserve(size);
    char r[MAX_CHAR_TO_DIGIT_CONVERTION];
    snprintf(r, size, "%d", value);
    ret = r;
    return ret;
}

template <>
inline std::string convertDigit2String<float>(float value)
{
    std::string ret;
    size_t size = MAX_CHAR_TO_DIGIT_CONVERTION; //255
    ret.reserve(size);
    char r[MAX_CHAR_TO_DIGIT_CONVERTION];
    snprintf(r, size, "%f", value);
    ret = r;
    return ret;
}
template <>
inline std::string convertDigit2String<double>(double value)
{
    std::string ret;
    size_t size = MAX_CHAR_TO_DIGIT_CONVERTION; //255
    ret.reserve(size);
    char r[MAX_CHAR_TO_DIGIT_CONVERTION];
    snprintf(r, size, "%e", value);
    ret = r;
    return ret;
}
constexpr int c_strcmp( char const* lhs, char const* rhs )
{
    return (('\0' == lhs[0]) && ('\0' == rhs[0])) ? 0
        :  (lhs[0] != rhs[0]) ? (lhs[0] - rhs[0])
        : c_strcmp( lhs+1, rhs+1 );
}


template <class Pred>
inline const char *get_next_char_not_if(const char *data, Pred pred)
{
    if(!data) return nullptr;

    while(*data && pred(data))
    {
        ++data;
    }
    return data;
}
//specialization for clib function
template <>
inline const char *get_next_char_not_if(const char *data, int (*clib_pred)(int) noexcept)
{
    if(!data) return nullptr;

    while(*data && (*clib_pred)(*data))
    {
        ++data;
    }
    return data;
}

template <class Pred>
inline const char *get_next_char_if(const char *data, Pred pred)
{
    if(!data) return nullptr;

    while(*data && !pred(data))
    {
        ++data;
    }
    return data;
}
//specialization for clib function
template <>
inline const char *get_next_char_if(const char *data, int (*clib_pred)(int) noexcept)
{
    if(!data) return nullptr;

    while(*data && !(*clib_pred)(*data))
    {
        ++data;
    }
    return data;
}

inline std::pair<std::string, std::string> parseParamValueLine(const char *line)
{
    std::pair<std::string, std::string > pair;
    if(!line) return pair;

    const char *pStart, *pEnd;
    pStart = Utils::get_next_char_not_if(line, ::isspace);
    pEnd = Utils::get_next_char_if(pStart, []( const char* sym) { return (isspace(*sym) || *sym == '=');});
    std::string(pStart, pEnd - pStart).swap(pair.first);

    pStart = Utils::get_next_char_if(pEnd, []( const char* sym) { return !(isspace(*sym) || *sym == '=');});
    pEnd = Utils::get_next_char_if(pStart, ::isspace);
    std::string(pStart, pEnd - pStart).swap(pair.second);

    return pair;
}

inline bool tokenizeString(const std::string &in, char token, std::list<std::string> &outList)
{
    std::string tmpStr;
    bool isEmpty = true;
    std::for_each(in.begin(), in.end(),
        [&tmpStr, &outList, &isEmpty, token] (const char &s)
    {
        if(s != token)
        {
            tmpStr += s;
        }
        else
        {
            if (!tmpStr.empty())
            {
                outList.push_back(tmpStr);
                tmpStr.clear();
                isEmpty = false;
            }
        }
    });

    //and last
    if (!tmpStr.empty())
    {
        outList.push_back(tmpStr);
        isEmpty = false;
    }
    return !isEmpty;
}
}
#endif//UTILS_H
