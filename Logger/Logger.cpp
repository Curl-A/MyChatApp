#include "Logger.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>

Logger::Logger(const std::string& filename):f(filename,std::ios::app){
	if(!f){
	    std::cerr<<"Cannot create/open file - "<<std::endl;
	}
}

Logger::~Logger() {
       f.close();
}
	
std::string Logger::currentTime() const {
       std::time_t now = std::time(nullptr);
       std::tm* local = std::localtime(&now);
       std::stringstream ss;
       ss << std::put_time(local,"[%Y-%m-%d %H:%M:%S]");
       return ss.str();
}

void Logger::log(const std::string& level, const std::string& message) {
       std::lock_guard<std::mutex> lock(mtx);
       f << currentTime() <<" "<<level<<" "<<message<<std::endl;
}
