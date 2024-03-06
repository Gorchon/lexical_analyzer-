#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

// Forward declarations of DFA functions for checking token types
bool isOperator(const std::string &str);
bool isSymbol(const std::string &str);
bool isNumber(const std::string &str);
bool isIdentifier(const std::string &str);

// Enum for different types of tokens that can be encountered in an arithmetic expression
enum class TokenType
{
    Integer,          // Represents positive integer numbers
    Float,            // Represents positive real numbers
    Variable,         // Represents variable identifiers
    Assignment,       // Represents the assignment operator '='
    Sum,              // Represents the addition operator '+'
    Subtract,         // Represents the subtraction operator '-'
    Product,          // Represents the multiplication operator '*'
    Division,         // Represents the division operator '/'
    LeftParenthesis,  // Represents the left parenthesis '('
    RightParenthesis, // Represents the right parenthesis ')'
    Unknown           // Used to handle any state that does not match the above
};

// Structure for a token, holding its value as a string and its type as a TokenType
struct Token
{
    std::string value;
    TokenType type;
};

// The Lexer class processes the input text and produces tokens
class Lexer
{
private:
    std::vector<Token> tokens;                            // Stores the list of identified tokens
    std::unordered_map<std::string, TokenType> symbolMap; // Map to hold string representations of operators and their corresponding TokenType

public:
    // Constructor to initialize the map with known operators and symbols
    Lexer()
    {
        symbolMap = {
            {"=", TokenType::Assignment},
            {"+", TokenType::Sum},
            {"-", TokenType::Subtract},
            {"*", TokenType::Product},
            {"/", TokenType::Division},
            {"(", TokenType::LeftParenthesis},
            {")", TokenType::RightParenthesis}};
    }

    // Analyzes the input file to tokenize the content
    void analyze(const std::string &filepath)
    {
        std::ifstream file(filepath);
        std::string token;
        char ch;

        if (!file.is_open())
        {
            std::cerr << "Could not open the file: " << filepath << std::endl;
            return;
        }

        // Process the file character by character
        while (file >> std::noskipws >> ch)
        {
            // If whitespace is encountered, finalize the current token
            if (std::isspace(ch))
            {
                if (!token.empty())
                {
                    addToken(token);
                    token.clear();
                }
            }
            // If an operator or symbol is encountered, finalize the current token and process the operator/symbol
            else if (isOperator(std::string(1, ch)) || isSymbol(std::string(1, ch)))
            {
                if (!token.empty())
                {
                    addToken(token);
                    token.clear();
                }
                addToken(std::string(1, ch));
            }
            // Otherwise, accumulate the character into the current token
            else
            {
                token.push_back(ch);
            }
        }

        // Process any remaining token after the end of file is reached
        if (!token.empty())
        {
            addToken(token);
        }

        file.close();
    }

    // Adds a token to the list after determining its type
    void addToken(const std::string &value)
    {
        Token token{value, TokenType::Unknown};

        // Determine the type of the token based on its value
        if (isNumber(value))
        {
            token.type = value.find('.') != std::string::npos ? TokenType::Float : TokenType::Integer;
        }
        else if (isIdentifier(value))
        {
            token.type = TokenType::Variable;
        }
        else if (auto it = symbolMap.find(value); it != symbolMap.end())
        {
            token.type = it->second;
        }

        tokens.push_back(token); // Add the token to the list
    }

    // Prints all the tokens and their types to the console
    void printTokens() const
    {
        for (const auto &token : tokens)
        {
            std::cout << "Token: " << token.value << " Type: ";
            switch (token.type)
            {
            case TokenType::Integer:
                std::cout << "integer";
                break;
            case TokenType::Float:
                std::cout << "float";
                break;
            case TokenType::Variable:
                std::cout << "variable";
                break;
            case TokenType::Assignment:
                std::cout << "assignment";
                break;
            case TokenType::Sum:
                std::cout << "sum";
                break;
            case TokenType::Subtract:
                std::cout << "subtract";
                break;
            case TokenType::Product:
                std::cout << "product";
                break;
            case TokenType::Division:
                std::cout << "division";
                break;
            case TokenType::LeftParenthesis:
                std::cout << "left parenthesis";
                break;
            case TokenType::RightParenthesis:
                std::cout << "right parenthesis";
                break;
            default:
                std::cout << "unknown";
                break;
            }
            std::cout << std::endl;
        }
    }
};

// DFA for identifying operators
bool isOperator(const std::string &str)
{
    int state = 0;

    for (char ch : str)
    {
        switch (state)
        {
        case 0:
            if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=')
                state = 1;
            else
                return false;
            break;
        default:
            return false;
        }
    }

    return state == 1;
}

// DFA for identifying symbols
bool isSymbol(const std::string &str)
{
    int state = 0;

    for (char ch : str)
    {
        switch (state)
        {
        case 0:
            if (ch == '(' || ch == ')')
                state = 1;
            else
                return false;
            break;
        default:
            return false;
        }
    }

    return state == 1;
}

// DFA for identifying numbers
bool isNumber(const std::string &str)
{
    int state = 0;

    for (char ch : str)
    {
        switch (state)
        {
        case 0:
            if (isdigit(ch))
                state = 1;
            else
                return false;
            break;
        case 1:
            if (isdigit(ch))
                state = 1;
            else if (ch == '.')
                state = 2;
            else
                return false;
            break;
        case 2:
            if (isdigit(ch))
                state = 3;
            else
                return false;
            break;
        case 3:
            if (isdigit(ch))
                state = 3;
            else
                return false;
            break;
        default:
            return false;
        }
    }

    // Accepting states are 1 (integer) and 3 (float)
    return state == 1 || state == 3;
}

// DFA for identifying identifiers
bool isIdentifier(const std::string &str)
{
    int state = 0;

    for (char ch : str)
    {
        switch (state)
        {
        case 0:
            // The first character must be a lowercase letter to proceed to state 1.
            if (islower(ch))
                state = 1;
            else
                return false;
            break;
        case 1:
            // Once in state 1, the identifier can contain any combination of lowercase letters and digits.
            if (islower(ch) || isdigit(ch))
                state = 1;
            else
                return false;
            break;
        default:
            return false;
        }
    }

    // The string is accepted as a valid identifier if the DFA is in state 1 after processing all characters.
    return state == 1;
}

// Function signature as required
void lexer(const std::string &filepath)
{
    Lexer lexer;
    lexer.analyze(filepath);
    lexer.printTokens();
}

// Main function for the program
int main()
{
    std::string filepath = "expressions.txt";
    lexer(filepath);
    return 0;
}
