#include    <Token.h>

namespace example {
Token::Token(Token::Type type, std::string const& key, std::string const& value) :
    type_(type),
    key_(key),
    value_(value)
{
}

Token::Token(Token&& token) :
    type_(token.type_),
    key_(std::move(token.key_)),
    value_(std::move(token.value_))
{
}

Token& Token::operator=(Token&& token) {
    type_ = token.type_;
    key_ = std::move(token.key_);
    value_ = std::move(token.value_);
    return *this;
}
}
