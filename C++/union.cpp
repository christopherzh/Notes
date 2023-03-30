#include <iostream>
#include <string>

using namespace std;
class Token
{
    friend ostream &operator<<(ostream &os, const Token &token);

public:
    Token() : tok(INT), ival{0} {};
    ~Token()
    {
        if (tok == STRING)
            sval.~string();
    };

    Token(const Token &token) : tok(token.tok) { copyUnion(token); };
    Token &operator=(const Token &token);

    Token(Token &&token) noexcept : tok(token.tok)
    {
        cout << "移动拷贝函数" << endl;
        copyUnion(token);
    };
    Token &operator=(Token &&token) noexcept;

    Token &operator=(const std::string &);
    Token &operator=(char);
    Token &operator=(int);
    Token &operator=(double);

private:
    enum
    {
        INT,
        CHAR,
        DOUBLE,
        STRING
    } tok;
    union
    {
        char cval;
        int ival;
        double dval;
        string sval;
    };

    void copyUnion(const Token &token);
    void copyUnion(Token &&token);
};

ostream &operator<<(ostream &os, const Token &token)
{
    switch (token.tok)
    {
    case Token::INT:
        return os << token.ival;
    case Token::CHAR:
        return os << token.cval;
    case Token::DOUBLE:
        return os << token.dval;
    case Token::STRING:
        return os << token.sval;
    }
    return os;
}
void Token::copyUnion(const Token &token)
{
    switch (token.tok)
    {
    case INT:
        ival = token.ival;
        break;
    case CHAR:
        cval = token.cval;
        break;
    case DOUBLE:
        dval = token.dval;
        break;
    case STRING:
        new (&sval) string(token.sval);
        break;
    }
}

Token &Token::operator=(const Token &token)
{
    if (tok == STRING && token.tok != STRING)
    {
        sval.~string();
    }
    if (tok == STRING && token.tok == STRING)
    { // 都为string，直接调用容器的赋值
        sval = token.sval;
    }
    else
    {
        copyUnion(token);
    }
    tok = token.tok;
    return *this;
}

Token &Token::operator=(Token &&token) noexcept
{
    cout << "移动赋值函数" << endl;
    if (this != &token)
    {
        tok = token.tok;
        copyUnion(token);
    }
    return *this;
}

void Token::copyUnion(Token &&token)
{
    switch (token.tok)
    {
    case INT:
        ival = token.ival;
        token.ival = 0;
        break;
    case CHAR:
        cval = token.cval;
        token.cval = 0;
        break;
    case DOUBLE:
        dval = token.dval;
        token.dval = 0.0;
        break;
    case STRING:
        sval = token.sval;
        token.sval = "";
        break;
    }
}

inline Token &Token::operator=(char c)
{
    if (tok == STRING)
        sval.~string();
    cval = c;
    tok = CHAR;
    return *this;
}

inline Token &Token::operator=(int i)
{
    if (tok == STRING)
        sval.~string();
    ival = i;
    tok = INT;
    return *this;
}

inline Token &Token::operator=(const std::string &s)
{
    if (tok == STRING)
        sval = s;
    else
        new (&sval) std::string(s);
    tok = STRING;
    return *this;
}

inline Token &Token::operator=(double d)
{
    if (tok == STRING)
        sval.~string();
    dval = d;
    tok = DOUBLE;
    return *this;
}
int main()
{
    Token token;
    Token t2;
    Token t3;
    cout << t2 << " " << t3 << endl;
    t2 = string("hi mom!");
    t3 = "good bye";
    token = t2;
    token = "boo";
    cout << token << endl;
    t2 = t3;
    cout << t2 << endl;

    token = 42;
    cout << token << endl;

    Token t4(std::move(t2));
    cout << t4 << endl;

    t3 = 12.12;
    t4 = std::move(t3);
    cout << t4 << endl;
}