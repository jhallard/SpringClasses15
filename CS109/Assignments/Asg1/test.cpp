#include <vector>
#include <stdio.h>

class basevector {
private :

public :
    std::vector<int> vals;
    virtual int indexTo(int arg) {
        if(arg < 0 || arg >= vals.size())
            return 0;
        return vals[arg];
    }
    virtual void push(int arg) {
        vals.push_back(arg);
    }
    virtual int pop(int args) {
        return vals[vals.size()-1];
    }
    virtual int getSize() const {
        return vals.size();
    }
};

class myvector : private basevector {
public:
    virtual void push(int arg) {
        vals.push_back(arg);
    }
    virtual int pop(int args) {
        return vals[vals.size()-1];
    }
    virtual int getSize() const {
        return vals.size();
    }
};

int do_something(basevector * arg) {
    for(int i = 0; i < arg->getSize(); i++) {
        printf("%d ", arg->indexTo(i));
    }
}

int main() {

    basevector * vec = new myvector;

    for(int i = 0; i < 20; i++) {
        vec->push(i);
    }

    do_something(vec);

    delete vec;
}