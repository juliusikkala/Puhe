/*
The MIT License (MIT)

Copyright (c) 2015 Julius Ikkala

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "chain.h"
#include "tools.h"
#include <sstream>

static void find_node(
    const char* source,
    size_t& pos,
    size_t& len
){
    len=0;
    while(isspace(*source))
    {
        source++;
        pos++;
    }
    for(;*source!='\0';source++, len++)
    {
        switch(*source)
        {
        case ' ':
        case '\n':
        case '\t':
            return;
        case ':':
        case '\'':
            if(len==0)
            {
                len=1;
                return;
            }
            else if(source[1]==' ')
            {
                return;
            }
            break;
        case '-':
            if(len==0&&source[1]==' ')
            {
                len=1;
                return;
            }
            else if(source[1]==' ')
            {
                return;
            }
            break;
        case '.':
        case ',':
        case '!':
        case '?':
        case ';':
        case '/':
        case '\\':
            if(len==0)
            {
                len=1;
                return;
            }
            else
            {
                return;
            }
        }
    }
}
static std::vector<std::string> split(const std::string& source)
{
    std::vector<std::string> res;
    size_t pos=0;
    size_t len=0;
    while(pos<source.size())
    {
        find_node(source.c_str()+pos, pos, len);
        if(len==0)
        {
            break;
        }
        res.push_back(source.substr(pos, len));
        pos+=len;
    }
    return res;
}

link::link(node& n, unsigned weight): n(&n), weight(weight){}
node::node(){}
node::node(const std::string& str): str(str) {}

std::string& node::get()
{
    return str;
}
const std::string& node::get() const
{
    return str;
}
void node::add_link(node& n)
{
    for(link& it: links)
    {
        if(it.n==&n)
        {
            it.weight++;
            return;
        }
    }
    links.push_back(link(n, 1));
}
void node::clear()
{
    links.clear();
}
unsigned node::total_weight() const
{
    unsigned total=0;
    for(const link& it: links)
    {
        total+=it.weight;
    }
    return total;
}
bool node::operator==(const node& o) const
{
    return str==o.str;
}
chain_iterator::chain_iterator(const node* n)
: n(n), rng(std::time(nullptr))
{}
const std::string& chain_iterator::operator*() const
{
    return n->str;
}
bool chain_iterator::operator!=(const chain_iterator& o) const
{
    return o.n!=n;
}
chain_iterator& chain_iterator::operator++()
{
    n=n->next(rng);
    return *this;
}
void chain::clear()
{
    nodes.clear();
    head.clear();
}
void chain::generate(const std::string& source)
{
    size_t i=0;
    std::vector<std::string> sources=split(source);
    if(sources.size()>0)
    {
        head.add_link(nodes[sources[0]]);
    }
    for(i=0;i<sources.size()-1;++i)
    {
        node& cur=nodes[sources[i]];
        node& next=nodes[sources[i+1]];
        cur.str=sources[i];
        next.str=sources[i+1];
        cur.add_link(next);
        if(cur.str.size()>0&&char_one_of(cur.str[0], ".?!"))
        {
            head.add_link(nodes[sources[i+1]]);
        }
    }
}
chain_iterator chain::begin() const
{
    return ++chain_iterator(&head);
}
chain_iterator chain::end() const
{
    return chain_iterator(nullptr);
}
