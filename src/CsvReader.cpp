#include    <CsvReader.h>
#include    <Factory.h>
#include    <Exception.h>

#include    <sstream>

namespace {
/// A simple csv record processor that assume no special characters are
/// embedded in each column.
///
/// @param[in]  line    The record to process
/// @return The contents of the individual columns
std::vector<std::string> SplitSimple(std::string&& line) {
    std::vector<std::string> columns;
    std::string column;
    std::istringstream iss(std::move(line));
    while(std::getline(iss, column, ',')) {
        columns.push_back(column);
    }
    return columns;
}
/// Processing state for the line parser
enum class ParseState {
    initial,
    simple,
    literal,
    escape,
};
/// A csv record processor that recognizes special characters embedded in a
///
/// @param[in]  line    The record to process
/// @return The contents of the individual columns
std::vector<std::string> SplitSpecial(std::string&& line) {
    std::vector<std::string> result;
    std::string column;
    ParseState state = ParseState::initial;
    for(auto ch : line) {
        switch(state) {
            case ParseState::initial:
                switch(ch) {
                    case '"':
                        state = ParseState::literal;
                        break;
                    case ',':
                        result.emplace_back("");
                        break;
                    default:
                        column = ch;
                        state = ParseState::simple;
                        break;
                }
                break;
            case ParseState::simple:
                if(ch == ',') {
                    result.emplace_back(column);
                    column = "";
                    state = ParseState::initial;
                }
                else {
                    column += ch;
                }
                break;

            case ParseState::literal:
                if(ch == '"') {
                    state = ParseState::escape;
                }
                else {
                    column += ch;
                }
                break;

            case ParseState::escape:
                switch(ch) {
                    case '"':
                        column += '"';
                        state = ParseState::literal;
                        break;
                    case ',':
                        state = ParseState::initial;
                        result.emplace_back(column);
                        column = "";
                        break;
                    default:
                        throw example::Exception(-1, "CSV syntax error");
                }
                break;
        }
    }


    if(!column.empty()) {
        result.emplace_back(column);
    }
    return result;
}
/// A selector for which csv record parser to use
///
/// @param[in]  line    The record to process
/// @return The contents of the individual columns
inline std::vector<std::string> Split(std::string&& line) { return SplitSpecial(std::move(line)); }
/// Registers this reader with the factory
bool const registered = example::Factory::RegisterReader("csv", example::CsvReader::Factory);
}

namespace example {
//  ----------------------------------------------------------------------------
//  CsvReader::Factory
//  ----------------------------------------------------------------------------
std::unique_ptr<Reader> CsvReader::Factory(std::istream& is) {
    return std::make_unique<CsvReader>(is);
}
//  ----------------------------------------------------------------------------
//  CsvReader::CsvReader
//  ----------------------------------------------------------------------------
CsvReader::CsvReader(std::istream& is) :
    Reader::Reader(is)
{
    handler_ = Handler([&]() { return Initialize(); });
}
//  ----------------------------------------------------------------------------
//  CsvReader::Initialize
//  ----------------------------------------------------------------------------
Token CsvReader::Initialize() {
    //  in case a bad stream
    if(!is_) {
        handler_ = Handler([&]() { return Null(); });
        return Token();
    }

    //  unpack keys
    std::string header;
    std::getline(is_, header);
    if(!is_ || header.empty()) {
        return Token();
    }
    keys_ = Split(std::move(header));
    
    //  change state
    handler_ = Handler([&]() { return GetRecord(); });
    return Token(Token::Type::document_start);
}
//  ----------------------------------------------------------------------------
//  CsvReader::GetRecord
//  ----------------------------------------------------------------------------
Token CsvReader::GetRecord() {
    //  retrieve next line
    std::string line;
    std::getline(is_, line);
    if(!is_) {
        handler_ = Handler([&]() { return Null(); });
        return Token(Token::Type::document_end);
    }
    ++record_count_;

    //  unpack values
    values_ = Split(std::move(line));
    if(values_.empty()) {
        std::clog << "Record no. " << record_count_ << " empty - ignored\n";
        return GetRecord();
    }

    if(keys_.size() < values_.size()) {
        values_.resize(keys_.size());
        std::clog << "Record no. " << record_count_ << " truncated\n";
    }

    next_column_ = 0;
    handler_ = Handler([&]() { return NextColumn(); });
    return Token(Token::Type::record_start);
}
//  ----------------------------------------------------------------------------
//  CsvReader::NextColumn
//  ----------------------------------------------------------------------------
Token CsvReader::NextColumn() {
    //  if all columns in row exhausted
    if(next_column_ == values_.size()) {
        handler_ = Handler([&]() { return GetRecord(); });
        return Token(Token::Type::record_end);
    }

    //  return next column
    auto current = next_column_++;
    if(values_[current].empty()) {
        return NextColumn();
    }
    return Token(Token::Type::key_value, keys_[current], std::move(values_[current]));
}
}
