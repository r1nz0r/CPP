#include <cstring>
#include <iostream>

class Mystring
{
    friend bool operator==(const Mystring& lhs, const Mystring& rhs);
    friend bool operator!=(const Mystring& lhs, const Mystring& rhs);
    friend bool operator>(const Mystring& lhs, const Mystring& rhs);
    friend bool operator<(const Mystring& lhs, const Mystring& rhs);
    
    friend Mystring operator+(const Mystring& lhs, const Mystring& rhs);
    friend Mystring& operator+=(Mystring& lhs, const Mystring& rhs);
    friend Mystring operator-(const Mystring& lhs);
private:
    char* str;
    void AllocateWithCopy(const char*);
    void AssignWithMove(char*);
public:
    Mystring();
    Mystring(const char*);
    Mystring(const Mystring&);
    Mystring(Mystring&&) noexcept;
    ~Mystring();

    size_t GetLength() const;
    const char* GetStr() const;
    void Display() const;

    Mystring& operator=(const Mystring&);
    Mystring& operator=(Mystring&&) noexcept;
};

void Mystring::AllocateWithCopy(const char* other)
{
    const size_t size = std::strlen(other) + 1;
    str = new char[size];
    strcpy_s(str, size, other);
}

void Mystring::AssignWithMove(char* other)
{
    str = other;
    other = nullptr;
}

Mystring::Mystring() : str{nullptr}
{
    str = new char[1];
    *str = '\0';
}

Mystring::Mystring(const char* other) : str{nullptr}
{
    if (other == nullptr)    
        Mystring();    
    else    
        AllocateWithCopy(other);    
}

Mystring::Mystring(const Mystring& other) : str{nullptr}
{
    AllocateWithCopy(other.str);
}

Mystring::Mystring(Mystring&& other) noexcept : str{nullptr}
{
    AssignWithMove(other.str);
}

Mystring::~Mystring()
{
    delete[] str;
}

size_t Mystring::GetLength() const
{
    return std::strlen(str);
}

const char* Mystring::GetStr() const
{
    return str;
}

void Mystring::Display() const
{
    std::cout << str << " : " << GetLength() << std::endl;
}

Mystring& Mystring::operator=(const Mystring& rhs)
{
    if (this == &rhs)
        return *this;
    
    delete[] str;
    AllocateWithCopy(rhs.str);    
    return *this;
}

Mystring& Mystring::operator=(Mystring&& rhs) noexcept
{
    if (this == &rhs)
        return *this;

    delete[] str;
    AssignWithMove(rhs.str);
    return *this;
}


bool operator==(const Mystring& lhs, const Mystring& rhs)
{
    if (std::strcmp(lhs.str, rhs.str) == 0)
        return true;

    return false;
}

bool operator!=(const Mystring& lhs, const Mystring& rhs)
{
    return !(std::strcmp(lhs.str, rhs.str) == 0);
}

bool operator>(const Mystring& lhs, const Mystring& rhs)
{
    if (std::strcmp(lhs.str, rhs.str) > 0)
        return true;

    return false;
}

bool operator<(const Mystring& lhs, const Mystring& rhs)
{
    if (std::strcmp(lhs.str, rhs.str) < 0)
        return true;

    return false;
}

Mystring operator+(const Mystring& lhs, const Mystring& rhs)
{
    const size_t newLength = std::strlen(lhs.str) + std::strlen(rhs.str) + 1;
    char* buffer = new char[newLength];
    strcpy_s(buffer, newLength, lhs.str);
    strcat_s(buffer, newLength, rhs.str);

    Mystring temp {buffer};
    delete[] buffer;
    return temp;
}

Mystring& operator+=(Mystring& lhs, const Mystring& rhs)
{
    lhs = lhs + rhs;
    return lhs;
}

Mystring operator-(const Mystring& lhs)
{
    size_t newSize = std::strlen(lhs.str) + 1;
    char* buffer = new char[newSize];
    strcpy_s(buffer, newSize, lhs.str);
    
    for (size_t i = 0; i < std::strlen(buffer); ++i)
        buffer[i] = tolower(buffer[i]);

    Mystring temp {buffer};
    delete[] buffer;
    return temp;
}

int main(int argc, char* argv[])
{
    Mystring a {"AAA"};
    a.Display();
    
    Mystring b{"Hello"};
    b.Display();
    
    b.operator=(a);
    b.Display();
    
    a = "Hello World!";
    b = -b;
    a += b;
    a.Display();
    
    b = Mystring("Bye");
    b.Display();    
}
