#pragma once

#include    <exception>

namespace example {
class Exception : public std::exception {
    public:
        explicit Exception(int code, char const* description) noexcept :
            code_(code), description_(description) {}
        Exception(Exception const& that) noexcept = default;
        ~Exception() override = default;
        char const* what() const noexcept override { return description_; }
        int Code() const { return code_; }
    private:
        int code_;
        char const* description_;
};
}

