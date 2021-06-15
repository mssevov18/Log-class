#include "Log.h"

void CreateSaveDir()
{
	system("mkdir C:/Logs");
	system("mkdir C:/Logs/Log-class");
	system("cls");
}

std::string AddLeadingZeroes(int num)
{
	std::string temp = "";
	if (num < 10 and num >= 0)
		temp += L'0';
	temp += std::to_string(num);
	return temp;
}

std::string TmToDateString(tm tm, char delimiter)
{
	std::string out = "";
	out += AddLeadingZeroes(tm.tm_year + 1900) + delimiter;
	out += AddLeadingZeroes(tm.tm_mon + 1) + delimiter;
	out += AddLeadingZeroes(tm.tm_mday);
	return out;
}

std::string TmToTimeString(tm tm, char delimiter)
{
	std::string out = "";
	out += AddLeadingZeroes(tm.tm_hour) + delimiter;
	out += AddLeadingZeroes(tm.tm_min) + delimiter;
	out += AddLeadingZeroes(tm.tm_sec);
	return out;
}

std::string SeverityToString(SEVERITY severity)
{
	switch (severity)
	{
	case $critical:
		return "CRITICAL";
	case $error:
		return "ERROR";
	case $warning:
		return "WARNING";
	case $debug:
		return "DEBUG";
	case $info:
		return "INFO";
	case $text:
		return "";
	default:
		return "UNKNOWN";
	}
}

void LOG::Log(SEVERITY severity, std::string message)
{
	this->severity = severity;
	this->message = message;
	time_t _t;
	time(&_t);
	localtime_s(&timeStamp, &_t);
}

void LOG::operator()(SEVERITY severity, std::string message)
{
	this->severity = severity;
	this->message = message;
	time_t _t;
	time(&_t);
	localtime_s(&timeStamp, &_t);
	logFstream << LogToString() << '\n';
}

std::string LOG::LogToString(char delimiter)
{
	if (severity!=$text)
	{
		// Add centering rules!
		// Compare strings and shit

		return (
			TmToDateString(timeStamp)  + delimiter + 
			TmToTimeString(timeStamp)  + delimiter + 
			SeverityToString(severity) + delimiter + 
			message
			);
	}
	return (message);
}

LOG::LOG(bool ornamental)
{
	this->severity = $info;
	this->message = "";
	this->ornamental = ornamental;
}

LOG::LOG(std::string path, bool ornamental)
{
	this->ornamental = ornamental;
	this->Open("C:/Users/mssevov18/Documents/Logs/logs.log");
}

void LOG::PrintLog()
{
	std::cout << LogToString() << std::endl;
}

bool LOG::Open(std::string path)
{
	logFstream.open(path, std::ios::out | std::ios::app);
	if (logFstream.is_open())
	{
		if (ornamental)
			logFstream << "====  ====  ====| Start of Log |====  ====  ====\n";
		else
			logFstream << "Start of Log\n";
		return true;
	}
	return false;
}

bool LOG::Is_Open()
{
	return logFstream.is_open();
}

void LOG::Close()
{
	if (ornamental)
		logFstream << "====  ====  ====| End  of  Log |====  ====  ====\n\n";
	else
		logFstream << "End of Log\n\n";
	logFstream.close();
}

void LOG::SaveLog()
{
	PrintLog();
	logFstream << LogToString() << '\n';
}