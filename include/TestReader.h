#pragma once

#include    <Reader.h>

#include    <memory>

namespace example {
class TestReader : public Reader {
    public:
        using Reader::Reader;
        ~TestReader() override = default;
        Token operator()() override;
        /// Factory to produce instances of CsvReader
        ///
        /// @param[in]  is  Input stream for reader
        /// @return A csv reader
        static std::unique_ptr<Reader> Factory(std::istream& is);
    private:
        size_t next_ {0};
};
}
