PROGRAM		= vsopc
CXX	 		= clang++

BUILDDIR	= build/
SOURCEDIR	= vsopcompiler/
MAINDIR 	= $(SOURCEDIR)main/
ASTDIR		= $(SOURCEDIR)astTree/
LEXERDIR	= $(SOURCEDIR)lexer/
PARSERDIR	= $(SOURCEDIR)parser/
VISITORDIR	= $(SOURCEDIR)visitors/
TEMPLDIR	= $(SOURCEDIR)templates/


VISITORS	= $(BUILDDIR)dumpASTVisitor.o $(BUILDDIR)augmentASTVisitor.o $(BUILDDIR)codeGeneratorVisitor.o
OBJECTS		= $(BUILDDIR)main.o $(BUILDDIR)lexer.o $(BUILDDIR)parser.o $(BUILDDIR)nodes.o $(VISITORS)
TEMPLATES 	= $(TEMPLDIR)inheritanceTree.hpp $(TEMPLDIR)info.hpp $(TEMPLDIR)tableTree.hpp

CXXFLAGS	= -fvisibility=hidden -I $(SOURCEDIR) -g -Wall -Wextra -Werror -Wpedantic -pedantic
STANDARD	= -std=c++17


vsopc: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(PROGRAM) $(OBJECTS) $(STANDARD)

# Main, visitors and nodes
$(BUILDDIR)main.o: $(MAINDIR)main.cpp $(PARSERDIR)parser.hpp $(LEXERDIR)lexer.hpp $(VISITORDIR)*.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(STANDARD)

$(BUILDDIR)%Visitor.o: $(VISITORDIR)%Visitor.cpp $(VISITORDIR)%Visitor.hpp $(VISITORDIR)visitor.hpp $(VISITORDIR)objectll.h $(ASTDIR)nodes.hpp $(PARSERDIR)parser.hpp $(TEMPLATES)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(STANDARD)

$(BUILDDIR)nodes.o: $(ASTDIR)nodes.cpp $(ASTDIR)nodes.hpp $(PARSERDIR)parser.hpp $(TEMPLATES)
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(STANDARD)

# Lexer and parser
$(BUILDDIR)lexer.o: $(LEXERDIR)lexer.cpp $(PARSERDIR)parser.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(STANDARD)

$(BUILDDIR)parser.o: $(PARSERDIR)parser.cpp $(PARSERDIR)parser.hpp
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(STANDARD)

$(LEXERDIR)lexer.cpp: $(LEXERDIR)lexer.lex $(PARSERDIR)parser.cpp
	flex -o $@ $<

$(PARSERDIR)parser.cpp $(PARSERDIR)parser.hpp: $(PARSERDIR)parser.y
	bison --output=$(PARSERDIR)parser.cpp --defines=$(PARSERDIR)parser.hpp $<

# Nothing to do
*.hpp:

*.hpp:

*.h:

clean:
	rm -f vsopc
	rm -f build/*.o
	rm -f $(LEXERDIR)lexer.cpp
	rm -f $(PARSERDIR)parser.cpp
	rm -f $(PARSERDIR)parser.hpp


install-tools:

# Doc generation
doc:
	@make -s clean
	$ doxygen docs
	$ firefox html/index.html

cleandoc:
	rm -rf html/
	rm -rf latex/

archive:
	@make -s clean
	@rm -rf temp vsopcompiler.tar.xz
	@mkdir temp && mkdir temp/vsopcompiler
	@cp -r Makefile report.pdf vsopcompiler docker-compose.yml docs mainpage.hpp build .clang-format temp/vsopcompiler
	@tar -C temp/ -cJf temp/vsopcompiler.tar.xz vsopcompiler
	@mv temp/vsopcompiler.tar.xz vsopcompiler.tar.xz
	@rm -rf temp