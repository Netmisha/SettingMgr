#ifdef _DEBUG
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <memory>
#include <cstdlib>
#include "Element.h"

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

int main()
{
    Test_ElementSetProperties();

    return 0;
}



#endif