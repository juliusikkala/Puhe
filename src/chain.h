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
#ifndef CHAIN_H_
#define CHAIN_H_
    #include <vector>
    #include <unordered_map>
    #include <random>
    #include <iterator>
    #include <ctime>
    #include <string>
    class node;
    class link
    {
    friend class node;
    public:
        link(node& n, unsigned weight);
    private:
        node* n;
        unsigned weight;
    };
    class node
    {
    friend class chain;
    friend class chain_iterator;
    public:
        node();
        node(const std::string& data);
        
        template<class RNG>
        const node *next(RNG &rng) const
        {
            std::uniform_int_distribution<unsigned> dist(0, total_weight()-1);
            unsigned n=dist(rng);
            for(const link& it: links)
            {
                if(n<it.weight)
                {
                    return it.n;
                }
                else
                {
                    n-=it.weight;
                }
            }
            return nullptr;
        }
        std::string& get();
        const std::string& get() const;
        void add_link(node& n);
        void clear();
        unsigned total_weight() const;
        bool operator==(const node& o) const;
    protected:
    private:
        std::string str;
        std::vector<link> links;
    };

    class chain_iterator: public std::iterator<std::forward_iterator_tag, std::string>
    {
    public:
        chain_iterator(const node* n);
        const std::string& operator*() const;
        bool operator!=(const chain_iterator& o) const;
        chain_iterator& operator++();
    private:
        const node* n;
        std::mt19937_64 rng;
    };
    
    class chain
    {
    public:
        void clear();
        void generate(const std::string& source);
        chain_iterator begin() const;
        chain_iterator end() const;
    protected:
    private:
        std::unordered_map<std::string, node> nodes;
        node head;
    };
#endif
