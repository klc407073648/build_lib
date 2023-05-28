/**
 * @file Config.h
 * @brief 配置类封装
 * @author klc
 * @date 2021-04-24
 * @copyright Copyright (c) 2021年 klc
 */

#ifndef __STIBEL_CONFIG_H__
#define __STIBEL_CONFIG_H__

#include <string>
#include <map>
#include <memory>
#include <sstream>

namespace StiBel {
namespace Common {
/**
 * @brief 配置变量的基类
 */

class ConfigBase
{
public:
    typedef std::shared_ptr<ConfigBase> ptr;

    /**
     * @brief 构造函数
     * @param[in] name 配置参数名称
     * @param[in] description 参数描述
     */
    ConfigBase(const std::string &name, const std::string &description = "")
        : _name(name), _description(description)
    {
    }

    /**
     * @brief 析构函数
     */
    virtual ~ConfigBase() {}

    /**
     * @brief 返回配置参数名称
     */
    const std::string &getName() const { return _name; }

    /**
     * @brief 返回配置参数的描述
     */
    const std::string &getDescription() const { return _description; }

    /**
     * @brief 转成字符串
     */
    virtual std::string toString() = 0;

    /**
     * @brief 从字符串初始化值
     */
    virtual bool fromString(const std::string &val) = 0;

    /**
     * @brief 返回配置参数值的类型名称
     */
    virtual const std::string& getTypeName() const = 0;

private:
    /// 配置参数的名称
    std::string _name;
    /// 配置参数的描述
    std::string _description;
};

/**
 * @brief 配置参数类
 */
class Config : public ConfigBase
{
public:
    typedef std::shared_ptr<Config> ptr;
    typedef std::map<std::string, std::map<std::string, std::string>> ParamsMap;

    /**
     * @brief 通过参数名,参数值,描述构造Config
     * @param[in] name 参数名称
     * @param[in] description 参数的描述
     * @param[in] default_value 参数的默认值
     */
    Config(const std::string &name, const ParamsMap &conf_map, const std::string &description = "", const std::string &type = "");

    /**
     * @brief 析构函数
     */
    ~Config();

    /**
     * @brief 将ParamsMap转换成String
     */
    std::string toString() override;

    /**
     * @brief 输出信息到ostream
     */
    std::ostream& dump(std::ostream& os);

    /**
     * @brief 根据参数名获取对应值
     */
    std::map<std::string, std::string> getParams(std::string &name);

    /**
     * @brief 重载[]方法
     */
    inline std::map<std::string, std::string> operator[](std::string &name)
    {
        return this->getParams(name);
    }

    /**
     * @brief 将String转换成ParamsMap
     *  TODO 空实现
     */
    bool fromString(const std::string &val) { return false; };

    /**
     * @brief 获取当前ParamsMap参数值
     */
    const ParamsMap& getValue() const { return _confMap; }

    /**
     * @brief 设置ParamsMap参数值
     */
    void setValue(const ParamsMap& v) { _confMap = v; }

    /**
     * @brief 返回参数值的类型名称(typeinfo)
     */
    const std::string &getTypeName() const  { return _type; }

private:
    // 配置参数的类型
    std::string _type;
    // 配置参数的描述
    ParamsMap _confMap;
};

} // namespace StiBel
} // namespace Common

#endif // __STIBEL_CONFIG_H__


