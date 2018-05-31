#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <cstdio>
#include <cstdlib>

#include "Document20.h"
#include "List20.h"
#include "Element20.h"
#include "Logger.h"

constexpr size_t smallBuffSize = 256;
constexpr size_t largeBuffSize = 1024;

Document20::Document20(char const* p, char const* r, char const* n, char const* d):
    path(new char[std::strlen(p) + 1]),
    root(new char[std::strlen(r) + 1]),
    node(new char[std::strlen(n) + 1]),
    decl(new char[std::strlen(d) + 1]),
    list(new List20())
{
    std::strcpy(path, p);
    std::strcpy(root, r);
    std::strcpy(node, n);
    std::strcpy(decl, d);

    Log("</doc-created>");
}

List20 & Document20::GetList()
{
    return *list;
}

void Document20::RetreiveFileData()
{
    Log("<doc-read>");

    std::FILE* file = std::fopen(path, "r");
    
    char buff[largeBuffSize];

    if (file)
    {
        Log("file open, reading");

        std::fgets(buff, _countof(buff), file); // declaration line
        std::fgets(buff, _countof(buff), file); // root line

        char* endTag;
        {
            endTag = new char[std::strlen(root) + 4]; // root -> </root>
            std::sprintf(endTag, "</%s>", root);
        }

        while (!std::feof(file))
        {
            std::fgets(buff, _countof(buff), file);

            if (!std::strcmp(buff, endTag)) // check if not </root>
                break;

            char format[smallBuffSize];
            char namebuf[smallBuffSize];
            char textbuf[smallBuffSize];
            std::sprintf(format, "<%s name = \"%%[^\"]s\">", node);
            std::sscanf(buff, format, namebuf);
            std::sscanf(std::strstr(buff, ">")+1, "%[^<]s", textbuf);

            auto ptr = new Element20(namebuf, textbuf);
            list->AddElement(ptr);
        }

        Log("closing file");
        std::fclose(file);
    }
    else
    {
        Log("file open fail");
    }

    Log("</doc-read>");
}

void Document20::FlushDataToFile()
{
    Log("<doc-flush>");

    std::FILE* file = std::fopen(path, "w");
    if(file)
    {
        Log("file open, flushing");

        std::fprintf(file, "%s%s", decl, "\n");
        std::fprintf(file, "<%s>%s", root, "\n");
        
        for (List20::Link* it = list->Top(); it; it = it->next)
        {
            std::fprintf(file, R"(<%s name = "%s">%s</%s>%s)", node, it->elem->GetName(), it->elem->GetText(), node, "\n");
        }

        std::fprintf(file, "</%s>", root);

        Log("closing file");
        std::fclose(file);
    }
    else
    {
        Log("file open fail");
    }
    Log("</doc-flush>");
}

Document20::~Document20()
{
    Log("<doc-cleanup>");

    delete[] path;
    delete[] root;
    delete[] node;
    delete[] decl;
    delete list;

    Log("</doc-cleanup>");
}
