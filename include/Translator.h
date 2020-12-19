#pragma once

#include    <Factory.h>

namespace example {
class Translator {
    public:
        Translator(int argc, char** argv);
        Translator(Translator const&) = delete;
        Translator(Translator&&) = delete;
        ~Translator() = default;
        void Run();
    private:
        void Args(int argc, char** argv);
        void Usage(char const* prog, char const* message = nullptr);
        void Setup();
        std::istream* is_;          //!< the configured input stream
        std::ostream* os_;          //!< the configured output stream
        std::unique_ptr<std::istream> is_conf_;
        std::unique_ptr<std::ostream> os_conf_;
        Factory::ReaderRef reader_;
        Factory::WriterRef writer_;
        
        std::string from_type_;
        std::string from_file_;
        std::string to_type_;
        std::string to_file_;
        bool list_readers_ {false};
        bool list_writers_ {false};
};
}
