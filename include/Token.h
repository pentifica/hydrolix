#pragma once

#include    <string>

namespace example {
struct Token {
    enum class Type {
        document_start,
        document_end,
        record_start,
        record_end,
        list_start,         //!< start of a list
        list_end,           //!< end of a list
        key_value,          //!< a key/value pair
        null,               //!< nothing
        number_of_tokens
    };
    Token() : type_(Type::null) {}
    explicit Token(Type type, std::string const& key = "", std::string const& value = "");
    Token(Token const&) = default;
    Token(Token&&);
    virtual ~Token() = default;

    Token& operator=(Token const&) = default;
    Token& operator=(Token&& token);

    bool operator==(Token const& rhs) const {
        return type_ == rhs.type_
            && key_ == rhs.key_
            && value_ == rhs.value_;
    }
    bool operator!=(Token const& rhs) const {
        return !operator==(rhs);
    }

    Type type_;
    std::string key_;
    std::string value_;
};
}
