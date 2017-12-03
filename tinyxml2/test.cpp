#include <iostream>
#include <thread>
using namespace std;
void A() {
	cout << "A";
}
void B() {
	cout << "B";
}
typedef void (*cmds)();

int maasdin() {
	cmds a[] = {A, B};
	a[0]();
}