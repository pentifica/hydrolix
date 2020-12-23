#include    <TestReader.h>
#include    <Factory.h>

#include <vector>

namespace {
using namespace example;
std::vector<Token> tokens {
    Token(Token::Type::document_start, "", ""),
    Token(Token::Type::record_start, "", ""),
    Token(Token::Type::list_start, "list", ""),
    Token(Token::Type::key_value, "key", "value"),
    Token(Token::Type::list_end, "", ""),
    Token(Token::Type::record_start, "record", ""),
    Token(Token::Type::record_end, "", ""),
    Token(Token::Type::record_end, "", ""),
    Token(Token::Type::document_end, "", ""),
    Token(Token::Type::null, "", "")
};
bool const registered = example::Factory::RegisterReader("test", example::TestReader::Factory);
}
namespace example {
std::unique_ptr<Reader> TestReader::Factory(std::istream& is) {
    return std::make_unique<TestReader>(is);
}
Token TestReader::operator()() {
    return tokens[next_++ % tokens.size()];
}
}
