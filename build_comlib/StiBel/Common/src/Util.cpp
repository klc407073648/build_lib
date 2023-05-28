#include "StiBel/Common/Util.h"
#include <execinfo.h>
#include <sys/time.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <cstdarg>
#include <dirent.h>
#include <fstream>

namespace StiBel {
namespace Common {

    int8_t TypeUtil::ToChar(const std::string &str)
    {
        if (str.empty())
        {
            return 0;
        }
        return *str.begin();
    }

    int64_t TypeUtil::Atoi(const std::string &str)
    {
        if (str.empty())
        {
            return 0;
        }
        return strtoull(str.c_str(), nullptr, 10);
    }

    double TypeUtil::Atof(const std::string &str)
    {
        if (str.empty())
        {
            return 0;
        }
        return atof(str.c_str());
    }

    int8_t TypeUtil::ToChar(const char *str)
    {
        if (str == nullptr)
        {
            return 0;
        }
        return str[0];
    }

    int64_t TypeUtil::Atoi(const char *str)
    {
        if (str == nullptr)
        {
            return 0;
        }
        return strtoull(str, nullptr, 10);
    }

    double TypeUtil::Atof(const char *str)
    {
        if (str == nullptr)
        {
            return 0;
        }
        return atof(str);
    }

    std::string StringUtil::Format(const char *fmt, ...)
    {
        va_list ap;
        va_start(ap, fmt);
        auto v = Formatv(fmt, ap);
        va_end(ap);
        return v;
    }

    std::string StringUtil::Formatv(const char *fmt, va_list ap)
    {
        char *buf = nullptr;
        auto len = vasprintf(&buf, fmt, ap);
        if (len == -1)
        {
            return "";
        }
        std::string ret(buf, len);
        free(buf);
        return ret;
    }

    static const char uri_chars[256] = {
        /* 0 */
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 1, 1, 0,
        1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 0, 0, 0, 1, 0, 0,
        /* 64 */
        0, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 0, 0, 0, 0, 1,
        0, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1,   1, 1, 1, 0, 0, 0, 1, 0,
        /* 128 */
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        /* 192 */
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0,
    };

    static const char xdigit_chars[256] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,1,2,3,4,5,6,7,8,9,0,0,0,0,0,0,
        0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,10,11,12,13,14,15,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    };

    #define CHAR_IS_UNRESERVED(c) \
        (uri_chars[(unsigned char)(c)])

    //-.0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~
    std::string StringUtil::UrlEncode(const std::string &str, bool space_as_plus)
    {
        static const char *hexdigits = "0123456789ABCDEF";
        std::string *ss = nullptr;
        const char *end = str.c_str() + str.length();
        for (const char *c = str.c_str(); c < end; ++c)
        {
            if (!CHAR_IS_UNRESERVED(*c))
            {
                if (!ss)
                {
                    ss = new std::string;
                    ss->reserve(str.size() * 1.2);
                    ss->append(str.c_str(), c - str.c_str());
                }
                if (*c == ' ' && space_as_plus)
                {
                    ss->append(1, '+');
                }
                else
                {
                    ss->append(1, '%');
                    ss->append(1, hexdigits[(uint8_t)*c >> 4]);
                    ss->append(1, hexdigits[*c & 0xf]);
                }
            }
            else if (ss)
            {
                ss->append(1, *c);
            }
        }
        if (!ss)
        {
            return str;
        }
        else
        {
            std::string rt = *ss;
            delete ss;
            return rt;
        }
    }

    std::string StringUtil::UrlDecode(const std::string &str, bool space_as_plus)
    {
        std::string *ss = nullptr;
        const char *end = str.c_str() + str.length();
        for (const char *c = str.c_str(); c < end; ++c)
        {
            if (*c == '+' && space_as_plus)
            {
                if (!ss)
                {
                    ss = new std::string;
                    ss->append(str.c_str(), c - str.c_str());
                }
                ss->append(1, ' ');
            }
            else if (*c == '%' && (c + 2) < end && isxdigit(*(c + 1)) && isxdigit(*(c + 2)))
            {
                if (!ss)
                {
                    ss = new std::string;
                    ss->append(str.c_str(), c - str.c_str());
                }
                ss->append(1, (char)(xdigit_chars[(int)*(c + 1)] << 4 | xdigit_chars[(int)*(c + 2)]));
                c += 2;
            }
            else if (ss)
            {
                ss->append(1, *c);
            }
        }
        if (!ss)
        {
            return str;
        }
        else
        {
            std::string rt = *ss;
            delete ss;
            return rt;
        }
    }

    std::string StringUtil::Trim(const std::string &str, const std::string &delimit)
    {
        auto begin = str.find_first_not_of(delimit);
        if (begin == std::string::npos)
        {
            return "";
        }
        auto end = str.find_last_not_of(delimit);
        return str.substr(begin, end - begin + 1);
    }

    std::string StringUtil::TrimLeft(const std::string &str, const std::string &delimit)
    {
        auto begin = str.find_first_not_of(delimit);
        if (begin == std::string::npos)
        {
            return "";
        }
        return str.substr(begin);
    }

    std::string StringUtil::TrimRight(const std::string &str, const std::string &delimit)
    {
        auto end = str.find_last_not_of(delimit);
        if (end == std::string::npos)
        {
            return "";
        }
        return str.substr(0, end);
    }

    std::string StringUtil::WStringToString(const std::wstring &ws)
    {
        std::string str_locale = setlocale(LC_ALL, "");
        const wchar_t *wch_src = ws.c_str();
        size_t n_dest_size = wcstombs(NULL, wch_src, 0) + 1;
        char *ch_dest = new char[n_dest_size];
        memset(ch_dest, 0, n_dest_size);
        wcstombs(ch_dest, wch_src, n_dest_size);
        std::string str_result = ch_dest;
        delete[] ch_dest;
        setlocale(LC_ALL, str_locale.c_str());
        return str_result;
    }

    std::wstring StringUtil::StringToWString(const std::string &s)
    {
        std::string str_locale = setlocale(LC_ALL, "");
        const char *chSrc = s.c_str();
        size_t n_dest_size = mbstowcs(NULL, chSrc, 0) + 1;
        wchar_t *wch_dest = new wchar_t[n_dest_size];
        wmemset(wch_dest, 0, n_dest_size);
        mbstowcs(wch_dest, chSrc, n_dest_size);
        std::wstring wstr_result = wch_dest;
        delete[] wch_dest;
        setlocale(LC_ALL, str_locale.c_str());
        return wstr_result;
    }

    std::vector<std::string> StringUtil::mySplit(const std::string &str, std::string sp_string) // split(), str 是要分割的string
    {
        std::vector<std::string> vecString;
        int sp_stringLen = sp_string.size();
        int lastPosition = 0;
        int index = -1;
        // 如果要分割的串就是自己怎么写？
        while (-1 != (index = str.find(sp_string, lastPosition)))
        {
            if (str.substr(lastPosition, index - lastPosition) != std::string("")) // 避免第一个字符串就是sp_string
            {
                vecString.push_back(str.substr(lastPosition, index - lastPosition));
            }
            lastPosition = index + sp_stringLen;
        }
        std::string lastStr = str.substr(lastPosition);
        if (!lastStr.empty())
        {
            vecString.push_back(lastStr);
        }
        return vecString;
    }

    void StringUtil::parseParam(const std::string &paramsStr, std::map<std::string, std::string> &reqParams)
    {

        std::vector<std::string> pairslist = StringUtil::mySplit(paramsStr, "&");

        for (size_t i = 0; i < pairslist.size(); ++i)
        {
            std::string name = pairslist[i].substr(0, pairslist[i].find("="));
            std::string value = pairslist[i].substr(pairslist[i].find("=") + 1);

            reqParams[name] = value;
        }
    }

    void StringUtil::ClearHeadTailSpace(std::string &str)
    {
        if (str.empty())
        {
            return;
        }

        str.erase(0, str.find_first_not_of(" "));
        str.erase(str.find_last_not_of(" ") + 1);
    }

    std::string StringUtil::getFileSuffix(const std::string &str)
    {
        if (str.empty())
        {
            return str;
        }

        int pos = str.find_last_of('.');

        if (pos == -1)
        {
            return "null";
        }
        else
        {
            return str.substr(pos + 1);
        }
    }

    void ShellUtil::execShell(const std::string &cmd)
    {
        system(cmd.c_str());
    }

    std::string ShellUtil::execShellPipe(const std::string &cmd)
    {
        char res[1024] = {0};

        FILE *fp = popen(cmd.c_str(), "r");

        if (fp != NULL)
        {
            // fgets( res, sizeof(res), fp ); //遇到\n终止复制
            fread(res, sizeof(char), sizeof(res), fp);
            pclose(fp);
        }

        return res;
    }

    std::string ShellUtil::execShellPipeEndWithLineFeed(const std::string &cmd)
    {
        char res[1024] = {0}, *p;

        FILE *fp = popen(cmd.c_str(), "r");

        if (fp != NULL)
        {
            fgets(res, sizeof(res), fp); // 遇到\n终止复制
            if ((p = strchr(res, '\n')) != NULL)
                *p = '\0';
            // fread( res, sizeof(char), sizeof(res), fp );
            pclose(fp);
        }

        return res;
    }

    std::string ShellUtil::getParamValue(const std::string &key, const std::string &fileName)
    {
        std::string cmd = "grep " + key + " " + fileName + " | cut -d \"=\" -f2";
        std::string value = execShellPipe(cmd);
        return value;
    }

    void ShellUtil::modParamValue(const std::string &key, const std::string &value, const std::string &fileName)
    {
        std::string relpaceline = key + "=" + value;
        std::string cmd = "sed -i 's/^" + key + "=.*/" + relpaceline + "/g' " + fileName;
        execShell(cmd);
    }

    bool ShellUtil::setEnv(const std::string &key, const std::string &val)
    {
        return !setenv(key.c_str(), val.c_str(), 1);
    }

    std::string ShellUtil::getEnv(const std::string &key, const std::string &default_value)
    {
        const char* v = getenv(key.c_str());

        if(v == nullptr) {
            return default_value;
        }

        return v;
    }

    std::string FileUtil::loadFile(const std::string &filename)
    {
        FILE *fp = fopen(filename.c_str(), "rb");
        if (fp == NULL)
            return "";

        // read file size
        fseek(fp, 0, SEEK_END);
        int bufsize = ftell(fp);
        rewind(fp);

        char *buf = new char[bufsize + 1];
        memset(buf, 0, bufsize + 1);
        fread(buf, 1, bufsize, fp);
        fclose(fp);

        return std::string(buf, bufsize);
    }

    std::vector<std::string> FileUtil::getFileListFromDir(const std::string &dirPath)
    {
        std::vector<std::string> vecString;
        DIR *dir = NULL;
        dirent *ptr = NULL;
        if (!isDir(dirPath))
        {
            std::cout << "dirPath is not dir" << std::endl;
            return vecString;
        }
        dir = opendir(dirPath.c_str());
        if (!dir)
        {
            closedir(dir);
            std::cout << "open dir failed!" << std::endl;
            return vecString;
        }
        for (ptr = readdir(dir); ptr != NULL; ptr = readdir(dir))
        {
            if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) /// current dir OR parrent dir
            {
                continue;
            }
            else
            {
                vecString.push_back(ptr->d_name);
            }
        }
        closedir(dir);
        return vecString;
    }

    bool FileUtil::isFile(const std::string &path)
    {
        if (path.length() == 0)
        {
            return false;
        }
        std::fstream fs;
        fs.open(path, std::ios::in);
        if (fs)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool FileUtil::isDir(const std::string &path)
    {
        if (path.length() == 0)
        {
            return false;
        }
        DIR *dir = opendir(path.c_str());
        if (dir)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool FileUtil::createDir(const std::string &path)
    {
        if (path.length() == 0)
        {
            return false;
        }
        if (isDir(path))
        {
            std::cout << "This directory already exists!" << std::endl;
            return false;
        }
        // S_IRWXU 00700权限，代表该文件所有者拥有读，写和执行操作的权限
        // S_IRUSR(S_IREAD) 00400权限，代表该文件所有者拥有可读的权限
        // S_IWUSR(S_IWRITE) 00200权限，代表该文件所有者拥有可写的权限
        // S_IXUSR(S_IEXEC) 00100权限，代表该文件所有者拥有执行的权限
        // S_IRWXG 00070权限，代表该文件用户组拥有读，写和执行操作的权限
        // S_IRGRP 00040权限，代表该文件用户组拥有可读的权限
        // S_IWGRP 00020权限，代表该文件用户组拥有可写的权限
        // S_IXGRP 00010权限，代表该文件用户组拥有执行的权限
        // S_IRWXO 00007权限，代表其他用户拥有读，写和执行操作的权限
        // S_IROTH 00004权限，代表其他用户拥有可读的权限
        // S_IWOTH 00002权限，代表其他用户拥有可写的权限
        // S_IXOTH 00001权限，代表其他用户拥有执行的权限
        int isCreate = mkdir(path.c_str(), S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
        if (!isCreate)
        {
            std::cout << "createDir succeed:" << path << std::endl;
            return true;
        }
        else
        {
            std::cout << "createDir faiiled!" << std::endl;
            return false;
        }
    }

    bool FileUtil::copyFile(const std::string &srcFile, const std::string &dstFile)
    {
        if (!isFile(srcFile))
        {
            std::cout << "source file is null!" << std::endl;
            return false;
        }
        FILE *fpR, *fpW;
        char buffer[BUFFER_SIZE];
        int lenR, lenW;
        if ((fpR = fopen(srcFile.c_str(), "r")) == NULL)
        {
            std::cout << "src file cannot open!" << std::endl;
            return false;
        }
        if ((fpW = fopen(dstFile.c_str(), "w")) == NULL)
        {
            std::cout << "dsr file cannot open!" << std::endl;
            fclose(fpR);
            return false;
        }

        memset(buffer, 0, BUFFER_SIZE);
        while ((lenR = fread(buffer, 1, BUFFER_SIZE, fpR)) > 0)
        {
            if ((lenW = fwrite(buffer, 1, lenR, fpW)) != lenR)
            {
                fclose(fpR);
                fclose(fpW);
                return false;
            }
            memset(buffer, 0, BUFFER_SIZE);
        }

        fclose(fpR);
        fclose(fpW);
        return true;
    }

    bool FileUtil::copyDir(const std::string &srcDir,
                           const std::string &dstDir, const bool &isCover)
    {
        if (!isDir(srcDir))
        {
            std::cout << "src dir is not a dir!" << std::endl;
            return false;
        }
        if (!isDir(dstDir))
        {
            std::cout << "dst dir is not a dir!" << std::endl;
            return false;
        }

        std::string sysStr = "cp " + srcDir + " " + dstDir + " -a";
        std::cout << sysStr << std::endl;
        return system(sysStr.c_str());
    }

} // namespace StiBel
} // namespace Common
