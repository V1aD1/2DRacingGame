//preprocessor directive that prevents a single header file
//from being included multiple times into a single translation unit
#pragma once

class Log {
public:
	const int LogLevelError = 0;
	const int LogLevelWarning = 1;
	const int LogLevelInfo = 2;


private:
	int logLevel = LogLevelInfo;

public:
	void SetLevel(int level);
	void Error(const char* message);
	void Warn(const char* message);
	void Info(const char* message);
};
