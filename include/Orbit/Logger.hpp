/*
 * Project: Orbit Engine
 * File: Logger.hpp
 * Author: Marius "Astroboy" Van Nieuwenhuyse
 */

#ifndef ORBITENGINE_LOGGER_H
#define ORBITENGINE_LOGGER_H

#include <iostream>

#define info(...) Logger::__info(__FILE__, __LINE__, __VA_ARGS__)
#define cinfo(...) Logger::__info(__VA_ARGS__)
#define warning(...) Logger::__warning(__FILE__, __LINE__, __VA_ARGS__)
#define cwarning(...) Logger::__warning(__VA_ARGS__)
#define error(...) Logger::__error(__FILE__, __LINE__, __VA_ARGS__)
#define cerror(...) Logger::__error(__VA_ARGS__)

namespace Orbit {
    class Logger {
    public:
        template<typename T, typename... Args>
        static void __info(T t, Args... args) {
            std::cout << t << ", ";
            Logger::__info(args...);
        }

        template<typename T>
        static void __info(T t) {
            std::cout << t << std::endl;
        }

        template<typename... Args>
        static void __info(const char *file, const int line, Args... args) {
            std::cout << "[info][" << file << ':' << line << "] ";
            Logger::__info(args...);
        }

        template<typename T, typename... Args>
        static void __warning(T t, Args... args) {
            std::cout << t << ", ";
            Logger::__warning(args...);
        }

        template<typename T>
        static void __warning(T t) {
            std::cout << t << std::endl;
        }

        template<typename... Args>
        static void __warning(const char *file, const int line, Args... args) {
            std::cout << "[warning][" << file << ':' << line << "] ";
            Logger::__warning(args...);
        }

        template<typename T, typename... Args>
        static void __error(T t, Args... args) {
            std::cerr << t << ", ";
            Logger::__error(args...);
        }

        template<typename T>
        static void __error(T t) {
            std::cerr << t << std::endl;
        }

        template<typename... Args>
        static void __error(const char *file, const int line, Args... args) {
            std::cerr << "[error][" << file << ':' << line << "] ";
            Logger::__error(args...);
        }
    };
}

#endif //ORBITENGINE_LOGGER_H
