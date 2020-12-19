bin_PROGRAMS = translator

translator_SOURCES = ../src/Token.cpp \
					 ../src/Writer.cpp \
					 ../src/LogWriter.cpp \
					 ../src/JsonWriter.cpp \
					 ../src/Reader.cpp \
					 ../src/TestReader.cpp \
					 ../src/CsvReader.cpp \
					 ../src/Factory.cpp \
					 ../src/Translator.cpp \
					 ../src/main.cpp

translator_CXXFLAGS = -std=c++17 \
					  -I../include

ACLOCAL_AMFLAGS = -I m4

translator_LDADD = -L/usr/lib64 \
				   -ldl \
				   -lrt \
				   -lstdc++ \
				   -lm
