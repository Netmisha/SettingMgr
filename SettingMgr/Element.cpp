#include "Element.h"

#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cstdio>

Element::Element(char const* name, char const* text, size_t propReserve):
    name(nullptr),
    text(nullptr),
    prpLen(0),
    prpRes(propReserve)
{
    if (name)
        SetName(name);

    if (text)
        SetText(text);

    prpK = new char*[prpRes];
    prpV = new char*[prpRes];
}

Element::Element(Element const & obj):
    Element(obj.name, obj.text, obj.prpRes)
{
    for (int i = 0; i < obj.prpLen; ++i)
    {
        SetProperty(obj.prpK[i], obj.prpV[i]);
    }
}

Element::Element(Element&& src):
    name(src.name),
    text(src.text),
    prpK(src.prpK),
    prpV(src.prpV),
    prpLen(src.prpLen),
    prpRes(src.prpRes)
{
    src.name = nullptr;
    src.text = nullptr;
    src.prpK = new char*[prpRes];
    src.prpV = new char*[prpRes];
    src.prpLen = 0;
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

void SetStr(char* &dst, char const* src) 
{
    size_t srcLen = std::strlen(src);
    
    bool realloc = false;
    {
        if (not dst)
            realloc = true;
        else
            if (std::strlen(dst) < srcLen)
            {
                delete[] dst;
                realloc = true;
            }
    }
    if (realloc)
        dst = new char[srcLen + 1];

    std::strcpy(dst, src);
}

void Element::SetName(char const* str)
{
    SetStr(name, str);
}

char*const Element::GetName() const
{
    return name;
}

void Element::SetText(char const * val)
{
    SetStr(text, val);
}

char*const Element::GetText() const
{
    return text;
}

size_t Element::GetPropertyCount() const
{
    return prpLen;
}

char** const Element::GetPropertyKeys() const
{
    return prpK;
}

char** const Element::GetPropertyVals() const
{
    return prpV;
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
                SetStr(prpV[i], val);
                return;
            }
        }
        //else append
        prpK[prpLen] = nullptr;
        prpV[prpLen] = nullptr;
        SetStr(prpK[prpLen], key);
        SetStr(prpV[prpLen], val);

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
