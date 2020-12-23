# hydrolix
CSV coding exercise
README.md
## Readers
Readers consume the contents of a stream and produce tokens based on the format specification for the data in the stream.
### csv
The *csv* reader consumes a csv-formatted file and produces tokens that can be processed by one or more writers.
The first line of the csv file (header line) is interpreted to be comma separated fields. Each field represents the name (key) associated with the data in the column. The data is located in lines 2 through the end of the file (data lines). Empty data lines are ignored.

The header line establishes the maximum number of columns that will be processed in each data line. When a data line contains more columns than established by the header line, the excess columns are ignored and a message is streamed to stdlog identifying the line that is being truncated. No warning is issued when a data line contains fewer columns than the header line.  Tokens are not generated for the missing columns.  Also, a token is not generated when a column is empty.
## Writers
Writers consume tokens and produce an output stream based on the requirements of the writer's format specification.
### json
The *json* writer produces a json formatted file from the tokens provided.
### log
The *log* writer generates a log of tokens output by a reader.  It makes no decision respective the tokens.  Merely reports each token produced by a reader.
## TODO
* **CsvReader** The current parser for the comma separated fields is primitive and only identifies column start/end  based on the existence of a **","**. Need to replace with a parser that understands csv special case sequences (eg. embedded **"** or **,** in the text).
* **Error handling** Error reporting is currently limited to throwing an *example::Exception* that contains a code and description.  The code is always **-1** but the description is specific to the type of failure.  Error reporting needs to be enhanced with a specific code for each failure type.  Also, more detail in the descriptions should be added to guide the user as to the specifics of the issue.
* **TestReader** This class produces canned tokens and was used for some initial simple testing.  It should be renamed to *TokenReader* and redesigned to read raw tokens from the input stream.
* Create a multi-format writer that would produce multiple outputs on a single read of a stream.
* Provide an optional configuration format that could be used in place of configuring from a command line.
* Provide a cmake build script
## Building
The code assumes a c++17 compliant compiler and uses only functions, templates, etc. from the std library. To build, follow these steps:

```
cd ...<path to install>/build
./configure
make
```
## Running
The name of the program is **translator**. The command line has the syntax:

    translator [-i <input>] [-o <output>] --from <format> --to <format>
    translator ((--list-from | --list-to) | --list-all)
    translator (-? | --help)

|option|description|
|------------------|-----------|
|-i \<input>|indicates the input stream to be translated. If absent, input is read from stdin|
|-o \<output>|indicates the output stream where the translated data will be written.  If absent, the output is written to stdout|
|--from \<format>|The format of the data to be translated|
|--to \<format>|The format of the translated data that is generated|
|--list-from|Lists the registered *from* formats. The program exits after listing the formats.|
|--list-to|Lists the registered *to* formats. The program exits after listing the formats.|
|--list-all|Lists all registered formats. The program exits after listing the formats.|
|-?|Display a help screen and exit|
|--help|Display a help screen and exit|
## manifest
|file|description|
|----|-----------|
|README.md|A file containing this descriptive text|
|src/CsvReader.cpp|Implements ingesting csv formatted files|
|src/Factory.cpp|Provides instances of readers and writers|
|src/JsonWriter.cpp|Implements producing json formatted files|
|src/LogWriter.cpp|Implements producing a log of the tokens generated by a reader|
|src/main.cpp|Bootstrap for starting translator|
|src/Reader.cpp|Implements the reader framework|
|src/TestReader.cpp|Implements a reader that produces all possible tokens (for testing)|
|src/Token.cpp|Tokens produced by readers and consumed by writers|
|src/Translator.cpp|Configures the translator and generates translated output|
|src/Writer.cpp|Implements the writer framework|
|include/CsvReader.h|Defines actions and state for a cvs reader|
|include/Exception.h|Defines actions and state for a cvs reader|
|include/Factory.h|Defines the actions and state for the factory|
|include/JsonWriter.h|Defines actions and state for a cvs reader|
|include/LogWriter.h|Defines actions and state for a cvs reader|
|include/Reader.h|Defines actions and state for a cvs reader|
|include/TestReader.h|Defines the actions and state for writer test|
|include/Token.h|Defines the characteristics of a token|
|include/Translator.h|Defines actions and state for the translator program|
|include/Writer.h|Defines actions and state for a cvs reader|
|build/Makefile.am|Describes makefile characteristics|
|build/configure.ac|Describes configration characteristics|
|build/configure|Creates a linux compatible Makefile to build the application| 
## Token description
Tokens produced by readers contain the following information:
    * Token id
    * Name of the token
    * Value associated with the token name
Both *name* and *value* can be any string of characters.  They can even be an empty string. The available token ids are defined in the file *Token.h*.
## Adding a Reader to the translator
All readers must be derived from the *Reader* class.
## Adding a writer to the translator
All writers must be derived from the *Writer* class.
