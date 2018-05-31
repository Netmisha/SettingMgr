#include "Element20.h"
#include "Logger.h"

#include <cstring>
#include <cstdlib>
#include <cstdio>

Element20::Element20(char const * n, char const * t):
    Element20()
{
    SetName(n);
    SetText(t);

    Log(name);
    Log(text);
    Log("</ele-created>");
}
Element20::Element20(char const * n, int const v, int const r) :
    Element20()
{
    char buff[32];
    _itoa_s(v, buff, _countof(buff), r);
    SetName(n);
    SetText(buff);

    Log(name);
    Log(text);
    Log("</ele-created>");
}
Element20::Element20(char const * n, double const v, int const p):
    Element20()
{
    char buff[32];
    char format[32];
    std::sprintf(format, "%%.%if", p);
    std::sprintf(buff, format, v);
    SetName(n);
    SetText(buff);

    Log(name);
    Log(text);
    Log("</ele-created>");
}
Element20::Element20() :
    name(nullptr),
    text(nullptr)
{
    Log("<ele-created>");
}
Element20::~Element20()
{
    Log("<ele-clean-up>");
    Log(name);
    Log(text);

    delete[] name;
    delete[] text;

    Log("</ele-clean-up>");
}

char*const Element20::GetName() const
{
    return const_cast<char*const> (name);
}
char*const Element20::GetText() const
{
    return const_cast<char*const> (text);
}

void Element20::SetName(char const* n)
{
    if(name)
        delete[] name;
    name = new char[std::strlen(n) + 1];
    std::strcpy(name, n);
}
void Element20::SetText(char const* t)
{
    if (text)
        delete[] text;
    text = new char[std::strlen(t) + 1];
    std::strcpy(text, t);
}