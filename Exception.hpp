//
// Created by FineArtz on 2018/04/12
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_EXCEPTION_H
#define INC_2018DATASTRUCTUREBIGWORK_EXCEPTION_H

#include <cstddef>
#include <cstring>
#include <iostream>
#include <csignal>

namespace myAlgorithm {
    class exception {
        friend class bad_exception;
    protected:
        char *info = nullptr;
    public:
        exception() throw() = default;

        explicit exception(const char *const &inf) {
            strcpy(info, inf);
        }

        exception(const exception &other) {
            strcpy(info, other.info);
        }

        virtual ~exception() throw() {
            delete info;
        }

        virtual const char *what() const throw(){

        }
    };

    class bad_exception{
        friend class exception;
    protected:
        char* info = nullptr;
        int retCode = 0;
    public:
        bad_exception() noexcept = default;
        explicit bad_exception(const char* const & inf) noexcept {
            strcpy(info, inf);
        }
        explicit bad_exception(const exception& rhs) noexcept {
            strcpy(info, rhs.info);
        }
        bad_exception(const bad_exception& rhs) noexcept {
            strcpy(info, rhs.info);
        }
        virtual ~bad_exception() noexcept {
            if(info != nullptr) delete info;
        }
        virtual const char* what() const noexcept{

        }
    };
    class fatal_error : public bad_exception{
        fatal_error() noexcept{
            std::cerr << "Fatal error Occured!";
#ifdef __unix
            //Todo: dump
#endif
#ifdef WINVER
            //Todo: dump
#endif
//            Experimental Feature
//            Danger! If you have handled the basic signal process and you raise a signal,
//            Fatal Error(incl. blue screen on Windows Platforms, System Halt on Mac OS Platforms) will OCCURED.
//            Whether it will cause hurt to the hardware is still UNKNOWN
//            Be sure your handler is correct to handle the signal.
//
//            raise(SIGABRT);
        }
        const char* what() const noexcept override {
            return (info ? info : "fatal error");
        }
    };
    class logic_error : public exception {
        logic_error() throw() = default;

        virtual const char *what() const throw() {
            return (info ? info : "logic error");
        }
    };

    class runtime_error : public exception {
        runtime_error() throw() = default;

        virtual const char *what() const throw() {
            return (info ? info : "runtime error");
        }
    };

    //Modified Apr.21 By PeterZheng
    class sql_error : public exception {
        sql_error() throw() = default;

        const char* what() const throw() override {
            return (info ? info : "sql_error");
        }
    };

    class invalid_iterator : public logic_error {
        invalid_iterator() throw() = default;

        virtual const char *what() const throw() {
            return (info ? info : "invalid iterator");
        }
    };

    class invalid_argument : public logic_error {
        invalid_argument() throw() = default;

        virtual const char *what() const throw() {
            return (info ? info : "invalid argument");
        }
    };

    class out_of_range : public runtime_error {
        out_of_range() throw() = default;

        virtual const char *what() const throw() {
            return (info ? info : "index out of range");
        }
    };

}
#endif