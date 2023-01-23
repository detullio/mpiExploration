#include "Logger.hpp"

#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <cerrno>

#if defined(GLOBAL_LOG_ENABLED)

BOOST_LOG_GLOBAL_LOGGER_INIT(g_SystemLogger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)
{

  boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level> logger;

  boost::log::add_common_attributes();

  boost::log::add_file_log(boost::log::keywords::file_name = std::string(program_invocation_name) + ".log",
			   boost::log::keywords::format = (boost::log::expressions::stream << boost::log::expressions::format_date_time<boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f:") << ' ' <<
							   boost::log::expressions::attr<boost::log::attributes::current_thread_id::value_type>("ThreadID") << " [" <<
							   boost::log::expressions::attr<boost::log::trivial::severity_level>("Severity") << " ]" <<
							   boost::log::expressions::smessage)
			   );

  boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::trace);

  return(logger);

}

#else

#endif
