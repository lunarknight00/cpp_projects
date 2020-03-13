// #pragma once
#include<iostream>
#include<string>
#include<cmath>

using namespace std;

enum Type{
    Int = 0,
    Double = 1,
    EMPTY = 3
};

class variant{
    private:
        bool ERROR;
        Type type;
        int intVal;
        double doubleVal;

    public:
        // constructor declear
        variant(){type = EMPTY;}
        variant(int value);
        variant(double value);
        variant(string value);
        variant(variant const &others){
            type = others.type;
            intVal = others.intVal;
            doubleVal = others.doubleVal;
        }

        Type getType(){return type;}

        //operator overloading 
        variant &operator=(variant const &others){
            type = others.type;
            intVal = others.intVal;
            doubleVal = others.doubleVal;
        }

        // made friend for access private member
        friend variant operator*(variant const &lvlaue,variant const & rvlaue);
        friend variant operator-(variant const &lvlaue,variant const & rvlaue);
        friend variant operator+(variant const &lvlaue,variant const & rvlaue);
        friend variant operator/(variant const &lvlaue,variant const & rvlaue);
        friend ostream& operator<<(ostream& os,variant const &others);

        // member function
        string ToStr();
        

};