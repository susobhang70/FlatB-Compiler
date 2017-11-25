# Flat-B Compiler FrontEnd
Parser, Scanner, AST Generator, Interpreter and LLVM IR Generator for FlatB Language

## Compile
- `$ cd src`
- `$ make`
- `$ make clean` - To clean up all compiled files

## Run
- `$ ./src/bcc file.b`
- If you need Interpreter support, uncomment `//ASTInterpreter itpr(v.getSymbolTable()); //itpr.visit(start);` in `./src/parser.y` (Line 344-345).

## Output
- The LLVM IR is saved a new file with extension ll, in the directory where the file exists. Eg: `file.b.ll`.
- One can use this generated .ll file with lli - `lli file.b.ll` to execute the code.
- One can also use llc on the .ll file - `llc -filetype=asm -relocation-model=pic file.b.ll` and get `file.b.s`, followed by clang compilation using `clang++ -fPIC file.b.s -o file.out`, and then run it using `./file.out`. 
- Output of the parser, scanner, interpreter and also the LLVM IR is shown on the terminal.
- The AST pass is saved to `./src/AST_XML.xml`

## Files and Structure
- `compiler-design.pdf` - Contains detailed specification of FlatB language, design principles deployed in this compiler frontend, and the performance statistics of the generated code (LLVM IR with llc vs LLVM IR with lli vs Interpreter)
- `test-units/`- Folder containing unit tests. FlatB files have extension .b
- `src/scanner.l` - Implementation of scanner. Uses Flex.
- `src/parser.y` - Implementation of parser. Uses Bison.
- `src/ASTDefinition.h` - Contains headers for ASTGenerator, Interpreter and LLVM IR Generator
- `src/ASTDefition.cpp` - Implementation of ASTGenerator, and Interpreter.
- `src/CodeGen.cpp` - Implementation of LLVM IR Generator.
