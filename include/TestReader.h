#pragma once

#include    <Reader.h>

namespace example {
class TestReader : public Reader {
    public:
        using Reader::Reader;
        ~TestReader() override = default;
        Token operator()() override;
    private:
        size_t next_ {0};
};
}
