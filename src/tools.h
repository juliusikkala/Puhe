#ifndef TOOLS_H_
#define TOOLS_H_
    inline unsigned char_one_of(char c, const char* of)
    {
        for(;*of!='\0';of++)
        {
            if(c==*of)
            {
                return 1;
            }
        }
        return 0;
    }
#endif
