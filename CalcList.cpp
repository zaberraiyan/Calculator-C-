/************************************
 * Zaber Raiyan Choudhury
 * 
 * Project One, Data Structures COP 4530
 * 
 *
 * 
 * **********************************/

#include "CalcList.hpp"

//Constructor
CalcList::CalcList() : CalcListInterface() {
    pointer = new node;
    pointer->operation = ADDITION;
    pointer->operand = 0.0;
    pointer->total = 0.0;
    pointer->next = pointer;//circular CalcList
}

//Destructor executes if empty returns 0
CalcList::~CalcList() {
    while (empty()== 0) { remove_node();}
}

void CalcList::add_node(const double& new_node) {
    
    node* new_pointer = new node;//adding to CalcList

    new_pointer->operation = ADDITION;
    new_pointer->operand = 0.0;
    new_pointer->total = 0.0;
    new_pointer->next = nullptr;

    if(pointer == nullptr) {//create circular linked CalcList
        new_pointer->total = new_node;
        pointer = new_pointer;
        pointer->next = new_pointer;
    }
    else {//add node to existing circular linked CalcList
        new_pointer->next = pointer->next;
        new_pointer->total = pointer->next->total;
        pointer->next = new_pointer;
    }
    ++count; //number of operations done
}

void CalcList::remove_node(){
    if(empty()) { throw("No node present in function"); }
    else {
        node* remove_pointer = pointer->next; //pointing to node to be removed
        if (remove_pointer == pointer) {pointer = nullptr;} //set to null if pointer points to itself
        else {
            pointer->next = remove_pointer->next;
        }
        
        delete remove_pointer;//node removed

        --count;//operation removed
    }
}

double CalcList::total() const {
    return pointer->next->total; //calculation total
}

void CalcList::newOperation (const FUNCTIONS func, const double operand) {
    add_node(0);//default node

    //Operations executed
    switch(func){
        case ADDITION:
                pointer->next->operation = ADDITION;
                pointer->next->operand = operand;
                pointer->next->total += operand;
                break;
        case SUBTRACTION:
                pointer->next->operation = SUBTRACTION;
                pointer->next->operand = operand;
                pointer->next->total -= operand;
                break;
        case MULTIPLICATION:
                pointer->next->operation = MULTIPLICATION;
                pointer->next->operand = operand;
                pointer->next->total *= operand;
                break;
        case DIVISION:
                pointer->next->operation = DIVISION;
                pointer->next->operand = operand;

                    if(operand == 0) { throw ("Cannot divide by 0");}

                pointer->next->total /= operand;
                break;
        default:
                throw ("incorrect operation selected");
                break;
    }
}

void CalcList::removeLastOperation() {
        remove_node();

}

//add comments
std::string CalcList::toString(unsigned short precision) const {
    
    std::stringstream prnt;//initializing string stream to print
    std::string data_to_string = "";

    int counter = count;
    
    node* holder = new node;//node pointer for temporarily holding node data
    holder = pointer->next;

    prnt.precision(precision);

    while(holder->total != 0){
        prnt << counter << ": ";

        prnt<< std::fixed << holder->next->total;

        //printing operations
        if (holder->operation == ADDITION) {
                prnt << "+";
        }
        else if (holder->operation == SUBTRACTION) {
                prnt << "-";
        }
        else if (holder->operation == MULTIPLICATION) {
                prnt << "*";
        }
        else if (holder->operation == DIVISION) {
                prnt << "/";
        }
        prnt << holder->operand;
        prnt << "=";
        prnt << holder->total;
        prnt << std::endl;
                
        holder = holder->next;
        --counter;
    }

    data_to_string = prnt.str();//return
    return data_to_string;

}
