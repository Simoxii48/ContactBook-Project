#pragma once

#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
using namespace std;

namespace validation
{
	int readValidateNumber(int from, int to, string message)
	{
		int number = 0;
		cout << "\n" << right << setw(5) << " " << message;

		while (!(cin >> number) || number < from || number > to)
		{
			cout << endl << right << setw(5) << " " << "Invalid (Range / Datatype) please enter a Number from " << from << " To " << to << " : ";
			
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		return number;
	}
}