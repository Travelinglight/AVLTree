#include "AVLTree.h"
#include <string>
using namespace std;
class A {
public :
	int x;
	A(int id = 0) { x = id; }
	friend ostream &operator<<(ostream &out, A a);
};

ostream &operator<<(ostream &out, A a) {
	cout << a.x;
	return out;
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
		for (int i = 1; i < 8; i++)
			AT7.insert(i);
	}
	system("pause");
}