#include "AVLTree.h"
#include <string>
using namespace std;

class A {
public :
	int x;
	A(int id = 0) { x = id; }
	friend ostream &operator<<(ostream &out, A a);
	friend bool operator<(const A &a, const A &b);
	friend bool operator>(const A &a, const A &b);
};

ostream &operator<<(ostream &out, A a) {
	cout << a.x;
	return out;
}

bool operator<(const A &a, const A &b) {
	return (a.x < b.x);
}

bool operator>(const A &a, const A &b) {
	return (a.x > b.x);
}

int cmp(const A &a, const A &b) {
	if (a.x > b.x)
		return 1;
	if (a.x < b.x)
		return -1;
	return 0;
}

int main() {
	{
		AVLTree<int> AT1;
		for (int i = 1; i < 8; i++)
			AT1.Insert(i);
		AT1.print();
	}
	{
		A a(3), b(4);
		AVLTree<A> AT1;
		AVLTree<int> AT2(2);
		AVLTree<A> AT3(a, NULL, cmp);
		AVLTree<A, int> AT4(4, 2, cmp);
		// Made the (*cmp) public
		//cout << AT3.cmp(a, b) << endl;
		//cout << AT4.cmp(b, a) << endl;
		AVLTree<A, int> AT5(AT4);
		//cout << AT5.cmp(a, a) << endl

		AT1.addRoot(1);
		AVLTree<A, int> AT6;
		AT6.addRoot(6, 8);
		AT6.setCmp(cmp);
		cout << *(AT6.find(6)) << endl;
		AT6.empty();
	}
	{
		cout << "-------------------------------------------" << endl;
		AVLTree<A, int> AT7(cmp);
		for (int i = 7; i > 0; i--)
			AT7.Insert(i);
		AT7.print();
		AT7.empty();
		cout << "-------------------------------------------" << endl;
		for (int i = 1; i < 8; i++)
			AT7.Insert(i);
		AT7.print();
		AT7.empty();
		cout << "-------------------------------------------" << endl;
		AT7.Insert(3);
		AT7.Insert(1);
		AT7.Insert(2);
		AT7.Insert(5);
		AT7.Insert(4);
		AT7.Insert(-2);
		AT7.Insert(-1);
		AT7.print();
	}
	{
		AVLTree<A, int> AT8(cmp);
		for (int i = 1; i < 16; i++)
			AT8.Insert(i);
		cout << "-------------------------------------------" << endl;
		AT8.print();
		//AT8.Delete(12);
		//cout << "-------------------------------------------" << endl;

		AT8.print();
		for (int i = 1; i <= 8; i++)
			AT8.Delete(i);
		cout << "-------------------------------------------" << endl;
		AT8.print();

		/*for (int i = 15; i >= 8; i--)
			AT8.Delete(i);
		cout << "-------------------------------------------" << endl;
		AT8.print();*/

		/*for (int i = 15; i >= 8; i--)
			AT8.Insert(i);
		cout << "-------------------------------------------" << endl;
		AT8.print();
		for (int i = 1; i < 8; i++)
			AT8.Delete(i);
		cout << "-------------------------------------------" << endl;
		AT8.print();*/

		/*for (int i = 0; i < 8; i++)
			AT8.Delete(AT8.rootID());
		cout << "-------------------------------------------" << endl;
		AT8.print()*/
		
	}
	system("pause");
}
