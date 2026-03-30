#include "lexer.h"

// Helper to avoid repetition
static void pushNewToken(std::vector<Token>& tokens) {
    // Only push a new token if the current one isn't empty
    if (!tokens.back().value.empty()) {
        tokens.emplace_back();
    }
}

LexedFile lexFile(const std::string& fileContents) {
    std::vector<Token> lexedFile = {Token()};
    bool isComment = false;
    bool inString  = false;
    bool inChar    = false;

    for (const char c : fileContents) {
        switch (c) {
            case '"':
                if (!isComment) {
                    if (inChar) {
                        lexedFile.back().value.push_back(c);
                    } else {
                        inString = !inString;
                        lexedFile.back().value.push_back(c);
                        if (!inString) pushNewToken(lexedFile); // closing quote = end of string token
                    }
                }
                break;
            case '\'':
                if (!isComment) {
                    if (inString) {
                        lexedFile.back().value.push_back(c);
                    } else {
                        inChar = !inChar;
                        lexedFile.back().value.push_back(c);
                        if (!inChar) pushNewToken(lexedFile); // closing quote = end of char token
                    }
                }
                break;
            case ' ':
            case '\t':
                if (inString || inChar) {
                    lexedFile.back().value.push_back(c);
                } else {
                    pushNewToken(lexedFile); // whitespace = token boundary
                }
                break;
            case '\n':
                if (inString || inChar) {
                    lexedFile.back().value.push_back(c);
                } else {
                    pushNewToken(lexedFile); // newline = token boundary
                    isComment = false;
                }
                break;
            case '#':
                if (inString || inChar) {
                    lexedFile.back().value.push_back(c);
                } else if (!isComment) {
                    isComment = true;
                }
                break;
            default:
                if (!isComment) {
                    lexedFile.back().value.push_back(c);
                }
                break;
        }
    }

    // Remove trailing empty token if present
    if (!lexedFile.empty() && lexedFile.back().value.empty()) {
        lexedFile.pop_back();
    }
    return LexedFile(std::move(lexedFile));
}