#pragma once

class Element
{
public:
    Element();
    ~Element();

    void SetName(char const*);

    void SetProperty(char const* propName, char const* propVal);
    void SetProperty(char const* propName, int propVal);
    void SetProperty(char const* propName, double propVal);

    void RemoveProperty(char const* propName);

    char* Represent() const;
protected:
    char* name;
    char* value;

    char** prpK;
    char** prpV;
    size_t prpLen;
    size_t prpRes;
};

