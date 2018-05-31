#pragma once

class List20;

class Document20
{
public:
    Document20(char const* path, char const* root, char const* node, char const* decl);

    List20& GetList();

    void RetreiveFileData();
    void FlushDataToFile();

    ~Document20();
protected:
    char* path;
    char* root;
    char* node;
    char* decl;

    List20* list;
};

