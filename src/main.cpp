#include <fstream>
#include <sstream>
#include "lexer.h"

int main() {
    std::ifstream in("../tests/test.flnt");
    if (!in.is_open()) {
        printf("ERROR: could not open input file\n");
        return 1;
    }
    printf("Loaded file\n");

    // Read entire file contents into a string
    std::ostringstream ss;
    ss << in.rdbuf();
    std::string input = ss.str();

    printf("File contents (%zu bytes):\n%s\n", input.size(), input.c_str());

    std::ofstream out("test_output.txt");
    if (!out.is_open()) {
        printf("ERROR: could not open output file\n");
        return 1;
    }
    printf("Writing to file\n");

    LexedFile output = lexFile(input);
    for (const Token& token : output.tokens) {
        out << token.value << '\n';
        printf("Wrote token: %s\n", token.value.c_str());
    }

    printf("Done. %zu tokens written.\n", output.tokens.size());
}