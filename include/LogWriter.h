#pragma once

#include    <Writer.h>

#include    <memory>

namespace example {
class LogWriter : public Writer {
    public:
        using Writer::Writer;
        ~LogWriter() override = default;
        LogWriter& operator=(LogWriter const&) = delete;
        LogWriter& operator=(LogWriter&&) = delete;
        /// Factory to produce instances of the LogWriter
        ///
        /// @param[in]  os  The stream to be used by the writer
        /// @return An instance ot the writer associated with the output stream
        static std::unique_ptr<Writer> Factory(std::ostream& os);
    protected:
        void HandleDocumentStart(Token const& token) override;
        void HandleDocumentEnd(Token const& token) override;
        void HandleRecordStart(Token const& token) override;
        void HandleRecordEnd(Token const& token) override;
        void HandleListStart(Token const& token) override;
        void HandleListEnd(Token const& token) override;
        void HandleKeyValue(Token const& token) override;
        void HandleNull(Token const& token) override;
    private:
        void Log(Token::Type type, std::string const& key, std::string const& value);
        std::string indent_;
};
}
