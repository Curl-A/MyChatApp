#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <string>
#include <mutex>
class Logger {
    private:
	std::fstream f;
	std::mutex mtx;

    public:
	Logger(const std::string& filename);
	~Logger();

	//function declarations
	std::string currentTime() const;
	void log(const std::string& level,const std::string& message);

};
#endif	
