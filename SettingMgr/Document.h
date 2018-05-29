#pragma once
class Element;

class Document
{
public:
    Document();
    Document(char const* documentName);
    
    char const* GetDocName() const;
    void SetDocName(char const* newDocName);

    //char const* GetRootName() const;
    //void SetRootName(const char* newRootName);

    //Element* GetDeclaration();
    //void SetDeclaration(char const* version, char const* encoding, char const* standalone);

    void ReadFromFile();
    void FlushToFile();

    Element* operator[](char const*);
    
    ~Document();
protected:
    char* docName;
    Element* elems;
};

