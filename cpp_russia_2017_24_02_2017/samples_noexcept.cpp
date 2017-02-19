#include "utils.h"


int main()
{
    vector<Foo> a;
    a.push_back_nothrow(10);
    
    vector<Foo> c;
    c.assign_copy(a);
    
    vector<vector<Foo>> d;
    d.push_back_nothrow(a);
    
    return 0;
}