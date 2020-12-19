# hydrolix
CSV coding exercise

## Readers
Readers consume the contents of a stream and produce tokens based on the format specification for the data in the stream.
### csv
The *csv* reader consumes a csv-formatted file and produces tokens that can be processed by one or more writers.
The first line of the csv file (header line) is interpreted to be comma separated fields. Each field represents the name (kry) associated with the data in the column. The data is located in lines 2 through the end of the file (data line). Empty data lines are ignored.

The header line establishes the maximum number of columns that will be processed in each data line. When a data line contains more columns than established by the header line, the excess columns are ignored and a message is streamed to std::clog indicating the line that is being truncated. No warning is issued when a data line contains fewer columns than the header line.  Tokens are not generated for the missing columns.  Also, a token is not generated when a column is empty.
## Writers
Writers consume tokens and produce an output stream based on the requirements of the writer's format specification.
### json
The *json* writer produces a json formatted file from the tokens provided.
### log
The *log* writer generates a log of tokens output by a reader.  It makes no decision repective the tokens.  Merely reports each token produced by a reader.
## TODO
* CsvReader - The current parser for the comma separated fields is primitive and only identifies column start/end  based on the existence of a **","**. Need to replace with a parser that understands csv escape sequences.
