#include    <JsonWriter.h>
#include    <Factory.h>
#include    <Exception.h>

#include    <string>

namespace {
bool const registered = example::Factory::RegisterWriter("json", example::JsonWriter::Factory);
std::string indent_pad {"  "};

std::string FormatText(std::string const& text, char escape = '"') {
    std::string result;
    for(auto const& value : text) {
        if(value == escape) result += '\\';
        result += value;
    }
    return result;
}
}

namespace example {
//  ----------------------------------------------------------------------------
//  JsonWriter::Factory
//  ----------------------------------------------------------------------------
std::unique_ptr<Writer> JsonWriter::Factory(std::ostream& os) {
    return std::make_unique<JsonWriter>(os);
}
//  ----------------------------------------------------------------------------
//  JsonWriter::HandleDocumentStart
//  ----------------------------------------------------------------------------
void JsonWriter::HandleDocumentStart(Token const& token) {
    if(!closure_.empty()) {
        throw Exception(-1, "Cannot embed document within document");
    }

    level_indent_ = indent_pad;
    os_ << '{';
    term_ = '\n';
    closure_.push(Token::Type::document_start);
}
//  ----------------------------------------------------------------------------
//  JsonWriter::HandleDocumentEnd
//  ----------------------------------------------------------------------------
void JsonWriter::HandleDocumentEnd(Token const& token) {
    if(closure_.top() != Token::Type::document_start) {
        throw Exception(-1, "No matching document start");
    }

    os_ << "\n}";
    closure_.pop();
}
//  ----------------------------------------------------------------------------
//  JsonWriter::HandleRecordStart
//  ----------------------------------------------------------------------------
void JsonWriter::HandleRecordStart(Token const& token) {
    closure_.push(Token::Type::record_start);
    os_ << term_ << level_indent_;
    if(!token.key_.empty()) {
        os_ << '"' << token.key_ << "\":";
    }
    os_ << '{';
    level_indent_ += indent_pad;
    term_ = "\n";
}
//  ----------------------------------------------------------------------------
//  JsonWriter::HandleRecordEnd
//  ----------------------------------------------------------------------------
void JsonWriter::HandleRecordEnd(Token const& token) {
    if(closure_.top() != Token::Type::record_start) {
        throw Exception(-1, "No matching record start");
    }

    closure_.pop();
    level_indent_.resize(level_indent_.size() - indent_pad.size());
    os_ << "\n" << level_indent_ << "}";
    term_ = ",\n";
}
//  ----------------------------------------------------------------------------
//  JsonWriter::HandleListStart
//  ----------------------------------------------------------------------------
void JsonWriter::HandleListStart(Token const& token) {
    closure_.push(Token::Type::list_start);
    os_ << term_ << level_indent_ << '"' << token.key_ << "\": [";
    level_indent_ += indent_pad;
    term_ = '\n';
}
//  ----------------------------------------------------------------------------
//  JsonWriter::HandleListEnd
//  ----------------------------------------------------------------------------
void JsonWriter::HandleListEnd(Token const& token) {
    if(closure_.top() != Token::Type::list_start) {
        throw Exception(-1, "No matching list start");
    }

    closure_.pop();
    level_indent_.resize(level_indent_.size() - indent_pad.size());
    os_ << '\n' << level_indent_ << ']';
    term_ = ",\n";
}
//  ----------------------------------------------------------------------------
//  JsonWriter::HandleKeyValue
//  ----------------------------------------------------------------------------
void JsonWriter::HandleKeyValue(Token const& token) {
    os_<< term_ << level_indent_ << '"' << token.key_ << "\": \"" << FormatText(token.value_) << '"';
    term_ = ",\n";
}
}
