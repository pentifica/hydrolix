#include    <Translator.h>
#include    <Exception.h>

int main(int argc, char** argv) {
    using namespace example;
    try {
        Translator translator(argc, argv);
        translator.Run();
    }
    catch(Exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}
