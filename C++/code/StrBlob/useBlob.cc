#include <iostream>
using std::cout;
using std::endl;

#include "StrBlob.h"

int main()
{
	StrBlob b1;
	{
		StrBlob b2({"a", "an", "the"});
		b1 = b2;
		b2.push_back("about");
		cout << b2.size() << endl;
	}
	cout << b1.size() << endl;

	for (auto it = b1.begin(); it != b1.end(); ++it)
		cout << *it << endl;

	cout << "----------------------------" << endl;

	const StrBlob cb1({"a", "an", "the"});
	cb1.push_back("about");
	cb1.push_back("hhh");
	cb1.pop_back();
	cout << cb1[2] << endl;
	for (auto it = cb1.cbegin(); it != cb1.cend(); ++it)
		cout << *it << endl;

	return 0;
}
