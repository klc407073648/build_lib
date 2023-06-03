
#include "StiBel/JSON/JSONException.h"
#include <typeinfo>

namespace StiBel {
namespace JSON {

STIBEL_IMPLEMENT_EXCEPTION(JSONException, StiBel::Common::Foundation::Exception, "JSON Exception")

} } // namespace StiBel::JSON
