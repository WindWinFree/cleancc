#ifndef __SGC_STRUTILS_H__
#define __SGC_STRUTILS_H__
#include <iostream>
#include <stdlib.h>

//////////////////////////////////////////
// char *
//////////////////////////////////////////

unsigned int gt2u(const char *t, int def)
{
	return (t ? strtoul(t, NULL, 10) : def);
}
unsigned int gt2i(const char *t, int def)
{
	return (t ? strtol(t, NULL, 10) : def);
}

int StrIndex(const char *s, char t[])
{
   int i, j, k;
   for (i = 0; s[i] != '\0'; i++)
   {
       for (j=i, k=0; t[k] != '\0' && s[j]==t[k]; j++,k++)
           ;
       if (k > 0 && t[k] == '\0')
             return i;
   }
   return -1
}


//////////////////////////////////////////
// string
//////////////////////////////////////////

std::string StringHex(std::string const& s)
{
    std::ostringstream out;
    out << std::hex ; /* <<  std::setfill('0') << std::setw(4);*/

    int cnt = 0;
    for (std::string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        if(cnt%2 == 0) out << " ";
        if(cnt%16 == 0) out << "\n";
        cnt++;
        out << setfill('0') << setw(2) << (static_cast<short>(*it) & 0xff);
    }

    return out.str();
}
#endif
