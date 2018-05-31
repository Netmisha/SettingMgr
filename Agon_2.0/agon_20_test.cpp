#ifdef _DEBUG
#include <iostream>


#include "Document20.h"
#include "Element20.h"
#include "List20.h"
#include "Logger.h"

#define fileName "test20.xml"
#define rootName "settings"
#define nodeName "setting"
#define declStat R"(<?xml version="1.0" encoding="UTF-8" standalone="no" ?>)"

void Test_DocFlush(Document20& doc)
{
    Log("<test-doc-flush>");

    doc.GetList().AddElement(new Element20("type", "int"));
    doc.GetList().AddElement(new Element20("value", 22.5));
    doc.GetList().AddElement(new Element20("sizeof", sizeof(int)));
    doc.GetList().AddElement(new Element20("key_1", "val_1"));
    doc.GetList().AddElement(new Element20("key_2", "val_2"));
    doc.GetList().AddElement(new Element20("key_3", "val_3"));

    doc.FlushDataToFile();

    Log("</test-doc-flush>");
}

void Test_DocRead(Document20& doc)
{
    Log("<test-doc-read>");
    doc.RetreiveFileData();

    for (auto it = doc.GetList().Top(); it; it = it->next)
    {
        std::cout << it->elem->GetName() << " " << it->elem->GetText() << std::endl;
    }

    Log("</test-doc-read>");
}

void Test_DocRemove(Document20& doc)
{
    Log("<test-doc-remove>");

    doc.GetList().RemoveElement("value");
    doc.GetList().RemoveElement("sizeof");
    doc.GetList().RemoveElement("type");

    Log("</test-doc-remove>");
}

int main()
{
    Log("<start>");

    Document20 doc(fileName, rootName, nodeName, declStat);

    Test_DocFlush(doc);

    Test_DocRead(doc);

    Test_DocRemove(doc);

    Log("</start>");

    return 0;
}


#endif
