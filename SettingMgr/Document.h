#pragma once
class Element;

class Document
{
public:
    Document(char const* documentName = nullptr, size_t elementReserve = 16);
    
    char* const GetDocName() const;
    void        SetDocName(char const* newDocName);

    void     AddElement(Element* newElement);
    void     AddElement(Element const& object);
    void     AddElement(Element&& object);
    Element* GetElement(char const* elementPropertyKey);
    Element* GetElement(char const* elementPropertyKey, char const* elementPropertyVal);
   
    void     RemoveElement(char const* elementPropertyKey, char const* elementPropertyVal);

    size_t   GetElementCout() const;
    
    Element** const GetElementPtrs() const;


    void ReadFromFile(const char* blockName, const char* tagName);

    void ReadFromFile();
    void FlushToFile();
    
    ~Document();
protected:
    char*       name;
    Element**   pelems;
    size_t      elemLen;
    size_t      elemRes;
};

