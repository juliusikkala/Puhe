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
        if(read_file(argv[1], src))
        {
            printf("%s: Could not open file for reading\n", argv[1]);
            return 2;
        }
        c.generate(src);
    }

    for(const std::string& str: c)
    {
        if(str.size()>0&&!char_one_of(str[0], ".,!?:;/\\-"))
        {
            putchar(' ');
        }
        printf("%s", str.c_str());
    }
    putchar('\n');
}
