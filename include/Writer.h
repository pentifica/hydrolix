#pragma once

#include    <Token.h>

#include    <iostream>
#include    <functional>
#include    <unordered_map>

namespace example {
class Writer {
    public:
        Writer(std::ostream& os);
        Writer(Writer const&) = delete;
        Writer(Writer&&) = delete;
        virtual ~Writer() = default;
        void operator()(Token const& token);
        Writer& operator=(Writer const&) = delete;
        Writer& operator=(Writer&&) = delete;
    protected:
        virtual void HandleDocumentStart(Token const& token);
        virtual void HandleDocumentEnd(Token const& token);
        virtual void HandleRecordStart(Token const& token);
        virtual void HandleRecordEnd(Token const& token);
        virtual void HandleListStart(Token const& token);
        virtual void HandleListEnd(Token const& token);
        virtual void HandleKeyValue(Token const& token);
        virtual void HandleNull(Token const& token);

        using Handler = std::function<void(Token const&)>;
        using DispatchTable = std::unordered_map<Token::Type, Handler>;

        DispatchTable dispatch_table_;
        std::ostream& os_;
};
}
