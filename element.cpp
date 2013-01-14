#ifndef ELEMENT_H_
#define ELEMENT_H_

#define DELAY 1
#define SUBCONTRACTION 2
#define EXTRA 3

class Element {
    public:
    
        int id;
        float cost;
        bool flag;
        //maximum number of elements
        int max;         
};

Element::Element() {
    id=0;
    cost=0.0;
    flag=false;
    max=0;
}

Element::~Element() {}

Element::setElement(int id, float cost, bool flag, int max) {
    this->id=id;
    this->cost=cost;
    this->flag=flag;
    this->max=max;
    
}

bool compare(Element el1, Element el2) {
    if(el1.flag) {
        if(el2.flag) {
            return(el1.cost<el2.cost);
        } else {
            return true;
        }
    } else {
        if(el2.flag) {
            return false;
        } else {
            return true;
        }
    }
}

#endif
