/**
 * @file LOG.hpp
 *
 * @brief Simple logger class for C++ 
 *
 * @author  Nenad Lazic
 * Contact: nenadlazic13@gmail.com
 *
 */

#ifndef LOG_HPP_INCLUDED
#define LOG_HPP_INCLUDED
 
#include <time.h>
#include <iostream>
#include <cstdint>

/*
 * Defining log levels
 */
enum LOG_LEVEL 
{
	ERROR,
	WARNING,
	DEBUG,
	INFO,
	ALL
};

/*
 * This class implements a simple logging mechanism
 */
class LOG
{
private:
	// here define the desired log level
	static LOG_LEVEL const current_log_level = ALL;

public:
	// method for printing error logs
	template<typename T0, typename ...T>
	static void E(T0 && t, T && ...args);
	
	// method for printing warning logs
	template<typename T0, typename ...T>
	static void W(T0 && t, T && ...args);

	// method for printing debug logs	
	template<typename T0, typename ...T>
	static void D(T0 && t, T && ...args);
	
	// method for printing info logs
	template<typename T0, typename ...T>
	static void I(T0 && t, T && ...args);

	// method for printing verbose logs	
	template<typename T0, typename ...T>
	static void V(T0 && t, T && ...args);
	
	// method for printing logs to console
	template <typename T>
	static void log_writer(T t);

	// method for printing logs to console
	template<typename T, typename... Args>
	static void log_writer(T t, Args... args);
	
	// method for prepare timestamp
	static std::string current_date_time()
	{
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[30];
    
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

		return buf;
	}
};


template<typename T0, typename ...T>
void LOG::E(T0 && t, T && ...args)
{
	if(LOG::current_log_level >= ERROR)
	{
		std::cout<<LOG::current_date_time()<< " \033[1;31mERROR:\033[0m    " << t << " "; 
		return log_writer(std::forward<T>(args)...);
	}
}
	
template<typename T0, typename ...T>
void LOG::W(T0 && t, T && ...args)
{
	
	if(LOG::current_log_level >= WARNING)
	{
		std::cout<<LOG::current_date_time()<< " \033[1;35mWARNING:\033[0m  " << t << " "; 
		return log_writer(std::forward<T>(args)...);
	}
}


template<typename T0, typename ...T>
void LOG::D(T0 && t, T && ...args)
{
	if(LOG::current_log_level >= DEBUG)
	{
		std::cout<<LOG::current_date_time()<< " \033[1;34mDEBUG:\033[0m    " << t << " "; 
		return log_writer(std::forward<T>(args)...);
	}
}

template<typename T0, typename ...T>
void LOG::I(T0 && t, T && ...args)
{
	if(LOG::current_log_level >= INFO)
	{
		std::cout<<LOG::current_date_time()<< " \033[1;33mINFO:\033[0m     " << t << " "; 
		return log_writer(std::forward<T>(args)...);
	}
}

template<typename T0, typename ...T>
void LOG::V(T0 && t, T && ...args)
{
	if(LOG::current_log_level >= INFO)
	{
		std::cout<<LOG::current_date_time()<< " \033[1;37mVERBOSE:\033[0m  " << t << " ";
		return log_writer(std::forward<T>(args)...);
	}
}

template <typename T>
void LOG::log_writer(T t) 
{
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void LOG::log_writer(T t, Args... args)
{
	std::cout << t << " ";
	
	log_writer(args...) ;
}

#endif // LOG_HPP_INCLUDED

