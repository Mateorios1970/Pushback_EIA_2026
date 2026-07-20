#include "main.h"
#include <cstdint>
#include "lemlib/api.hpp"
#include <iostream>
#include <fstream>


class Logger{
    public:
        Logger(FILE* logFilepointer);
        void log_to_file(const std::string& message);
        void end_logger();
    private:
        FILE *logFile_inner;

};



