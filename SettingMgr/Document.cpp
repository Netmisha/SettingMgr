#include "Document.h"
#include "Element.h"
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <utility>
#include <fstream>
#include <sstream>


//Document

extern void SetStr(char* &dst, char const* src);

Document::Document(char const * str, size_t n):
    name(nullptr),
    elemLen(0),
    elemRes(n)
{
    if(str)
        SetDocName(str);

    pelems = new Element*[n];
}
Document::~Document()
{
    if (name)
        delete[] name;

    for (int i = 0; i < elemLen; ++i)
        delete pelems[i];

    delete[] pelems;
}

char * const Document::GetDocName() const
{
    return name;
}
void Document::SetDocName(char const * newDocName)
{
    SetStr(name, newDocName);
}

void Document::AddElement(Element * el)
{
    if (not el)
        return;

    if (elemLen < elemRes)
    {
        pelems[elemLen++] = el;
    }
    else
    {
        elemRes *= 2;
        Element** newElems = new Element*[elemRes];
        for (int i = 0; i < elemLen; ++i)
            newElems[i] = pelems[i];
        
        delete[] pelems;
        pelems = newElems;

        AddElement(el);
    }
}
void Document::AddElement(char const * elName)
{
    AddElement(new Element(elName));
}
void Document::AddElement(Element const & obj)
{
    AddElement(new Element(obj));
}
void Document::AddElement(Element && obj)
{
    AddElement(new Element(std::move(obj)));
}

Element* Document::GetElement(char const * elName)
{
    for (int i = 0; i < elemLen; ++i)
        if (not std::strcmp(pelems[i]->GetName(), elName))
            return pelems[i];

    return nullptr;
}

void Document::RemoveElement(char const * elName)
{
    for (int i = 0; i < elemLen; ++i)
        if (not std::strcmp(pelems[i]->GetName(), elName))
        {
            delete pelems[i];
            --elemLen;
            pelems[i] = pelems[elemLen];
            //pelems[elemLen] = nullptr;
        }
}

size_t Document::GetElementCout() const
{
    return elemLen;
}

Element** const Document::GetElementPtrs() const
{
    return pelems;
}

void Document::FlushToFile()
{
    std::ofstream file(name, std::ios::out);
    for (int i = 0; i < elemLen; ++i)
    {
        char* ptr = pelems[i]->Represent();
        file << ptr << std::endl;
        delete[] ptr;
    }
    file.close();
}

char * SkipWhiteSpaces(char* ptr)
{
    while (*ptr == ' ')
        ++ptr;
    return ptr;
}

Element* CharPtrToElem(char* ptr)
{
    Element* elem = new Element();
    {
        ptr = SkipWhiteSpaces(ptr);
        // check for <
        if (*ptr == '<')
            ++ptr;
        else
            return nullptr; // bad format -> u lose

        ptr = SkipWhiteSpaces(ptr);

        // scheck for </
        bool hasText = true;
        if (*ptr == '/')
        {
            // if found means we have no text
            // wouldnt even check
            hasText = false;
            ++ptr;
            ptr = SkipWhiteSpaces(ptr);
        }

        // read tag name
        char namebuf[128];
        sscanf(ptr, "%[^ >]s", namebuf);
        elem->SetName(namebuf);
        ptr += std::strlen(namebuf);

        ptr = SkipWhiteSpaces(ptr);

        // until close tag
        if (*ptr != '>') {

            ptr = SkipWhiteSpaces(ptr);

            // find properties
            while (true)
            {
                char* eq = std::strstr(ptr, "=");
                char* ct = std::strstr(ptr, ">");

                // while there is = with index lesser than <
                if ((not eq) or eq > ct)
                    break; // couldda put it in statement but woullda be uglier

                // read key
                char keybuf[128];
                sscanf(ptr, "%[^ =]s", keybuf);
                ptr += std::strlen(keybuf) + 1;

                // skip ws, = and \"
                while (*ptr == ' ' or *ptr == '=' or *ptr == '\"')
                    ++ptr;

                // read val
                char valbuf[128];
                sscanf(ptr, "%[^ \">]s", valbuf);
                ptr += std::strlen(valbuf) + 1;

                ptr = SkipWhiteSpaces(ptr);

                elem->SetProperty(keybuf, valbuf);
            }

            //ptr = SkipWhiteSpaces(ptr);
        }
        // skip close tag
        ++ptr;

      // get text
        // check if text area not empty
        if (*ptr == '<')
            hasText = false;

        if (hasText)
        {
            char textbuf[1024];
            sscanf(ptr, "%[^<]s", textbuf);
            elem->SetText(textbuf);
        }


    }
    return elem;
}


void Document::ReadFromFile()
{
    std::ifstream file(name, std::ios::in);
    char buff[1024];
    while (not file.eof())
    {
        file.getline(buff, _countof(buff));

        AddElement(CharPtrToElem(buff));
    }
    file.close();
}