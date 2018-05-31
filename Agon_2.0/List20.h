#pragma once

class Element20;

class List20
{
public:
    struct Link
    {
        Link(Element20*);
        ~Link();

        Element20* elem;
        Link*      next;
    };

    List20();
    ~List20();

    Link* Top() const;

    void        AddElement(Element20* element);
    Link const* GetElement(char const* name) const;
    void        RemoveElement(char const* name);

protected:
    Link* top;
    Link* bot;
    size_t size;
};

