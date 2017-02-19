

void Foo() {
    throw 42;
}

int Bar() {
    return 42;
}

int main() {
    try {
        Foo();
    }
    catch (...) {
        return 1;
    }
    
    if (Bar() == 42) {
        return 1;
    }
    
    return 0;
}