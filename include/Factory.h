#pragma once

#include    <Reader.h>
#include    <Writer.h>

#include    <functional>
#include    <vector>
#include    <memory>

namespace example {
class Factory {
    public:
        using ReaderRef = std::unique_ptr<Reader>;
        using WriterRef = std::unique_ptr<Writer>;
        using ReaderFactory = std::function<ReaderRef(std::istream&)>;
        using WriterFactory = std::function<WriterRef(std::ostream&)>;
        using FactoryList = std::vector<std::string>;

        /// Register a reader
        ///
        /// @param[in]  name    The human readable name for the reader
        /// @param[in]  factory The factory that produces the reader
        /// @return Always true
        static bool RegisterReader(std::string const& name, ReaderFactory factory);
        /// Register a writer
        ///
        /// @param[in]  name    The human readable name for the writer
        /// @param[in]  factory The factory that produces the writer
        /// @return Always true
        static bool RegisterWriter(std::string const& name, WriterFactory factory);
        /// Lookup a reader
        ///
        /// @param[in]  name    The name of the reader to look up
        /// @param[in]  is      The stream to associate with the reader
        /// @return The reader associated with the lookup name. If not found, a null
        ///         reference returned.
        static ReaderRef LookupReader(std::string const& name, std::istream& is);
        /// Lookup a writer
        ///
        /// @param[in]  name    The name of the writer to look up
        /// @param[in]  os      The stream to associate with the writer
        /// @return The writer associated with the lookup name. If not found, a null
        ///         reference returned.
        static WriterRef LookupWriter(std::string const& name, std::ostream& os);
        /// Return the names of the registered readers
        static FactoryList ReaderList();
        /// Return the names of the registered writers
        static FactoryList WriterList();
};
}
