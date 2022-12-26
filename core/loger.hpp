#ifndef LOGER_HPP
#define LOGER_HPP

#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 
#include <fstream> 
#include <ctime>
//прописываем избегание ошибки из-pf localtime
#pragma warning(disable: 4996)

static std::ofstream* file;

static void start_loger(const char* name_file)
{
    file = new std::ofstream(name_file);
}

static void log(const char* text)
{
    if (file != nullptr) {

        time_t now = time(NULL);
        tm* ltm = localtime(&now);

        * file << 1900 + ltm->tm_year << ":" << 1 + ltm->tm_mon << ":" << ltm->tm_mday << ":" << ltm->tm_hour << ":" << ltm->tm_min << ":" << 1 + ltm->tm_sec << " - - - " << text << std::endl;
    }
}

static void end_loger()
{
    file->close();
}



//static void loger(const char* text) {
//    start_loger("loger.txt");
//    log(text);
//    end_loger();
//}
#endif //LOGER_HPP
