#pragma once
class Element;

class Document
{
public:
    Document(char const* documentName = nullptr, size_t elementReserve = 16);
    
    char* const GetDocName() const;
    void        SetDocName(char const* newDocName);

    //char const* GetRootName() const;
    //void SetRootName(const char* newRootName);

    //Element* GetDeclaration();
    //void SetDeclaration(char const* version, char const* encoding, char const* standalone);

    void     AddElement(Element* newElement);
    void     AddElement(char const* elementName);
    void     AddElement(Element const& object);
    void     AddElement(Element&& object);
    Element* GetElement(char const* elementName);
    void     RemoveElement(char const* elementName);

    size_t   GetElementCout() const;
    
    Element** const GetElementPtrs() const;

    void ReadFromFile();
    void FlushToFile();
    
    ~Document();
protected:
    char*       name;
    Element**   pelems;
    size_t      elemLen;
    size_t      elemRes;
};

