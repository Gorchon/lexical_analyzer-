#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <unordered_map>

// Enumeration for the different types of tokens.
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

// Token structure to hold the value and type.
struct Token
{
    std::string value;
    TokenType type;
};

// Convert TokenType to a string for easier output.
std::string tokenTypeToString(TokenType type)
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

// Helper functions to identify character types.
bool isOperator(char ch)
{
    return std::string("+-*/=").find(ch) != std::string::npos;
}

bool isSymbol(char ch)
{
    return std::string("()").find(ch) != std::string::npos;
}

bool isIdentifierStart(char ch)
{
    return std::islower(ch);
}

// The main lexer function.
void lexer(const std::string &filepath)
{
    std::ifstream file(filepath);
    if (!file)
    {
        std::cerr << "Could not open the file: " << filepath << std::endl;
        return;
    }

    std::vector<Token> tokens;
    std::string token;
    char ch;
    while (file.get(ch))
    {
        // Skip whitespaces.
        if (std::isspace(ch))
        {
            continue;
        }
        // Handle operators.
        if (isOperator(ch))
        {
            tokens.push_back({std::string(1, ch), TokenType::Unknown}); // Unknown for now, will determine later.
            continue;
        }
        // Handle symbols.
        if (isSymbol(ch))
        {
            tokens.push_back({std::string(1, ch), TokenType::Unknown}); // Unknown for now, will determine later.
            continue;
        }
        // Handle identifiers (variables).
        if (isIdentifierStart(ch))
        {
            token += ch;
            while (file.peek() != EOF && std::islower(file.peek()))
            {
                file.get(ch);
                token += ch;
            }
            tokens.push_back({token, TokenType::Variable});
            token.clear();
            continue;
        }
        // Handle numbers (integers and floats).
        if (std::isdigit(ch))
        {
            token += ch;
            bool isFloat = false;
            while (file.peek() != EOF && (std::isdigit(file.peek()) || (!isFloat && file.peek() == '.')))
            {
                file.get(ch);
                if (ch == '.')
                {
                    isFloat = true;
                }
                token += ch;
            }
            tokens.push_back({token, isFloat ? TokenType::Float : TokenType::Integer});
            token.clear();
            continue;
        }
    }

    // Now determine the type of operators and symbols.
    for (auto &tk : tokens)
    {
        if (tk.type == TokenType::Unknown)
        {
            if (tk.value == "=")
                tk.type = TokenType::Assignment;
            else if (tk.value == "+")
                tk.type = TokenType::Sum;
            else if (tk.value == "-")
                tk.type = TokenType::Subtract;
            else if (tk.value == "*")
                tk.type = TokenType::Product;
            else if (tk.value == "/")
                tk.type = TokenType::Division;
            else if (tk.value == "(")
                tk.type = TokenType::LeftParenthesis;
            else if (tk.value == ")")
                tk.type = TokenType::RightParenthesis;
        }
    }

    // Print out the tokens.
    for (const auto &tk : tokens)
    {
        std::cout << "Token: " << tk.value << "  Type: " << tokenTypeToString(tk.type) << "\n";
    }
}

// The main function for the program.
int main()
{
    // Replace "expressions.txt" with the actual path to the input file.
    lexer("expressions.txt");
    return 0;
}
