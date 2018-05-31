#include "List20.h"
#include "Element20.h"
#include "Logger.h"
#include <cstring>

List20::List20() :
    top(nullptr),
    bot(nullptr),
    size(0)
{
    Log("</lst_created>");
}
List20::~List20()
{
    Log("<lst_clean_up>");

    while (top)
    {
        Link* kill = top;
        top = top->next;
        delete kill;
    }

    Log("</lst_clean_up>");
}

List20::Link* List20::Top() const
{
    return top;
}

void List20::AddElement(Element20 * elm)
{
    if (not top)
    {
        top = bot = new Link(elm);
    }
    else
    {
        bot->next = new Link(elm);
        bot = bot->next;
    }

    ++size;
}
List20::Link const* List20::GetElement(char const * name) const
{
    for (Link* it = top; it; it = it->next)
    {
        if (not std::strcmp(it->elem->GetName(), name))
        {
            return it;
        }
    }
    return nullptr;
}
void List20::RemoveElement(char const* name)
{
    bool nameCmpSame; 
    //top
    nameCmpSame = not std::strcmp(top->elem->GetName(), name);
    if (nameCmpSame)
    {
        Link* kill = top;
        top = top->next;
        --size;
        delete kill;
        return;
    }
    //rest
    for (Link* it = top; it->next; it = it->next)
    {
        nameCmpSame = not std::strcmp(it->next->elem->GetName(), name);
        if (nameCmpSame)
        {
            Link* kill = it->next;
            it->next = kill->next;
            --size;
            delete kill;
            return;
        }
    }
}

List20::Link::Link(Element20* ptr):
    elem(ptr),
    next(nullptr)
{
    Log("</lnk_created>");
}

List20::Link::~Link()
{
    Log("<lnk-clean-up>");
    if (elem)
        delete elem;
    Log("</lnk-clean-up>");
}
