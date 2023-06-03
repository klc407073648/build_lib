#include "StiBel/JSON/JSONException.h"
#include "CommonTest.h"

using StiBel::Common::Foundation::Exception;
using StiBel::JSON::JSONException;

/* JSONExceptionTest */
class JSONExceptionTest : public CommonTest
{

protected:
  JSONExceptionTest()
  {
  }

  ~JSONExceptionTest()
  {
  }

  void SetUp()
  {
  }

  void TearDown()
  {
  }

public:
};

/* JSONExceptionTest */

/* 测试json字符串读取 */
TEST_F(JSONExceptionTest, Given_JSONException_When_throw_Then_success_catch_and_parse_content)
{
  // enable_print();//TODO
  try
  {
    throw JSONException("Attempt to set value on an empty stack");
  }
  catch (StiBel::Common::Foundation::Exception &e)
  {
    std::cout << "StiBel::Common::Exception caught" << std::endl;
    std::cout << e.what() << std::endl;
    std::cout << e.displayText() << std::endl;
  }
}