#include <iostream>
#include <map>
#include "StiBel/Data/MySQL/MySQL.h"
#include "CommonTest.h"

using namespace StiBel::Data::MySQL;
using namespace std;

/* DataMySQLTest */
class DataMySQLTest : public CommonTest
{

protected:
    DataMySQLTest()
    {
        // 初始化map
        params["host"] = "1.15.109.169";
        params["user"] = "root";
        params["passwd"] = "klczxas789";
        params["dbname"] = "student";
    }

    ~DataMySQLTest()
    {
    }

    void SetUp()
    {
		/*
        mysql = new MySQL(params);
        if (!mysql->connect())
        {
            std::cout << "connect fail" << std::endl;
            return;
        }
		*/
    }

    void TearDown()
    {
    }
    // SetUpTestCase 和 TearDownTestCase

public:
    std::map<std::string, std::string> params;
    MySQL::ptr mysql;
};

/* DataMySQLTest */

/* 测试MySQL数据库正常连接后，查询各类信息,考虑加载数据，清理数据 */
TEST_F(DataMySQLTest, Given_json_file_When_load_Then_success_parse_content)
{
    // enable_print();//TODO


    std::map<std::string, std::string> params;
    // 数据库的参数
    params["host"] = "1.15.109.169";
    params["user"] = "root";
    params["passwd"] = "klczxas789";
    params["dbname"] = "student";

    MySQL::ptr mysql(new MySQL(params));
    if (!mysql->connect())
    {
        std::cout << "connect fail" << std::endl;
        return;
    }


    cout << "查询studentInfo表的结果集" << endl;
    std::string sql1 = "select * from studentInfo";
    ISQLData::ptr m_ptr1 = mysql->query(sql1);
    m_ptr1->showAllRes();
    cout << "——————————————————————————————" << endl;

    cout << "更换数据库为myTest，查询表test结果集" << endl;
    mysql->use("myTest");
    std::string sql2 = "select * from test";
    ISQLData::ptr m_ptr2 = mysql->query(sql2);
    m_ptr2->showAllRes();
    cout << "——————————————————————————————" << endl;

    cout << "切换回student数据库，测试基本的函数" << endl;
    mysql->use("student");
    std::string sql3 = "select * from studentInfo";
    ISQLData::ptr m_ptr3 = mysql->query(sql3);
    cout << "数据库名称:" << mysql->getDbname() << endl;
    cout << "行:" << m_ptr3->getDataCount() << "	列:" << m_ptr3->getColumnCount() << endl;
    cout << "表格字段内容：" << endl;
    for (int i = 0; i < m_ptr3->getColumnCount(); i++)
    {
        cout << m_ptr3->getColumnName(i) << " ";
    }
    cout << endl;
    m_ptr3->next();
    cout << "当前行第0个元素:" << m_ptr3->getString(1) << "占用字节: " << m_ptr3->getColumnBytes(1) << endl;
    m_ptr3->next();
    m_ptr3->next();
    cout << "当前行第0个元素:" << m_ptr3->getString(0) << "占用字节: " << m_ptr3->getColumnBytes(0) << endl;
    cout << "——————————————————————————————" << endl;

    cout << "测试带format的query函数" << endl;
    std::string sql4 = "select * from studentInfo where id=%d";
    ISQLData::ptr m_ptr4 = mysql->query(sql4.c_str(), 1002);
    m_ptr4->showAllRes();
    cout << "——————————————————————————————" << endl;
}