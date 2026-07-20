#include "log.hpp"



Logger::Logger(FILE* logFilepointer):
logFile_inner(logFilepointer)
{
    logFile_inner = fopen("/usd/log.txt", "w");
    
    if (this->logFile_inner == NULL) {
        pros::screen::set_eraser(pros::Color::purple); // Set background to bluen
        pros::screen::erase(); // Clear with blue
        pros::screen::set_pen(pros::Color::white); // Set text color to white
        pros::lcd::print(0, "Error opening file!, check your SD card (BLAME SALACHO)");

    }
};



void Logger::log_to_file(const std::string& message){
    if (logFile_inner != NULL) {
        fprintf(logFile_inner, "%s\n", message.c_str());
    }
}

void Logger::end_logger(){
    fclose(this->logFile_inner);
    this->logFile_inner = NULL;
}