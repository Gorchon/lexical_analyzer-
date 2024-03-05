#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
#include <ctype.h>

using namespace std;

// Token types
enum class TokenType
{
    Integer,
    Float,
    Variable,
    Assignment,
    Sum,
    Subtract,
    Product,
    Division,
    LeftParenthesis,
    RightParenthesis,
    Unknown
};

// Convert TokenType to string for output
string tokenTypeToString(TokenType type)
{
    switch (type)
    {
    case TokenType::Integer:
        return "integer";
    case TokenType::Float:
        return "float";
    case TokenType::Variable:
        return "variable";
    case TokenType::Assignment:
        return "assignment";
    case TokenType::Sum:
        return "sum";
    case TokenType::Subtract:
        return "subtract";
    case TokenType::Product:
        return "product";
    case TokenType::Division:
        return "division";
    case TokenType::LeftParenthesis:
        return "left parenthesis";
    case TokenType::RightParenthesis:
        return "right parenthesis";
    default:
        return "unknown";
    }
}

// Token structure
struct Token
{
    string value;
    TokenType type;

    Token(string val, TokenType typ) : value(val), type(typ) {}
};

// Lexer class
class Lexer
{
private:
    vector<Token> tokens;
    unordered_map<char, TokenType> tokenMap;

public:
    Lexer()
    {
        // Initialize the token map with single-character tokens
        tokenMap['='] = TokenType::Assignment;
        tokenMap['+'] = TokenType::Sum;
        tokenMap['-'] = TokenType::Subtract;
        tokenMap['*'] = TokenType::Product;
        tokenMap['/'] = TokenType::Division;
        tokenMap['('] = TokenType::LeftParenthesis;
        tokenMap[')'] = TokenType::RightParenthesis;
    }

    void analyze(const string &filepath)
    {
        ifstream file(filepath);
        if (!file.is_open())
        {
            cerr << "Failed to open file: " << filepath << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            // Tokenization logic goes here
            // Simplified for demonstration; real implementation would involve more detailed parsing and state management
        }
        file.close();
    }

    // Function to print tokens
    void printTokens() const
    {
        cout << "Token\t\tType\n";
        for (const auto &token : tokens)
        {
            cout << token.value << "\t\t" << tokenTypeToString(token.type) << "\n";
        }
    }
};

void lexer(string filepath)
{
    Lexer lexer;
    lexer.analyze(filepath);
    lexer.printTokens();
}

int main()
{
    string filepath = "expressions.txt";
    lexer(filepath);
    cout << "U r done!";
    return 0;
}
