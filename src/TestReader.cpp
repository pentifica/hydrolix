#include    <TestReader.h>

#include <vector>

namespace {
    using namespace example;
    std::vector<Token> tokens {
        Token(Token::Type::document_start, "", ""),
        Token(Token::Type::record_start, "", ""),
        Token(Token::Type::list_start, "", ""),
        Token(Token::Type::key_value, "key", "value"),
        Token(Token::Type::list_end, "", ""),
        Token(Token::Type::record_end, "", ""),
        Token(Token::Type::document_end, "", ""),
        Token(Token::Type::null, "", "")
    };
}
namespace example {
Token TestReader::operator()() {
    return tokens[next_++ % tokens.size()];
}
}
