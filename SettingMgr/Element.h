#pragma once

class Element
{
public:
    Element(char const* elemName = nullptr, char const* elemText = nullptr, size_t propReserve = 16);
    Element(Element const&);
    Element(Element &&);
    ~Element();

    void        SetName(char const* elemName);
    char* const GetName() const;
    void        SetText(char const* elemValue);
    char* const GetText() const;

    size_t      GetPropertyCount() const;
    char**const GetPropertyKeys() const;
    char**const GetPropertyVals() const;

    void        SetProperty(char const* propertyKey, char const* properyValue);
    void        SetProperty(char const* propertyKey, int properyValue, int radix = 10);
    void        SetProperty(char const* propertyKey, double properyValue, int digitCount = 5);

    void        RemoveProperty(char const* propertyKey);

    char*       Represent() const;
    char*       Represent(char const* txtDelim, char const* prpDelim) const;
protected:
    char* name;
    char* text;

    char** prpK;
    char** prpV;
    size_t prpLen;
    size_t prpRes;
};

