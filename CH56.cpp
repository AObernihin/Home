
#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <thread>
#include <time.h>
#include <map>
using namespace std;



//class Calculator
//{
//public:
//    function<int(int, int)> sum = [](int a, int b) {return a + b; };
//    function<int(int, int)> multy = [](int a, int b) {return a * b; };
//    function<int(int, int)> minus = [](int a, int b) {return a - b; };
//    function<int(int, int)> divide = [](int a, int b) {return a / b; };
//	
//};
//


class MathOperations {
    function<int(int, int)> add = [](int a, int b) {return a + b; };
    function<int(int, int)> multiply = [](int a, int b) {return a * b; };
    public:
	int Add(int a, int b) { return add(a, b); }
	int Multiply(int a, int b) { return multiply(a, b); }

};

class Counter {
    int counter = 0;
public:
	auto getIncrement() { return [this]() { return ++counter; }; };
};
class Greeter {
    string name;
    function<void()> greet;
public:
	Greeter(string nameu) : name(nameu) {
		greet = [this]() { cout << "Hello " << name << endl; };
    }

    void Greet() { greet(); }
	
};

class Executor {
public:
    function<void()> executeTask = []() { cout << "Executing task" << endl; };
};

class Numbers {
    vector<int> numbers;
public:
    Numbers(vector<int> numbers1) : numbers(numbers1) {}

    void PrintFiltered(function<bool(int)> filter) {
		for_each(numbers.begin(), numbers.end(), [filter](int i) { if (filter(i)) cout << i << endl; });
	}
};

class People {
    vector<string> names;
public:
        People(vector<string> names1) : names(names1)
        {

        }
    void sortNames() {
        auto predicate = [](string a, string b) {int a1 = a.size(); int b1 = b.size(); return a1 < b1; };
		sort(names.begin(), names.end(), predicate);
	}

    void show() {
		for_each(names.begin(), names.end(), [](string i) { cout << i << endl; });
	}

};

class Grades {
	vector<int> marks;
public:
	Grades(vector<int> marks1) : marks(marks1) {}
	void show() {
        for_each(marks.begin(), marks.end(), [](int i) { cout<<" " << i; });
	}
    void removeLowGrades(int threshold) {
		auto predicate = [threshold](int a) {return a > threshold; };
       for(int i = 0; i < marks.size(); i++)
		{
			if (!predicate(marks[i]))
			{
				marks.erase(marks.begin() + i);
				i--;
			}
		}
	}
};



class AgeFilter {

public:
    void FilterAdults(map<string, int> people) {
	
		for_each(people.begin(), people.end(), [](pair<string, int> i) { if (i.second > 18) cout << i.first << endl; });
         
    }
};

class Scaler {
    vector<int> numbers;
public:
    Scaler(vector<int> numbers1) : numbers(numbers1) {}
    void scale(int factor) {
       /* for_each(numbers.begin(), numbers.end(), [factor](int& i) { i = i * factor; });*/
        transform(numbers.begin(), numbers.end(), numbers.begin(), [factor](int i) { return i * factor; });
    }
    void Show() {
		for_each(numbers.begin(), numbers.end(), [](int i) { cout << i << endl; });
	}
};

class ResourceManager {
    unique_ptr<int> resource;
public:
    void MoveResource(unique_ptr<int> resource1) {
        auto lmbd = [res = move(resource)]() { cout << *res << endl; };
    }
	
};
		



    int main()
    {
        int x = 10;
        auto PrintX = [=]() {cout << x << endl; };

        //================
        auto IncrementX = [&x]() {x++; };
        IncrementX();
        IncrementX();
        cout << x << endl;

        //================
        int a = 10;
        int b = 20;
        auto SumAB = [](int a, int b) {return a + b; };
        //================
        auto lmbd = [=]() {cout << "X:" << x << "a:" << a << "b:" << b << endl; };
        auto lmbd2 = [&, x]() {cout << "X:" << x << "a:" << a << "b:" << b << endl; };
        lmbd();
        lmbd2();
        //================
        int count = 0;
        auto IncrementCount = [&count]()mutable {count++; };

        //================
        vector<int> v = { 1,2,3,4,5,6,7,8,9,10 };
        for_each(v.begin(), v.end(), [](int i) { i = i * 2; cout << i; });
        cout << endl;
        //================  
        vector<int> values = { 3, 1, 4, 1, 5, 9, 2 };
        auto pred = [](int a, int b) {return a > b; };
        sort(values.begin(), values.end(), pred);
        for (int i = 0; i < values.size(); i++)
        {
            cout << values[i] << " ";
        }
        cout << endl;

        //============  
        /*vector<int> numbers = { 10, 20, 30, 40, 50, 60 };
        int multiplier;
        cout << "Enter multiplier: ";
        cin >> multiplier;
        auto pred2 = [multiplier](int a) {return a * multiplier; };
        transform(numbers.begin(), numbers.end(), numbers.begin(), pred2);
        for (int i = 0; i < numbers.size(); i++)
        {
            cout << numbers[i] << " ";
        }*/



        //===================
        int threadRunning = 0;
        string message = "Thread running";
        auto thread = std::thread([&message, &threadRunning]() {
            for (int i = 1; i <= 5; i++)
            {
                cout << i << endl;
                this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            threadRunning = 1;
            message = "Thread finished";
            });
        thread.join();
        cout << message << endl;
        //===========================

        MathOperations mathOperations;
        int result = mathOperations.Add(2, 3);
        cout << result << endl;
        result = mathOperations.Multiply(2, 3);
        cout << result << endl;
        //===========================
        Numbers numbers1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
		numbers1.PrintFiltered([](int i) {return i % 2 == 0; });
        //===========================
		People people({ "John", "Jane", "Bob", "Alice", "Charlie" });
		people.sortNames();
		people.show();
        //===========================
        class Grades grades({ 11, 2, 12,9, 10, 10, 7, 6, 9, 10 });
		grades.show();
        cout << endl;
		grades.removeLowGrades(9);
		grades.show();
       //===========================
		map<string, int> ages = { { "John", 15 }, { "Jane", 30 }, { "Bob", 35 }, { "Alice", 14 }, { "Charlie", 45 } };
		AgeFilter ageFilter;
		ageFilter.FilterAdults(ages);
		//===========================
        Scaler scaler1({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
		scaler1.scale(2);
        scaler1.Show();
        //===========================
		

       





    }

























    /*
    int a = 10;
    int b = 20;
    int counter = 0;
    string num = "10";

    auto strChange = [&num](string str){num = str;};
    auto lambda = [=](){cout << "a:" << a << "b:" << b << endl; };
    lambda();

    auto increment = [&counter](){counter++;};
    increment();
    increment();
    increment();

    cout << num << endl;
    strChange("20");
    cout << num << endl;


    auto lmbd = [=, &b ](int newB){b = newB; cout << "a:" << a << "b:" << b << endl; };
    lmbd(30);


    int x = 10;
    auto lmbd2 = [x]()mutable {x++; cout << "X in Lmbd2: " << x << endl;};
    lmbd2();

     auto ptr = make_unique<int>(10);

     auto lmbd3 = [p = move(ptr)](){cout << "X in Lmbd3: " << *p << endl;};
     lmbd3();

     vector<int> vec = {1, 8, 3, 43, 7, 2};
     sort(vec.begin(), vec.end(), [](int a, int b){return a > b;});
     for (int i = 0; i < vec.size(); i++)
     {
         cout << vec[i] << " ";
     }
    */



