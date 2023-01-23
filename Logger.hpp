#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/trivial.hpp>

#if !defined(__LOGGER_HPP__)
#define __LOGGER_HPP__

#if defined(GLOBAL_LOG_ENABLED)

BOOST_LOG_GLOBAL_LOGGER(g_SystemLogger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)

#define GLOBAL_LOG(output) do { BOOST_LOG_SEV(g_SystemLogger::get(), boost::log::trivial::trace) << output; } while(0);
#define GLOBAL_LOG_CALCULATION(aCalculation) do { aCalculation } while(0);
#define GLOBAL_LOG_DECLARATION(aDeclaration) aDeclaration;

#else

#endif


#endif //#if !defined(__LOGGER_HPP__)
