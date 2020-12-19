#include    <Factory.h>

#include    <unordered_map>

namespace {
using namespace example;
using ReaderLookup = std::unordered_map<std::string, Factory::ReaderFactory>;
using WriterLookup = std::unordered_map<std::string, Factory::WriterFactory>;

ReaderLookup *reader_lookup = nullptr;
WriterLookup *writer_lookup = nullptr;
}

namespace example {
//  ----------------------------------------------------------------------------
//  Factory::RegisterReader
//  ----------------------------------------------------------------------------
bool Factory::RegisterReader(std::string const& name, ReaderFactory factory) {
    static ReaderLookup lookup;
    if(reader_lookup == nullptr) reader_lookup = &lookup;
    lookup.emplace(name, factory);
    return true;
}
//  ----------------------------------------------------------------------------
//  Factory::RegisterWriter
//  ----------------------------------------------------------------------------
bool Factory::RegisterWriter(std::string const& name, WriterFactory factory) {
    static WriterLookup lookup;
    if(writer_lookup == nullptr) writer_lookup = &lookup;
    lookup.emplace(name, factory);
    return true;
}
//  ----------------------------------------------------------------------------
//  Factory::LookupReader
//  ----------------------------------------------------------------------------
Factory::ReaderRef Factory::LookupReader(std::string const& name, std::istream& is) {
    auto const factory = reader_lookup->find(name);
    return factory != reader_lookup->end() ? factory->second(is) : ReaderRef();
}
//  ----------------------------------------------------------------------------
//  Factory::LookupWriter
//  ----------------------------------------------------------------------------
Factory::WriterRef Factory::LookupWriter(std::string const& name, std::ostream& os) {
    auto const factory = writer_lookup->find(name);
    return factory != writer_lookup->end() ? factory->second(os) : WriterRef();
}
//  ----------------------------------------------------------------------------
//  Factory::ReaderList
//  ----------------------------------------------------------------------------
Factory::FactoryList Factory::ReaderList() {
    FactoryList list;
    list.reserve(reader_lookup->size());
    for(auto const& factory : *reader_lookup) {
        list.push_back(factory.first);
    }
    return list;
}
//  ----------------------------------------------------------------------------
//  Factory::WriterList
//  ----------------------------------------------------------------------------
Factory::FactoryList Factory::WriterList() {
    FactoryList list;
    list.reserve(writer_lookup->size());
    for(auto const& factory : *writer_lookup) {
        list.push_back(factory.first);
    }
    return list;
}
}
