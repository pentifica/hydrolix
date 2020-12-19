#include    <CsvReader.h>
#include    <Factory.h>

#include    <sstream>

namespace {
//  @TODO   The following code does not provide for the csv escape sequences.  Need to replace
//          with a regular expression (regex) algo
std::vector<std::string> Split(std::string&& line) {
    std::vector<std::string> columns;
    std::string column;
    std::istringstream iss(std::move(line));
    while(std::getline(iss, column, ',')) {
        columns.push_back(column);
    }
    return columns;
}

const bool registered = example::Factory::RegisterReader("csv", example::CsvReader::Factory);
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
