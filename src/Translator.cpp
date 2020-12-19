#include    <Translator.h>
#include    <Exception.h>

#include    <cstdlib>
#include    <fstream>

#include    <unistd.h>
#include    <getopt.h>

namespace example {
//  ----------------------------------------------------------------------------
//  Translator::Usage
//  ----------------------------------------------------------------------------
void Translator::Usage(char const* prog, char const* message) {
    if(message != nullptr) {
        std::cerr << message << "\n\n";
    }

    std::cerr << "usage: " << prog
         << " [-i <input>] [-o <output>] --from <format> --to <format>"
            " [--help|-?] [--list_from] [--list_to] [--list-all]\n"
            "where: i .......... The pathname of the input file\n"
            "       o .......... The pathname of the outpput file\n"
            "       ?|help ..... Display this help screen and exit\n"
            "       from ....... The format type of the input\n"
            "       to ......... The format type of the output\n"
            "       list-from .. List all input format types\n"
            "       list-to .... List all output format types\n"
            "       list-all ... List all input/output format types\n";

    throw Exception(-1, "Help reported");
}
//  ----------------------------------------------------------------------------
//  Translator::Args
//  ----------------------------------------------------------------------------
void Translator::Args(int argc, char** argv) {

    char const* const short_options ="?i:o:";
    struct option long_options[] = {
        { "from",      required_argument, 0, 0 },
        { "to",        required_argument, 0, 0 },
        { "help",      no_argument,       0, 0 },
        { "list-from", no_argument,       0, 0 },
        { "list-to",   no_argument,       0, 0 },
        { "list-all",  no_argument,       0, 0 },
        { 0,           0,                 0, 0 }
    };

    while(true) {
        int option_index = 0;
        auto opt = getopt_long(argc, argv, short_options, long_options, &option_index);
        switch(opt) {
            case '?':   Usage(argv[0]);         break;
            case 'i':   from_file_ = optarg;    break;
            case 'o':   to_file_ = optarg;      break;

            case 0:
                switch(option_index) {
                    case 0: from_type_ = optarg;    break;
                    case 1: to_type_ = optarg;      break;
                    case 2: Usage(argv[0]);         break;
                    case 3: list_readers_ = true;   break;
                    case 4: list_writers_ = true;   break;
                    case 5: list_readers_ = list_writers_ = true;   break;
                    default:
                        Usage(argv[0], "Unrecognized option");
                        break;
                }
                break;
            default:
                return;
        }
    }
}
//  ----------------------------------------------------------------------------
//  Translator::Setup
//  ----------------------------------------------------------------------------
void Translator::Setup() {
    //  list readers
    if(list_readers_) {
        auto const& readers = Factory::ReaderList();
        if(readers.empty()) {
            std::clog << "No read formats available\n";
        }
        else {
            std::clog << "Read Formats:\n";
            for(auto const& reader : readers) {
                std::clog << "    " << reader << '\n';
            }
        }
    }

    //  list writers
    if(list_writers_) {
        auto const& writers = Factory::WriterList();
        if(writers.empty()) {
            std::clog << "No read formats available\n";
        }
        else {
            std::clog << "Write Formats:\n";
            for(auto const& writer : writers) {
                std::clog << "    " << writer << '\n';
            }
        }
    }

    //  if list generated - terminate
    if(list_readers_ || list_writers_) {
        throw Exception(-1, "To list generated");
    }

    //  set input stream
    if(!from_file_.empty()) {
       is_conf_ = std::make_unique<std::ifstream>(from_file_.c_str());
       is_ = is_conf_.get();
    }
    else {
        is_ = &std::cin;
    }
    reader_ = Factory::LookupReader(from_type_, *is_);
    if(!reader_) {
        throw Exception(-1, "Cannot find reade format");
    }

    //  set output stream
    if(!to_file_.empty()) {
       os_conf_ = std::make_unique<std::ofstream>(to_file_.c_str());
       os_ = os_conf_.get();
    }
    else {
        os_ = &std::cout;
    }
    writer_ = Factory::LookupWriter(to_type_, *os_);
    if(!writer_) {
        throw Exception(-1, "Cannot find write format");
    }
}
//  ----------------------------------------------------------------------------
//  Translator::Translator
//  ----------------------------------------------------------------------------
Translator::Translator(int argc, char** argv) {
    Args(argc, argv);
    Setup();
}
//  ----------------------------------------------------------------------------
//  Translator::Run
//  ----------------------------------------------------------------------------
void Translator::Run() {
    for(auto const& token : *reader_) {
        (*writer_)(token);
    }
}
}
