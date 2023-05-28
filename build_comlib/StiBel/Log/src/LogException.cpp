
#include "StiBel/Log/LogException.h"
#include <typeinfo>

namespace StiBel {
namespace Log {

STIBEL_IMPLEMENT_EXCEPTION(LogException, StiBel::Common::Exception, "Log Exception")

} } // namespace StiBel::Log
