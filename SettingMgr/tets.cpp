#ifdef _DEBUG
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <cstdlib>
#include "Element.h"
#include "Document.h"

void Test_ElementSetProperties()
{
    Element elem;
    {
        elem.SetName("NAME");
        elem.SetText("TEXT");
        for (int i = 0; i < 20; ++i)
        {
            char i_buff[16];
            char buff[32];
            _itoa_s(i, i_buff, sizeof(i_buff), 10);
            std::sprintf(buff, "prp_%s", i_buff);
            elem.SetProperty(buff, "PVAL");
        }

        elem.RemoveProperty("prp_0");
        elem.RemoveProperty("prp_10");
    }
    std::unique_ptr<char[]> ptr(elem.Represent());
    std::cout << ptr.get() << std::endl;
}

void Test_Document_CreateFillAndFlush()
{
    Document doc("test.xml", 5);

    doc.AddElement("elem_1");
    Element* pel = doc.GetElement("elem_1");
    pel->SetText("kek");
    pel->SetProperty("pel_prop_1", 1.0);
    pel->SetProperty("pel_Prop_2", "2.0");

    doc.AddElement(new Element("elem_2"));
    doc.AddElement(new Element("elem_3", "some text"));

    Element* pelpel = new Element();
    {
        pelpel->SetName("SomeCoolName");
        pelpel->SetText("Some generic Nietzsche quote.");
        pelpel->SetProperty("topkek", "kektop");
    }

    doc.FlushToFile();
}

Element* CharPtrToElem(char* ptr);
void Test_StrToEl()
{
    auto e1 = CharPtrToElem("  <  elem_1  el_prop_1  =  \"1.\"   el_Prop_2=\"2.0\"  >kek</elem_1>");
    std::cout << e1->Represent() << std::endl;
    delete e1;

    auto e11 = CharPtrToElem("<elem_1 el_prop_1=1.0 el_Prop_2=\"2.0\">kek</elem_1>");
    std::cout << e11->Represent() << std::endl;
    delete e11;

    auto e2 = CharPtrToElem("<elem_2></elem_2");
    std::cout << e2->Represent() << std::endl;
    delete e2;
}

void Test_Document_ReadFromFile()
{
    Document doc("test.xml");
    doc.ReadFromFile();

    std::cout << std::endl << "From document:" << std::endl;
    for (int i = 0; i < doc.GetElementCout(); ++i)
    {
        Element* e = doc.GetElementPtrs()[i];
        char* repr = e->Represent();
        std::cout << "\t" << repr << std::endl;
        delete[] repr;
    }
}

int main()
{
    //Test_ElementSetProperties();
    //Test_Document_CreateFillAndFlush();
    Test_StrToEl();
    Test_Document_ReadFromFile();
    return 0;
}



#endif