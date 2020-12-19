#include    <Writer.h>
#include    <Exception.h>

namespace example {
//  ----------------------------------------------------------------------------
//  Writer::Writer
//  ----------------------------------------------------------------------------
Writer::Writer(std::ostream& os) :
    os_(os)
{
    dispatch_table_.rehash(static_cast<size_t>(Token::Type::number_of_tokens));
    dispatch_table_[Token::Type::document_start] = Handler([&](Token const& token) { HandleDocumentStart(token); });
    dispatch_table_[Token::Type::document_end] = Handler([&](Token const& token) { HandleDocumentEnd(token); });
    dispatch_table_[Token::Type::record_start] = Handler([&](Token const& token) { HandleRecordStart(token); });
    dispatch_table_[Token::Type::record_end] = Handler([&](Token const& token) { HandleRecordEnd(token); });
    dispatch_table_[Token::Type::list_start] = Handler([&](Token const& token) { HandleListStart(token); });
    dispatch_table_[Token::Type::list_end] = Handler([&](Token const& token) { HandleListEnd(token); });
    dispatch_table_[Token::Type::key_value] = Handler([&](Token const& token) { HandleKeyValue(token); });
    dispatch_table_[Token::Type::null] = Handler([&](Token const& token) { HandleNull(token); });
} 
//  ----------------------------------------------------------------------------
//  Writer::operator()
//  ----------------------------------------------------------------------------
void Writer::operator()(Token const& token) {
    auto const& handler = dispatch_table_.find(token.type_);
    if(handler != dispatch_table_.end()) {
        handler->second(token);
        return;
    }

    throw Exception(-1, "Cannot handle token type");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleDocumentStart
//  ----------------------------------------------------------------------------
void Writer::HandleDocumentStart(Token const& token) {
    throw Exception(-1, "Document Start token not handled");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleDocumentEnd
//  ----------------------------------------------------------------------------
void Writer::HandleDocumentEnd(Token const& token) {
    throw Exception(-1, "Document End token not handled");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleRecordStart
//  ----------------------------------------------------------------------------
void Writer::HandleRecordStart(Token const& token) {
    throw Exception(-1, "Record Start token not handled");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleRecordEnd
//  ----------------------------------------------------------------------------
void Writer::HandleRecordEnd(Token const& token) {
    throw Exception(-1, "Record End token not handled");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleListStart
//  ----------------------------------------------------------------------------
void Writer::HandleListStart(Token const& token) {
    throw Exception(-1, "List Start token not handled");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleListEnd
//  ----------------------------------------------------------------------------
void Writer::HandleListEnd(Token const& token) {
    throw Exception(-1, "List End token not handled");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleKeyValue
//  ----------------------------------------------------------------------------
void Writer::HandleKeyValue(Token const& token) {
    throw Exception(-1, "Key Value token not handled");
}
//  ----------------------------------------------------------------------------
//  Writer::HandleNull
//  ----------------------------------------------------------------------------
void Writer::HandleNull(Token const& token) {
}
}
