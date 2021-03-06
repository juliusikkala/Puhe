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
#include <cstdio>

int read_file(const char *path, std::string& str)
{
    FILE* f=fopen(path, "rb");
    if(f==NULL)
    {
        return 1;
    }
    fseek(f, 0, SEEK_END);
    size_t sz=ftell(f);
    fseek(f, 0, SEEK_SET);
    str.resize(sz);
    fread(&str[0], 1, sz, f);
    return 0;
}

int main(int argc, char **argv)
{
    if(argc<2)
    {
        printf("Usage: %s textfile\n", argv[0]);
        return 1;
    }
    chain c;
    int i=0;
    for(i=1;i<argc;++i)
    {
        std::string src;
        if(read_file(argv[i], src))
        {
            printf("%s: Could not open file for reading\n", argv[i]);
            return 2;
        }
        c.generate(src);
    }

    for(const std::string& str: c)
    {
        if(str.size()!=1||!char_one_of(str[0], ".,!?:;/\\-\'"))
        {
            putchar(' ');
        }
        printf("%s", str.c_str());
        fflush(stdout);
    }
    putchar('\n');
}
