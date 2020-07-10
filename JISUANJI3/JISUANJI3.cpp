// JISUANJI3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
using namespace std;


//定义一个Stack
//enum Error_code { bingo, overflow, underflow };
const int maxsize = 50;
template <class T>
class Stack {
public:
	Stack();
	bool empty() const;
	bool full() const;
	int size() const;
	bool top(T& item) const;
	bool pop();
	bool push(const T& item);
private:
	int count;
	T entry[maxsize];
};

template <class T>
Stack<T>::Stack()
{
	count = 0;
}

template <class T>
bool Stack<T>::empty() const
{
	return count == 0;
}

template <class T>
bool Stack<T>::full() const
{
	return count == maxsize;
}

template <class T>
int Stack<T>::size() const
{
	return count;
}



template <class T>
bool Stack<T>::top(T& item) const   //得到栈顶
{
	if (empty()) return false;
	item = entry[count - 1];
	return true;
}

template <class T>
bool Stack<T>::pop()           //出
{
	if (empty()) return false;
	count--;
	return true;
}

template <class T>
bool Stack<T>::push(const T& item)    //进
{
	if (full()) return false;
	entry[count++] = item;
	return true;
}




//进行计算的函数
void jisuan(char s, Stack<double>& num)
{
	double a, b;
	num.top(b);
	num.pop();
	num.top(a);
	num.pop();
	switch (s) {
	case'+':num.push(a + b); break;
	case'-':num.push(a - b); break;
	case'*':num.push(a * b); break;
	case'/':if (b != 0.0) num.push(a / b);
			else cout << "分母不能为0" << endl;
		break;
	}
}


//判断优先级，得到结果的函数
void proity(Stack<double> & num, Stack<char> & signal) {
	string str;
	string s;
	int i = 0;
	double result;
	string numtemp = "";
	char sign;
	cout << "请输入表达式" << endl;
	char temp;
	cin >> str;
	s = str;
	//当且仅当读入了2个数字以上才能继续进行
	while (1) 
	{
		if (str[i] >= '0' && str[i] <= '9' || str[i] == '.')
		{
			numtemp = numtemp + str[i];
			i++;
			while (str[i] >= '0' && str[i] <= '9' || str[i] == '.')
			{
				numtemp = numtemp + str[i];
				i++;
			}
			//得到一个数以后进行压栈操作
			num.push(atof(numtemp.c_str()));   //atof可以将“12.56”转化为十进制



		}
		else
		{
			sign = str[i];
			i++;//得到了一个字符以后进行压栈操作
			signal.push(sign);

		}
		numtemp = "";
		if (num.size() == 2)
			break;

	}//读入两个数字以上继续进行
	while (str[i] != '\0') {
		if (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
			numtemp = numtemp + str[i];
			i++;
			while (str[i] >= '0' && str[i] <= '9' || str[i] == '.') {
				numtemp = numtemp + str[i];
				i++;
			}//得到一个数以后进行压栈操作
			num.push(atof(numtemp.c_str()));
		}



		else
		{
			sign = str[i];
			
			i++;
			switch (sign) {
				char c;

			case'+':
			case'-':
				signal.top(c);
				if (c != '(')
				{
					jisuan(c, num); 
					signal.pop();
				}
				if (signal.size() == 0) { signal.push(sign); break; }
				signal.top(c);

			case'*':
			case'/':if (signal.size() >= 1)signal.top(c); else { cout << "输入格式出错" << endl; break; }
					if (c == '*' || c == '/')
					{
						jisuan(c, num); 
						signal.pop();
					}
					signal.push(sign);
					break;
			case'(':signal.push(sign);
				break;
			case')':signal.top(c);

				jisuan(c, num);
				signal.pop();
				signal.top(c);
				if (c == '(') { signal.pop(); break; }
				else {
					while (c != '(') {
						jisuan(c, num);
						signal.pop();
						if (signal.size() >= 1)signal.top(c); else break;
					}
				}
				if (c == '(')
					signal.pop();


				break;
			case '=':signal.top(c);     //要输等于号
				if (c != '(')
				{
					jisuan(c, num);
					signal.pop();
					while (signal.size() != 0) {
						signal.top(c);
						jisuan(c, num);
						signal.pop();
					}
				}
				break;
			default: break;
			}//退出switch
		}//退出else
	
		numtemp = "";
	}
	
		num.top(result);
		cout << "计算器计算中" << endl;
		cout <<  "result：" << result << endl;

	

}


	      







int main() {
	cout << "请输入类似于3*(1+5.5)=的表达式" << endl;
	Stack<double>num_entry;
	Stack<char>ch_entry;
	
	proity(num_entry, ch_entry);

	return 0;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
