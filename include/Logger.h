#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <chrono>
#include <filesystem>
#include <sys/stat.h>

#define INFO(msg) Logger::Log::Info(msg, __FILE__,  __LINE__);
#define WARNING(msg) Logger::Log::Warning(msg, __FILE__,  __LINE__);
#define ERROR(msg) Logger::Log::Error(msg, __FILE__,  __LINE__);
#define DEBUG(msg) Logger::Log::Debug(msg, __FILE__,  __LINE__);

namespace Logger {
    class Log {
    private:
    static std::ofstream out;
    public:
        static void Write(const std::string& mode, const std::string& msg, std::string file = "", int line = 0) {
            std::chrono::time_point now = std::chrono::system_clock::now();
            time_t tt = std::chrono::system_clock::to_time_t(now);
            std::tm local_tm = *localtime(&tt);

            out << "[ " << (local_tm.tm_year + 1900) << "."
                << local_tm.tm_mon << "."<< local_tm.tm_mday << " "
                << local_tm.tm_hour << ":" << local_tm.tm_min << ":" << local_tm.tm_sec << " ]"
                << "[" << mode << "] " << msg << " " << (file.empty() ? "" : "File: " + file)
                << " " << (line == 0 ? "" : "Line: " + std::to_string(line)) << '\n';

            out.flush();
        }

        static void InitLogFile() {
            std::chrono::time_point now = std::chrono::system_clock::now();
            time_t tt = std::chrono::system_clock::to_time_t(now);
            std::tm local_tm = *localtime(&tt);

            if (!(std::filesystem::exists("logs")))
                std::filesystem::create_directory("logs");

            std::string filename = "logs\\log_" +
                    std::to_string(local_tm.tm_year + 1900) + "-" +
                    std::to_string(local_tm.tm_mon) + "-" +
                    std::to_string(local_tm.tm_mday) + ".txt";

            out.open(filename, std::ios::app);
            Write("INIT", "Init Logger");
        }

        static void Info(const std::string& msg, std::string file, int line) {
            Write("INFO", msg, file, line);
        }

        static void Debug(const std::string& msg, std::string file, int line) {
            std::cerr << msg << " " << "File: " << file << " " << "Line: " << line << std::endl;
        }

        static void Error(const std::string& msg, std::string file, int line) {
            Write("ERROR", msg, file, line);
        }

        static void Warning(const std::string& msg, std::string file, int line) {
            Write("WARNING", msg, file, line);
        }
    };
}


