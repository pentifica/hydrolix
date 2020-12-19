#pragma once

#include    <Reader.h>

#include    <vector>
#include    <functional>
#include    <memory>

namespace example {
class CsvReader : public Reader {
    public:
        CsvReader(std::istream& is);
        /// @see Reader::operator()
        Token operator()() override { return handler_(); }
        /// Factory to produce instances of CsvReader
        ///
        /// @param[in]  is  Input stream for reader
        /// @return A csv reader
        static std::unique_ptr<Reader> Factory(std::istream& is);

    private:
        /// Initializes token production and produces a document start token.
        Token Initialize();
        /// Initializes processing of the next record and produces a record start
        /// token.  If no more records are found, produces a document end token.
        Token GetRecord();
        /// Produces the next key/value pair token from the current record.  If
        /// all key/values reported, produces a record end token.
        Token NextColumn();

        std::vector<std::string> keys_;             //!< the key for each column
        std::vector<std::string> values_;           //!< the column values in the current record
        size_t next_column_ {0};                    //!< next column to output
        size_t record_count_;                       //!< current record count
        using Handler = std::function<Token(void)>;
        Handler handler_;
};
}
