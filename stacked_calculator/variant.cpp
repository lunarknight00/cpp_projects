/*
Create a class for int float conversion and operatpInt && rvlaue == Intlo
ading
*/
#include "variant.hpp"

variant::variant(int value){
    type = Int;
    intVal = value;
}

variant::variant(double value){
    type = Double;
    doubleVal = value;
}

variant::variant(string value){
    if(value.find('.')!=string::npos){
        type = Double;
        doubleVal = stod(value);     
    } 
    else{
        type = Int;
        intVal = stoi(value);
    }
}

// ref operator overloading function
// overloading operator cout
ostream& operator<<(ostream& os,variant const &others){
    if(others.type == Int){
        os << others.intVal;
    }
    else{
        os << others.doubleVal;
    }
    return os;
}


variant operator*(variant const & lvlaue,variant const & rvlaue){
    if(lvlaue.type == Int && rvlaue.type == Int){
        return variant(lvlaue.intVal * rvlaue.intVal);
    }
    else if(lvlaue.type != Int && rvlaue.type == Int){
        return variant(lvlaue.doubleVal * rvlaue.intVal);
    }
    else if(lvlaue.type == Int && rvlaue.type != Int){
        return variant(lvlaue.intVal * rvlaue.doubleVal);
    }
    else if(lvlaue.type != Int && rvlaue.type != Int){
        return variant(lvlaue.doubleVal * rvlaue.doubleVal);
    }
}

variant operator-(variant const &lvlaue,variant const & rvlaue){
    if(lvlaue.type == Int && rvlaue.type == Int){
        return variant(lvlaue.intVal - rvlaue.intVal);
    }
    else if(lvlaue.type != Int && rvlaue.type == Int){
        return variant(lvlaue.doubleVal - rvlaue.intVal);
    }
    else if(lvlaue.type == Int && rvlaue.type != Int){
        return variant(lvlaue.intVal - rvlaue.doubleVal);
    }
    else if(lvlaue.type != Int && rvlaue.type != Int){
        return variant(lvlaue.doubleVal - rvlaue.doubleVal);
    }
}

variant operator+(variant const &lvlaue,variant const & rvlaue){
    if(lvlaue.type == Int && rvlaue.type == Int){
        return variant(lvlaue.intVal + rvlaue.intVal);
    }
    else if(lvlaue.type != Int && rvlaue.type == Int){
        return variant(lvlaue.doubleVal + rvlaue.intVal);
    }
    else if(lvlaue.type == Int && rvlaue.type != Int){
        return variant(lvlaue.intVal + rvlaue.doubleVal);
    }
    else if(lvlaue.type != Int && rvlaue.type != Int){
        return variant(lvlaue.doubleVal + rvlaue.doubleVal);
    }
}

variant operator/(variant const &lvlaue,variant const & rvlaue){
    if(lvlaue.type == Int && rvlaue.type == Int){
        return variant(lvlaue.intVal/rvlaue.intVal);
    }
    else if(lvlaue.type != Int && rvlaue.type == Int){
        return variant(lvlaue.doubleVal/rvlaue.intVal);
    }
    else if(lvlaue.type == Int && rvlaue.type != Int){
        return variant(lvlaue.intVal/rvlaue.doubleVal);
    }
    else if(lvlaue.type != Int && rvlaue.type != Int){
        return variant(lvlaue.doubleVal/rvlaue.doubleVal);
    }
}

string variant ::ToStr(){
    if(getType() == Int) return to_string(intVal);
    else return to_string(doubleVal);
}


// int main(){

//     cout.setf(ios::fixed,ios::floatfield);
//     cout.precision(3);
//     variant v(1.6);
//     variant w(2);
//     cout <<1.6<<" "<< 2 <<endl;

//     variant s = v * w;

//     cout<< "multiplies: " <<s <<endl;

//     variant s1 = v + w;

//     cout<< "add: "<<s1 <<endl;

//     variant s2 = v - w;

//     cout<< "sub: "<<s2 <<endl;

//     variant s3 = v / w;

//     cout<< "divide: "<<s3 <<endl;

//     variant s4 = variant("1.5");

//     cout << s4 << endl;
//     cout << s4 + s3 << endl;

//     cout<<stod("1.6")<<endl;
//     cout<< s4.ToStr()<<endl;
//     return 0;
// }