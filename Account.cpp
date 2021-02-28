/*
 * Account.cpp
 *
 *  Created on: Feb 5, 2021
 *      Author: Andrew Hwang
 */

#include <iostream>
#include <iomanip> 		//setw
#include <stdexcept> 	//to use try/catch
#include <limits> 		//to use numeric_limits<streamsize>::max()
using namespace std;

#include "Account.h"

// Initial display to get input from user
void Account::GetInput() {

	cout << setw(33) << setfill('*') << "*" << endl;
	cout << "********** Data Input ***********" << endl;

	/*
	 * "Initial Investment Amount:"
	 *  The cout/text display is expressed in the function so that the user can be
	 *  re-prompted to enter a valid entry if error checks catch invalid entries
	 */
	SetBalance();

	/*
	 *  "Monthly Deposit:"
	 *  The cout/text display is written in the function so that the user can be
	 *  re-prompted to enter a valid entry if error checks catch invalid entries.
	 */
	SetMonthlyDeposit();

	/*
	 *  "Annual Interest:"
	 *  The cout/text display is written in the function so that the user can be
	 *  re-prompted to enter a valid entry if error checks catch invalid entries.
	 */
	SetInterest();

	/*
	 *  "Number of years:"
	 *  The cout/text display is written in the function so that the user can be
	 *  re-prompted to enter a valid entry if error checks catch invalid entries.
	 */
	SetYears();

	cout << endl;

}

//sets starting balance and utilizes try/catch statements to check for errors
void Account::SetBalance(){
	double input;
	char loopBreak = 'a'; //start loop condition

	// this loop will continue until a valid entry is entered
	while (loopBreak != 'q') {
		try {
			cout << "Initial Investment Amount: $";
			cin >> input;

			//error checking, non-negative number
			if (input < 0) {
				throw runtime_error("Negative numbers not allowed.");
			}

			//error checking, numerical entry only
			if (!cin.good()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw runtime_error("Numerical entry is required.");
			}

			balance = input;
			loopBreak = 'q'; //to break loop if no errors were caught
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
		}
	}
}

//sets deposit amount and utilizes try/catch statements to check for errors
void Account::SetMonthlyDeposit(){
	double input;
	char loopBreak = 'a'; //start loop condition

	// this loop will continue until a valid entry is entered
	while (loopBreak != 'q') {
		try {
			cout << "Monthly Deposit: $";
			cin >> input;

			//error checking, non-negative number
			if (input < 0) {
				throw runtime_error("Negative numbers not allowed.");
			}

			//error checking, numerical entry
			if (!cin.good()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw runtime_error("Numerical entry is required.");
			}

			deposit = input;
			loopBreak = 'q'; //to break loop if no errors were caught
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
		}
	}
}

//sets interest rate and uses try/catch statements to check for errors
void Account::SetInterest() {
	int input;
	char loopBreak = 'a'; //start loop condition

	// this loop will continue until a valid entry is entered
	while (loopBreak != 'q') {
		try {
			cout << "Annual Interest: %";
			cin >> input;

			//error checking, non-negative number
			if (input < 0) {
				throw runtime_error("Negative numbers not allowed.");
			}

			//error checking, numerical entry
			if (!cin.good()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw runtime_error("Numerical entry is required.");
			}

			//error checking, cannot exceed 100% (most banks will not even give 5%)
			if (input > 100) {
				throw runtime_error("Interest cannot exceed 100% - This is not bitcoin.");
			}

			interest = input;
			loopBreak = 'q'; //to break loop if no errors were caught
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
		}
	}
}

//sets years to be calculated and uses try/catch statements to check for errors
void Account::SetYears(){
	int input;
	char loopBreak = 'a'; //start loop condition

	// this loop will continue until a valid entry is entered
	while (loopBreak != 'q') {
		try {
			cout << "Number of years: ";
			cin >> input;

			//error checking, non-negative number
			if (input < 0) {
				throw runtime_error("Negative numbers not allowed.");
			}

			//error checking, numerical entry
			if (!cin.good()){
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				throw runtime_error("Numerical entry is required.");
			}

			years = input;
			loopBreak = 'q'; //to break loop if no errors were caught
		}
		catch (runtime_error& excpt) {
			cout << excpt.what() << endl;
		}
	}
}

//function to display the two tables showing with or without monthly deposits
void Account::ShowInterestTables(){
	//header for report without additional monthly deposits
	cout << setw(60) << setfill('=') << "=" << endl;
	cout << "  Balance and Interest Without Additional Monthly Deposits" << endl;
	cout << setw(60) << setfill('=') << "=" << endl;
	cout << "Year\t Year End Balance \t Year End Earned Interest" << endl;
	cout << setw(60) << setfill('-') << "-" << endl;
	InterestNoDeposit();
	cout << endl;

	//header for report with additional monthly deposits
	cout << setw(60) << setfill('=') << "=" << endl;
	cout << "    Balance and Interest With Additional Monthly Deposits" << endl;
	cout << setw(60) << setfill('=') << "=" << endl;
	cout << "Year\t Year End Balance \t Year End Earned Interest" << endl;
	cout << setw(60) << setfill('-') << "-" << endl;
	InterestWithDeposit();
}

/*
 *  The calculations for no monthly deposits are more straight forward. We find the interest
 *  amount by multiplying the balance * interest rate (as a decimal) and add it to the balance.
 *  Each year is displayed with each iteration of the for loop. Of note, we declared a new
 *  variable to hold and modify the balance amount. At first I tried using the same variable
 *  as the class (balance), but found that it effects the other functions since I am directly
 *  modifying that variable.
 */
void Account::InterestNoDeposit() {
	//initialized variables to be used
	int i;
	double calcBalance = balance;
	double interestTotal;

	for (i = 1; i <= years; i++){
		interestTotal = calcBalance * interest / 100;
		calcBalance = calcBalance + interestTotal;

		//output display for user - alternatively we could have used printf statements
		cout << "   " << i << "\t\t$";
		cout << fixed << setprecision(2) << calcBalance;
		cout << "\t\t\t\t$";
		cout << fixed << setprecision(2) << interestTotal << endl;

		interestTotal = 0; //resets interest total for next iteration of loop
	}
}

/*
 *  The calculations for monthly deposits are below. We have to utilize multiple loops and also
 *  vectors. The first outer for loop is to use for the user display in terms of years.
 *  The inner loop is to calculate monthly totals, monthly interest, and total interest for the year.
 */
void Account::InterestWithDeposit() {
	//initialized variables
	int i;
	int j;
	double calcBalance = balance;
	double compoundInterest;
	double interestTotal;

	for (i = 1; i <= years; i++){
		//this loop calculates the new monthly totals, monthly interest, and total interest for the year
		for (j = 1; j <= 12; j++){
			calcBalance = calcBalance + deposit;
			compoundInterest = calcBalance * interest / 100 / 12;
			calcBalance = calcBalance + compoundInterest;
			interestTotal += compoundInterest;
		}

		//output display for user - alternatively we could have used printf statements
		cout << "   " << i << "\t\t$";
		cout << fixed << setprecision(2) << calcBalance;
		cout << "  \t\t\t$";
		cout << fixed << setprecision(2) << interestTotal << endl;

		//resets variables for next iteration of loop
		interestTotal = 0;
		compoundInterest = 0;
	}
}
