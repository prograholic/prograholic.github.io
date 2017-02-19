#include "utils.h"


int main()
{
    vector<Foo> a;
    a.push_back(10);
    
    vector<Foo> b{a};
    
    vector<Foo> c;
    c = a;
    
    vector<vector<Foo>> d;
    d.push_back(a);
    
    return 0;
}