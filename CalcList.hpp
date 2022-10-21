#ifndef CALCLIST_H
#define CALCLIST_H

#include <iostream>
#include <cstdlib>

#include <sstream>
#include <iomanip>

#include "CalcListInterface.hpp"

class node {
     
     //Singly Linked List
     friend class CalcList;
     node* next;

     FUNCTIONS operation;
     double total; 
     double operand;
};

class CalcList: public CalcListInterface {
     private: 
          node* pointer;

     public: 
          int count = 0;// no of operations

          void add_node (const double& new_node);//add on top
          void remove_node ();

          CalcList();//Constructor
          ~CalcList();//Destructor

          bool empty() const { return (count == 0); }//returns if list empty

          //interface functions again, (what is the purpose of calclistinterface.hpp????)
          double total() const;
          void newOperation(const FUNCTIONS func, const double operand);
          void removeLastOperation();
          std::string toString(unsigned short precision) const;
};

#endif