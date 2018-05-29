#include "Element.h"

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cassert>

Element::Element():
    name(nullptr),
    value(nullptr),
    prpLen(0),
    prpRes(16)
{
    prpK = new char*[prpRes];
    prpV = new char*[prpRes];
}

Element::~Element()
{
    if (name)
        delete[] name;
    if (value)
        delete[] value;

    for (int i = 0; i < prpLen; ++i)
    {
        delete[] prpK[i];
        delete[] prpV[i];
    }
    delete[] prpK;
    delete[] prpV;
}

void Element::SetName(char const* name)
{
    assert(name != nullptr);

    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
}

void Element::SetProperty(char const* propKey, char const* propVal)
//  if len < reserve
//      if
//  else
//      reserve some more
//      copy
//      find and modify or append
{
    if (prpLen < prpRes)
    {
        for (int i = 0; i < prpLen; ++i)
        {
            // if found
                // change and return
        }

        //else append
    }
    else
    {
        prpRes *= 2;
        char** newK = new char*[prpRes];
        char** newV = new char*[prpRes];
        for (int i = 0; i < prpLen; ++i)
        {
            newK[i] = prpK[i];
            newV[i] = prpV[i];
        }
        delete[] prpK;
        delete[] prpV;

        prpK = newK;
        prpV = newV;

        SetProperty(propKey, propVal);
    }
}
