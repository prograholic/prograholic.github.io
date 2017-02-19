#include "utils.h"



struct Test1 {
    Test1() noexcept : x(0) {}

    int x;
};

struct Test2 {
    Test1 t1;
    float f;
};


static_assert(std::is_nothrow_default_constructible_v<Test1>, "");
static_assert(std::is_nothrow_default_constructible_v<Test2>, "");

int main()
{
    vector<Foo> a;
    a.push_back_nothrow(10);
    
    vector<Foo> c;
    c.assign_copy(a);
    
    vector<vector<Foo>> d;
    d.push_back_nothrow(a);
    
    
    vector<Test2> t2;
    
    return 0;
}