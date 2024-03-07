#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>

enum class TokenType {
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

// We can define our differnt types of states


enum class State {
    Start,
    InInteger,
    InFloat,
    InIdentifier,
    DetectOperator,
    Accept,
    Error
};

struct Token {
    TokenType type;
    std::string value;
};

bool isDigit(char ch) {
    return ch >= '0' && ch <= '9';
}

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool isDecimalPoint(char ch) {
    return ch == '.';
}

// Define a function that maps the current character to a token type, if possible
TokenType charToTokenType(char ch) {
    if (isOperator(ch)) {
        switch (ch) {
            case '+': return TokenType::Sum;
            case '-': return TokenType::Subtract;
            case '*': return TokenType::Product;
            case '/': return TokenType::Division;
        }
    } else if (ch == '=') {
        return TokenType::Assignment;
    } else if (ch == '(') {
        return TokenType::LeftParenthesis;
    } else if (ch == ')') {
        return TokenType::RightParenthesis;
    }
    return TokenType::Unknown;
}

// Example lexer function
std::vector<Token> lexer(const std::string& input) {
    std::vector<Token> tokens;
    State state = State::Start;
    std::string tokenValue = "";
    
    for (char ch : input) {
        switch (state) {
            case State::Start:
                if (isDigit(ch)) {
                    state = State::InInteger;
                    tokenValue += ch;
                } else if (isLetter(ch)) {
                    state = State::InIdentifier;
                    tokenValue += ch;
                } else if (isOperator(ch) || ch == '=' || ch == '(' || ch == ')') {
                    tokens.push_back(Token{charToTokenType(ch), std::string(1, ch)});
                }
                break;
            case State::InInteger:
                if (isDigit(ch)) {
                    tokenValue += ch;
                } else if (isDecimalPoint(ch)) {
                    state = State::InFloat;
                    tokenValue += ch;
                } else {
                    tokens.push_back(Token{TokenType::Integer, tokenValue});
                    tokenValue = "";
                    state = State::Start;
                }
                break;
            case State::InFloat:
                if (isDigit(ch)) {
                    tokenValue += ch;
                } else {
                    tokens.push_back(Token{TokenType::Float, tokenValue});
                    tokenValue = "";
                    state = State::Start;
                }
                break;
            case State::InIdentifier:
                if(isLetter(ch)){
                    tokenValue += ch;

                } else { 
                    tokens.push_back(Token{TokenType::Variable, tokenValue});
                    tokenValue = "";
                    state = State::Start;

                }

            // Add cases for other states as necessary
        }
    }
    
    // Handle the last token if there's any
    if (!tokenValue.empty()) {
        if (state == State::InInteger) {
            tokens.push_back(Token{TokenType::Integer, tokenValue});
        } else if (state == State::InFloat) {
            tokens.push_back(Token{TokenType::Float, tokenValue});
        }
        // Handle other states as necessary
    }
    
    return tokens;
}

int main() {
    std::string input = "b = 3 ";
    std::vector<Token> tokens = lexer(input);
    
    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << " Type: ";
        switch (token.type) {
            case TokenType::Integer:
                std::cout << "Integer";
                break;
            case TokenType::Float:
                std::cout << "Float";
                break;
            case TokenType::Variable:
                std::cout << "Variable";
                break;
            case TokenType::Assignment:
                std::cout << "Assignment";
                break;
            case TokenType::Sum:
                std::cout << "Sum";
                break;
            case TokenType::Subtract:
                std::cout << "Subtract";
                break;
            case TokenType::Product:
                std::cout << "Product";
                break;
            case TokenType::Division:
                std::cout << "Division";
                break;
            case TokenType::LeftParenthesis:
                std::cout << "LeftParenthesis";
                break;
            case TokenType::RightParenthesis:
                std::cout << "RightParenthesis";
                break;
            case TokenType::Unknown: // Fall through
            default:
                std::cout << "Unknown";
        }
        std::cout << std::endl;
    }
}

