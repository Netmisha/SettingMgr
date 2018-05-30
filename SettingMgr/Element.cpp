#include "Element.h"

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstdio>

Element::Element(char * name, char * text, size_t propReserve):
    prpLen(0),
    prpRes(propReserve)
{
    if (name)
        SetName(name);
    else
        this->name = nullptr;

    if (text)
        SetText(text);
    else
        this->text = nullptr;

    prpK = new char*[prpRes];
    prpV = new char*[prpRes];
}

Element::~Element()
{
    if (name)
        delete[] name;
    if (text)
        delete[] text;

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
    this->name = new char[std::strlen(name) + 1];
    std::strcpy(this->name, name);
}

char*const Element::GetName() const
{
    return const_cast<char*const>(name);
}

void Element::SetText(char const * val)
{
    this->text = new char[std::strlen(val) + 1];
    std::strcpy(text, val);
}

char * const Element::GetText() const
{
    return const_cast<char*const>(text);
}

size_t Element::GetPropertyCount() const
{
    return prpLen;
}

char** const Element::GetPropertyKeys() const
{
    return const_cast<char**const>(prpK);
}

char** const Element::GetPropertyVals() const
{
    return const_cast<char**const>(prpV);
}

void Element::SetProperty(char const* key, char const* val)
{
    if (prpLen < prpRes)
    {
        // if find change and return
        for (int i = 0; i < prpLen; ++i)
        {
            if (std::strcmp(prpK[i], key) == 0)
            {
                if (std::strlen(prpV[i]) < std::strlen(val))
                {
                    delete[] prpV[i];
                    prpV[i] = new char[std::strlen(val) + 1];
                }
                std::strcpy(prpV[i], val);
                return;
            }
        }
        //else append
        prpK[prpLen] = new char[std::strlen(key) + 1];
        std::strcpy(prpK[prpLen], key);
        prpV[prpLen] = new char[std::strlen(val) + 1];
        std::strcpy(prpV[prpLen], val);

        ++prpLen;
    }
    else
    {
        prpRes *= 2;

        char** newK = new char* [prpRes];
        char** newV = new char* [prpRes];
        for (int i = 0; i < prpLen; ++i)
        {
            newK[i] = prpK[i];
            newV[i] = prpV[i];
        }
        delete[] prpK;
        delete[] prpV;

        prpK = newK;
        prpV = newV;

        SetProperty(key, val);
    }
}

void Element::SetProperty(char const * k, int v, int rx)
{
    char vcstr[_CVTBUFSIZE];
    _itoa_s(v, vcstr, _countof(vcstr), rx);
    SetProperty(k, vcstr);
}
void Element::SetProperty(char const * k, double v, int dc)
{
    char vcstr[_CVTBUFSIZE];
    _gcvt_s(vcstr, _countof(vcstr), v, dc);
    SetProperty(k, vcstr);
}

void Element::RemoveProperty(char const * k)
{
    for (int i = 0; i < prpLen; ++i)
    {
        if (not std::strcmp(prpK[i], k))
        {
            delete[] prpK[i];
            delete[] prpV[i];

            --prpLen;

            prpK[i] = prpK[prpLen];
            prpV[i] = prpV[prpLen];

            prpK[prpLen] = nullptr;
            prpV[prpLen] = nullptr;

            return;
        }
    }
}

char * Element::Represent() const
{
    return Represent("", " ");
}

char* Element::Represent(char const* td, char const* pd) const
{
    char* repr = new char[1024];
    char  buff[128];
    {
        std::strcpy(repr, "");
        
        // cat <tagname
        std::sprintf(buff, (text ? "<%s" : "</%s"), name);
        std::strcat(repr, buff);

        // cat prpkey="prpval"...
        for (int i = 0; i < prpLen; ++i)
        {
            std::sprintf(buff, "%s%s=\"%s\"", pd, prpK[i], prpV[i]);
            std::strcat(repr, buff);
        }
        
        // cat >text</name> if there is text
        std::strcat(repr, ">");
        if (text)
        {
            std::sprintf(buff, "%s%s%s", td, text, td);
            std::strcat(repr, buff);

            std::sprintf(buff, "</%s>", name);
            std::strcat(repr, buff);
        }
    }
    return repr;
}
