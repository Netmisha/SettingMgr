#pragma once
class Element20
{
public:
    Element20(char const* name, char const* text);
    Element20(char const* name, int const value, int const rx=10);
    Element20(char const* name, double const value, int const precision);
    ~Element20();

    char* const GetName() const;
    char* const GetText() const;

    void        SetName(char const*);                 
    void        SetText(char const*);

protected:
    Element20();
    char* name;
    char* text;
};

