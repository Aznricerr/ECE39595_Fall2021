EXECUTABLE = ZorkProject
CC = g++
CFLAGS = -g -std=c++11 -Wall -Werror -DTIXML_USE_STL
COMMAND_FILE_FLAGS = $(CFLAGS) -DCOMMAND_FILE_DEBUG
XML_CLASSES = tinystr.cpp tinyxml.cpp XMLParser.cpp
CLASSES = Border.cpp Condition.cpp ConditionalExecutable.cpp Container.cpp Creature.cpp DungeonElement.cpp DungeonElementHolder.cpp Item.cpp Map.cpp Room.cpp Trigger.cpp Player.cpp
SOURCES = main.cpp $(XML_CLASSES) $(CLASSES) tinyxmlerror.cpp tinyxmlparser.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(CLASSES:.cpp=.h)
XMLHEADERS = $(XML_CLASSES:.cpp=.h)

PROJECT_FILES = Makefile README.txt Readme.pdf
ZIPNAME = $(EXECUTABLE).zip
ZIPFILES = $(SOURCES) $(HEADERS) $(XMLHEADERS) $(PROJECT_FILES) sample_xml/*

run: $(EXECUTABLE)
	./$(EXECUTABLE)

rebuild: clean $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(HEADERS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

.cpp.o: $(HEADERS)
	$(CC) $(CFLAGS) -c $<

run_command_file: build_command_file
	./$(EXECUTABLE)

rebuild_command_file: clean build_command_file

build_command_file: $(HEADERS)
	$(CC) $(COMMAND_FILE_FLAGS) -o $(EXECUTABLE) $(SOURCES)

clean:
	$(RM) *.o
	$(RM) $(EXECUTABLE)
	$(RM) $(EXECUTABLE).exe
	$(RM) $(ZIPNAME)

zip: $(ZIPFILES)
	zip $(ZIPNAME) $(ZIPFILES)

.PHONY: run clean rebuild
