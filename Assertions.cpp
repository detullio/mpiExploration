#include "Logger.hpp"

#include <sstream>

#if !defined(BOOST_DISABLE_ASSERTS)

namespace boost
{
  void assertion_failed_msg(char const *expr, char const *msg, char const *function, char const *file, long line)
  {

    std::stringstream message;
    message << function << " failed " << expr << "@" << file << ":"
	    << line << '\n' << msg << std::endl;

#if defined(GLOBAL_LOG_ENABLED)

    auto logger = ::g_SystemLogger::get();
    BOOST_LOG_SEV(logger, boost::log::trivial::fatal) << message.str() << std::endl;

#endif

    throw(std::runtime_error(message.str()));

  }

  void assertion_failed(char const *expr, char const *function, char const *file, long line)
  {

    std::stringstream message;
    message << function << " failed " << expr << "@" << file << ":"
	    << line << '\n' << std::endl;

#if defined(GLOBAL_LOG_ENABLED)

    auto logger = ::g_SystemLogger::get();
    BOOST_LOG_SEV(logger, boost::log::trivial::fatal) << message.str() << std::endl;

#endif

    throw(std::runtime_error(message.str()));

  }

}

#endif
