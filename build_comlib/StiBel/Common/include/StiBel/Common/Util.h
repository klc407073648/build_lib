/**
 * @file Util.h
 * @brief 常用工具类
 * @author klc
 * @date 2020-04-30
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_UTIL_H_
#define __STIBEL_UTIL_H_

#include <cxxabi.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <iostream>
#include <map>

#define BUFFER_SIZE 102400
// #include <boost/lexical_cast.hpp>

namespace StiBel{
namespace Common {

    /**
     * @brief 类型转换类
     */
    class TypeUtil
    {
    public:
        static int8_t ToChar(const std::string &str);
        static int64_t Atoi(const std::string &str);
        static double Atof(const std::string &str);
        static int8_t ToChar(const char *str);
        static int64_t Atoi(const char *str);
        static double Atof(const char *str);
    };

    /**
     * @brief string工具类
     */
    class StringUtil
    {
    public:
        static std::string Format(const char *fmt, ...);
        static std::string Formatv(const char *fmt, va_list ap);

        static std::string UrlEncode(const std::string &str, bool space_as_plus = true);
        static std::string UrlDecode(const std::string &str, bool space_as_plus = true);

        static std::string Trim(const std::string &str, const std::string &delimit = " \t\r\n");
        static std::string TrimLeft(const std::string &str, const std::string &delimit = " \t\r\n");
        static std::string TrimRight(const std::string &str, const std::string &delimit = " \t\r\n");

        static std::string WStringToString(const std::wstring &ws);
        static std::wstring StringToWString(const std::string &s);

        static std::vector<std::string> mySplit(const std::string &str, std::string sp_string); // split(), str 是要分割的string
        static void parseParam(const std::string &paramsStr, std::map<std::string, std::string> &reqParams);
        static void ClearHeadTailSpace(std::string &str);
        static std::string getFileSuffix(const std::string &str);
    };

    /**
     * @brief shell工具类
     */
    class ShellUtil
    {
    public:
        static void execShell(const std::string &cmd);
        static std::string execShellPipe(const std::string &cmd);
        static std::string execShellPipeEndWithLineFeed(const std::string &cmd);
        static std::string getParamValue(const std::string &key, const std::string &fileName);
        static void modParamValue(const std::string &key, const std::string &value, const std::string &fileName);
        static bool setEnv(const std::string &key, const std::string &val);
        static std::string getEnv(const std::string &key, const std::string &default_value = "");
    };

    /**
     * @brief File工具类
     */
    class FileUtil
    {
    public:
        static std::string loadFile(const std::string &filename);
        static std::vector<std::string> getFileListFromDir(const std::string &dirPath);
        static bool isFile(const std::string &path);
        static bool isDir(const std::string &path);
        static bool createDir(const std::string &path);
        static bool copyFile(const std::string &srcFile, const std::string &dstFile);
        static bool copyDir(const std::string &srcDir, const std::string &dstDir, const bool &isCover);
    };

} // namespace StiBel
} // namespace Common

#endif //__STIBEL_UTIL_H_
