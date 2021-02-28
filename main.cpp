/*
 * 		Project Two
 * 		SNHU CS-210-T3184
 *
 * 		Author: Andrew Hwang
 * 		Date: 2/7/21
 */

#include <iostream>
using namespace std;

#include "Account.h"

int main() {

	Account test; 				//creates account
	test.GetInput(); 			//gathers input from user
	test.ShowInterestTables(); 	//generates and displays two tables

	return 0;
}
