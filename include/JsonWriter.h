#pragma once

#include    <Writer.h>

#include    <memory>
#include    <functional>
#include    <stack>
#include    <unordered_map>

namespace example {
class JsonWriter : public Writer {
    public:
        using Writer::Writer;
        ~JsonWriter() override = default;
        JsonWriter& operator=(JsonWriter const&) = delete;
        JsonWriter& operator=(JsonWriter&&) = delete;
        /// Factory to produce instances of the JsonWriter
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

        using Closure = std::stack<Token::Type>;

        Closure closure_;
        std::string level_indent_;
        std::string term_;
};
}
