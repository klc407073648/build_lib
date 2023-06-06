#include "StiBel/JSON/JSONException.h"

using StiBel::Common::Foundation::Exception;
using StiBel::JSON::JSONException;

int main()
{
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

  return 0;
}