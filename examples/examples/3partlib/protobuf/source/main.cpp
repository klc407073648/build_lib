#include <iostream>
#include <fstream>
#include <string>
#include "person.pb.h"
#include "game.pb.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "google/protobuf/text_format.h"

using namespace test1;
using namespace test2;

void test1Fun()
{
  Person p;
  p.set_name("test");
  p.set_id(100);
  p.set_email("a.iabc.com");

  //------------------将pb二进制信息保存到字符串
  std::string str;
  p.SerializeToString(&str);
  std::cout << "str: [" << str << "]" << std::endl;

  //------------------将pb文本信息写入文件
  std::ofstream fw;
  fw.open("./Person.txt", std::ios::out | std::ios::binary);
  google::protobuf::io::OstreamOutputStream *output = new google::protobuf::io::OstreamOutputStream(&fw);
  google::protobuf::TextFormat::Print(p, output);

  delete output;
  fw.close();

  //---------------------将pb文本信息保存到字符串
  std::string str1;
  google::protobuf::TextFormat::PrintToString(p, &str1);
  std::cout << "str1: [" << str1 << "]" << std::endl;

  //---------------------反序列化
  Person p1;
  p1.ParseFromString(str);
  std::cout << "name:" << p1.name() << ",email:" << p1.email() << ",id:" << p1.id() << std::endl;
}

void test2Fun()
{
  rsp_login rsp{};
  rsp.set_ret(rsp_login_RET_SUCCESS);
  auto user_info = rsp.mutable_user_info();
  user_info->set_nickname("dsw");
  user_info->set_icon("345DS55GF34D774S");
  user_info->set_coin(2000);
  user_info->set_location("zh");

  for (int i = 0; i < 5; i++)
  {
    auto record = rsp.add_record();
    record->set_time("2017/4/13 12:22:11");
    record->set_kill(i * 4);
    record->set_dead(i * 2);
    record->set_assist(i * 5);
  }

  std::string buff{};
  rsp.SerializeToString(&buff);
  //------------------解析----------------------
  rsp_login rsp2{};
  if (!rsp2.ParseFromString(buff))
  {
    std::cout << "parse error\n";
  }

  auto temp_user_info = rsp2.user_info();
  std::cout << "nickname:" << temp_user_info.nickname() << std::endl;
  std::cout << "coin:" << temp_user_info.coin() << std::endl;
  for (int m = 0; m < rsp2.record_size(); m++)
  {
    auto temp_record = rsp2.record(m);
    std::cout << "time:" << temp_record.time() << " kill:" << temp_record.kill() << " dead:" << temp_record.dead() << " assist:" << temp_record.assist() << std::endl;
  }
}

int main()
{
  test1Fun();
  test2Fun();

  return 0;
}
