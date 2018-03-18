#include "testlib.h"
#include <sstream>

using namespace std;

int main(int argc, char * argv[])
{
    setName("compare ordered sequences of signed int%d numbers", 8 * sizeof(long long));

    registerTestlibCmd(argc, argv);

    int n = 0;
    string firstElems;

    while (!ans.seekEof() && !ouf.seekEof())
    {
        n++;
        long long j = ans.readLong();
        long long p = ouf.readLong();
        if (j != p)
            quitf(_wa, "%d%s numbers differ - expected: '%s', found: '%s'", n, englishEnding(n).c_str(), vtos(j).c_str(), vtos(p).c_str());
        else
            if (n <= 5)
            {
                if (firstElems.length() > 0)
                    firstElems += " ";
                firstElems += vtos(j);
            }
    }

    int extraInAnsCount = 0;

    while (!ans.seekEof())
    {
        ans.readLong();
        extraInAnsCount++;
    }
    
    int extraInOufCount = 0;

    while (!ouf.seekEof())
    {
        ouf.readLong();
        extraInOufCount++;
    }

    if (extraInAnsCount > 0)
        quitf(_wa, "Answer contains longer sequence [length = %d], but output contains %d elements", n + extraInAnsCount, n);
    
    if (extraInOufCount > 0)
        quitf(_wa, "Output contains longer sequence [length = %d], but answer contains %d elements", n + extraInOufCount, n);
    
    if (n <= 5)
        quitf(_ok, "%d number(s): \"%s\"", n, compress(firstElems).c_str());
    else
        quitf(_ok, "%d numbers", n);
}
