#pragma once
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>

class Log
{
   public:
    enum class Level
    {
        Trace,
        Debug,
        Info,
        Warn,
        Error,
        Critical
    };

    // Enable or disable colors
    static inline bool useColor = true;

    static void setLevel(Level lvl) { minLevel = lvl; }

    template <typename... Args>
    static void trace(Args&&... args)
    {
        write(Level::Trace, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void debug(Args&&... args)
    {
        write(Level::Debug, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void info(Args&&... args)
    {
        write(Level::Info, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void warn(Args&&... args)
    {
        write(Level::Warn, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void error(Args&&... args)
    {
        write(Level::Error, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void critical(Args&&... args)
    {
        write(Level::Critical, std::forward<Args>(args)...);
    }

   private:
    static inline Level minLevel = Level::Trace;
    static inline std::mutex writeMutex;

    static const char* levelName(Level lvl)
    {
        switch (lvl)
        {
            case Level::Trace:
                return "TRACE";
            case Level::Debug:
                return "DEBUG";
            case Level::Info:
                return "INFO ";
            case Level::Warn:
                return "WARN ";
            case Level::Error:
                return "ERROR";
            case Level::Critical:
                return "CRIT ";
        }
        return "UNKWN";
    }

    static const char* levelColor(Level lvl)
    {
        if (!useColor) return "";

        switch (lvl)
        {
            case Level::Trace:
                return "\033[90m";  // gray
            case Level::Debug:
                return "\033[36m";  // cyan
            case Level::Info:
                return "\033[32m";  // green
            case Level::Warn:
                return "\033[33m";  // yellow
            case Level::Error:
                return "\033[31m";  // red
            case Level::Critical:
                return "\033[41m\033[97m";  // red background, white text
        }
        return "";
    }

    static void resetColor()
    {
        if (useColor) std::cout << "\033[0m";
    }

    template <typename... Args>
    static void write(Level lvl, Args&&... args)
    {
        if (lvl < minLevel) return;

        std::lock_guard<std::mutex> lock(writeMutex);

        // timestamp
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        auto tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::put_time(&tm, "%H:%M:%S");

        // message
        std::ostringstream msg;
        (msg << ... << args);

        // print
        std::cout << levelColor(lvl) << "[" << oss.str() << "] " << levelName(lvl) << " " << msg.str();

        resetColor();
        std::cout << std::endl;
    }
};
