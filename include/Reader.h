#pragma once

#include    <Token.h>

#include    <iostream>
#include    <iterator>

namespace example {
class Reader;
namespace private_do_not_use {
class iterator {
    public:
        using self_type = iterator;
        using value_type = Token;
        using reference = Token&;
        using pointer = Token*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = size_t;
        iterator() : reader_(nullptr), token_(Token::Type::null) {}
        iterator(Reader* reader);
        iterator(iterator const& rhs);
        iterator(iterator&& rhs);
        ~iterator() = default;
        iterator operator++();
        iterator operator++(int);
        reference operator*() { return token_; }
        pointer operator->() { return &token_; }
        bool operator==(self_type const& rhs) const {
            return token_ == rhs.token_;
        }
        bool operator!=(self_type const& rhs) const {
            return !operator==(rhs);
        }

    private:
        Reader* reader_;
        mutable Token token_;
};
class const_iterator {
    public:
        using self_type = const_iterator;
        using value_type = Token;
        using reference = Token const&;
        using pointer = Token const*;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = size_t;
        const_iterator() : reader_(nullptr), token_(Token::Type::null) {}
        const_iterator(Reader const* reader);
        const_iterator(const_iterator const& rhs);
        const_iterator(const_iterator&& rhs);
        ~const_iterator() = default;
        const_iterator operator++();
        const_iterator operator++(int);
        reference operator*() { return token_; }
        pointer operator->() { return &token_; }
        bool operator==(self_type const& rhs) const {
            return reader_ == rhs.reader_ && token_ == rhs.token_;
        }
        bool operator!=(self_type const& rhs) const {
            return !operator==(rhs);
        }

    private:
        Reader* reader_;
        Token token_;
};
}
class Reader {
    public:
        Reader(std::istream& is) : is_(is) {}
        Reader(Reader const&) = delete;
        Reader(Reader&&) = delete;
        virtual ~Reader() = default;
        virtual Token operator()() = 0;
        Reader& operator=(Reader const&) = delete;
        Reader& operator=(Reader&&) = delete;

        using iterator = private_do_not_use::iterator;
        using const_iterator = private_do_not_use::const_iterator;
        iterator begin() { return iterator(this); }
        iterator end() { return iterator(); }
        const_iterator begin() const { return const_iterator(this); }
        const_iterator end() const { return const_iterator(); }

    protected:
        /// Always produces a null token
        Token Null() { return Token(); }
        std::istream& is_;
};
}
