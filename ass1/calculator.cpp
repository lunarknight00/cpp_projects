/*
Write a stack-based calculator program in C++. The calculator reads tokens (numbers and commands) from a specified input file. 
In the input file each token is separated by a space or a new line. 
Each number is placed on a stack and each command consumes one or more values from the stack. 
A command may result in a modification of the stack, an additional number added to the stack, and/or output printed to the console (stdout / cout). 
The calculator should support int and double values and only promote an int to a double when necessary. 
Your program should be written in pure C++ (not C) and should make use of the C++ STL. 
When printing output your double values should be formatted to three decimal places.
*/

#include "calculator.hpp"

void clear( queue<string> &q )
{
   queue<string> empty;
   swap( q, empty );
}

void arithmetic(stack<string> &Stack, const string &cmd){
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);
    if(Stack.size()<2) return;
    variant res = variant();

    variant lhs(Stack.top());
    // cout<<Stack.top()<<endl;
    Stack.pop();
    variant rhs(Stack.top());
    // cout<<Stack.top()<<endl;
    Stack.pop();

    // cout<<lhs<<endl;
    // cout<<rhs<<endl;

    if(cmd == "add"){
        res = lhs + rhs;
        cout<< lhs << " + "<<rhs<<" = "<<res<<endl;
        Stack.push(res.ToStr());       
    }
    else if(cmd == "sub"){
        res = lhs - rhs;
        cout<< lhs << " - "<<rhs<<" = "<<res<<endl;
        Stack.push(res.ToStr());       
    }
     else if(cmd == "mult"){
        res = lhs * rhs;
        cout<< lhs << " * "<<rhs<<" = "<<res<<endl;
        Stack.push(res.ToStr());       
    }
    else if(cmd == "div"){
        res = lhs / rhs;
        cout<< lhs << " / "<<rhs<<" = "<<res<<endl;
        Stack.push(res.ToStr());       
    }
    // cout<< res.getType()<<endl;
    // cout<<"\n"<<endl;
    if(res.getType() != EMPTY) 
        Stack.push(res.ToStr());
    else{
        Stack.push(lhs.ToStr());
        Stack.push(rhs.ToStr());
    }
	return;
}

void Sqrt(stack<string> &Stack,string s){
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);
	if(s != "sqrt" || Stack.empty()) return;

	double value = stod(Stack.top());
	double res = sqrt(value);
	Stack.pop();
	cout << "sqrt "<< value << " = " << res <<endl;
	Stack.push(to_string(res));
	return;
}

void processRepeat(stack<string> &Stack, queue<string> &Buffer,int numRepeat){
	
	if(numRepeat==0) return;

	bool REPEAT = false;
	queue<string> innerRepeat,buffer;
	buffer = Buffer;
	string s = buffer.front();
	int innerCount;
	
	while(!buffer.empty())
	{
		if(s == "repeat")
		{
			REPEAT = true;
			buffer.pop();
			s = buffer.front();
			continue;
		}
		else if (s == "endrepeat")
		{
			innerCount = stoi(Stack.top());
			Stack.pop();
			processRepeat(Stack,innerRepeat,innerCount);
		}
		else if(s=="pop"){
			Stack.pop();
			buffer.pop();
			s = buffer.front();
			continue;
		}
		else if(s=="reverse"){
			int num = stoi(Stack.top());
			Stack.pop();
			// cout<< "INNER stack: "<<Stack.top()<<endl;
			reverse(Stack,num);
			// cout<< "INNER stack: "<<Stack.top()<<endl;
			buffer.pop();
			s = buffer.front();
			continue;
		}
		if(REPEAT)
		{
			innerRepeat.push(s);
			buffer.pop();
			s = buffer.front();
			continue;
		}
		else
		{
			// cout<< "INNER s: "<<Stack.top()<<endl;
			if(isdigit(s[0]))
			{

				// cout<< "INNER stack: "<<Stack.top()<<endl;
				Stack.push(s);
				buffer.pop();
				s = buffer.front();
				continue;
			}
			if(s=="sqrt") Sqrt(Stack,s);
			else arithmetic(Stack,s);
			// cout<< 11111111111<<endl;
		}
		buffer.pop();
		if(!buffer.empty())
			s = buffer.front();
	}
	processRepeat(Stack, Buffer,numRepeat-1);

}

void reverse(stack<string> &Stack, const int &count){
	int i = 0;
	queue<string> buffer;
 	while(i < count)
	{
		// cout<< "INNER reverse stack: "<<Stack.top()<<endl;
		 buffer.push(Stack.top());
		 Stack.pop();
		 i++;
	}
	while(!buffer.empty()){
		Stack.push(buffer.front());
		buffer.pop();
	}
}



int main(int argc, char* argv[]) {

	// init a stack for store number
	stack<string> Stack;
	queue<string> repeatBuffer; 

	// setup the print out format for the precision required.
	cout.setf(ios::fixed,ios::floatfield);
	cout.precision(3);

	// open the file for reading
	ifstream in;
	in.open(argv[1]);

	// string to be read into
	string s;

	bool REPEAT = false;
	int numRepeat;

	//// only for test
	// int i = 0;
	// read the file while we have input.
	while (in >> s) {

		// // only for test
		// if(i==13) break;

		// cout<<s<<endl;
		// push stack if it is a number 
		if(s == "repeat") {
			REPEAT = true;
			numRepeat = stoi(Stack.top());
			// cout<<"numRepeat: "<<numRepeat<<endl;
			Stack.pop();
			continue;
		}
		else if(s == "endrepeat"){
			// cout<<"enter repeat"<<endl;
			processRepeat(Stack,repeatBuffer,numRepeat);
			clear(repeatBuffer);
			REPEAT = false;
			continue;
		}
		else if(s=="pop"&& ! REPEAT){
			Stack.pop();
		}
		else if(s=="reverse" && ! REPEAT){
			int num = stoi(Stack.top());
			Stack.pop();
			// cout<< "num: "<<num<<endl;
			reverse(Stack,num);
			continue;
		}

		if(!REPEAT){
			if(isdigit(s[0])){
				Stack.push(s);
				continue;
			}
			if(s=="sqrt") Sqrt(Stack,s);
			else arithmetic(Stack,s);
		}
		else{
			// enqueue to buffer
			// cout<< "OUTER s: "<<s <<endl;
			repeatBuffer.push(s);
			// cout<< "repeatBuffer back: "<<repeatBuffer.back() <<endl;
		}

		// // only for testing
		// i ++;
	}
	in.close();
}