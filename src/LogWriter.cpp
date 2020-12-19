#include    <LogWriter.h>
#include    <Factory.h>

namespace {
std::string const tab {"  "};
bool const registered = example::Factory::RegisterWriter("log", example::LogWriter::Factory);
}

namespace example {
//  ----------------------------------------------------------------------------
//  LogWriter::Factory
//  ----------------------------------------------------------------------------
std::unique_ptr<Writer> LogWriter::Factory(std::ostream& os) {
    return std::make_unique<LogWriter>(os);
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleDocumentStart
//  ----------------------------------------------------------------------------
void LogWriter::HandleDocumentStart(Token const& token) {
    os_ << "*****> Document start\n";
    indent_ += tab;
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleDocumentEnd
//  ----------------------------------------------------------------------------
void LogWriter::HandleDocumentEnd(Token const& token) {
    os_ << "<***** Document end\n";
    indent_ = "";
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleRecordStart
//  ----------------------------------------------------------------------------
void LogWriter::HandleRecordStart(Token const& token) {
    os_ << indent_ << "=====> Record start\n";
    indent_ += tab;
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleRecordEnd
//  ----------------------------------------------------------------------------
void LogWriter::HandleRecordEnd(Token const& token) {
    indent_.resize(indent_.size() - tab.size());
    os_ << indent_ << "<===== Record end\n";
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleListStart
//  ----------------------------------------------------------------------------
void LogWriter::HandleListStart(Token const& token) {
    os_ << indent_ << "-----> List start\n";
    indent_ += tab;
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleListEnd
//  ----------------------------------------------------------------------------
void LogWriter::HandleListEnd(Token const& token) {
    indent_.resize(indent_.size() - tab.size());
    os_ << indent_ << "<----- List end\n";
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleKeyValue
//  ----------------------------------------------------------------------------
void LogWriter::HandleKeyValue(Token const& token) {
    os_ << indent_ << token.key_ << ": \"" << token.value_ << "\"\n";
}
//  ----------------------------------------------------------------------------
//  LogWriter::HandleNull
//  ----------------------------------------------------------------------------
void LogWriter::HandleNull(Token const& token) {
    os_ << "!!!!! NULL !!!!!\n";
}
}
