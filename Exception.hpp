//
// Created by FineArtz on 2018/04/12
//

#ifndef INC_2018DATASTRUCTUREBIGWORK_EXCEPTION_H
#define INC_2018DATASTRUCTUREBIGWORK_EXCEPTION_H

#include <cstddef>
#include <cstring>

namespace myAlgorithm{
class exception{
protected:
    char *info = nullptr;
public:
    exception() throw() = default;
    exception(const char *const &inf){
        strcpy(info, inf);
    }
    exception(const exception &other){
        strcpy(info, other.info);
    }
    virtual ~exception() throw(){
        delete info;
    }
    
    virtual const char *what() const throw();
};

class logic_error : public exception{
    logic_error() throw() = default;

    virtual const char *what() const throw(){
        return (info ? info : "logic error");
    }
};

class runtime_error : public exception{
    runtime_error() throw() = default;

    virtual const char *what() const throw(){
        return (info ? info : "runtime error");
    }
};

class invalid_iterator : public logic_error{
    invalid_iterator() throw() = default;

    virtual const char *what() const throw(){
        return (info ? info : "invalid iterator");
    }
};

class invalid_argument : public logic_error{
    invalid_argument() throw() = default;

    virtual const char *what() const throw(){
        return (info ? info : "invalid argument");
    }
};

class out_of_range : public runtime_error{
    out_of_range() throw() = default;

    virtual const char *what() const throw(){
        return (info ? info : "index out of range");
    }
};

}
#endif