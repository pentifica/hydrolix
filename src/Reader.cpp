#include    <Reader.h>

namespace example::private_do_not_use {
iterator::iterator(Reader* reader) :
    reader_(reader),
    token_((*reader)())
{
}
iterator::iterator(iterator const& rhs) :
    reader_(rhs.reader_),
    token_(rhs.token_)
{
}
iterator::iterator(iterator&& rhs) :
    reader_(rhs.reader_),
    token_(std::move(rhs.token_))
{
}
iterator iterator::operator++() {
    token_ =  (*reader_)();
    return *this;
}
iterator iterator::operator++(int) {
    auto current = *this;
    token_ = (*reader_)();
    return current;
}
const_iterator::const_iterator(Reader const* reader) :
    reader_(const_cast<Reader*>(reader)),
    token_((*reader_)())
{
}
const_iterator::const_iterator(const_iterator const& rhs) :
    reader_(rhs.reader_),
    token_(rhs.token_)
{
}
const_iterator::const_iterator(const_iterator&& rhs) :
    reader_(rhs.reader_),
    token_(std::move(rhs.token_))
{
}
const_iterator const_iterator::operator++() {
    token_ =  (*reader_)();
    return *this;
}
const_iterator const_iterator::operator++(int) {
    auto current = *this;
    token_ = (*reader_)();
    return current;
}
}
