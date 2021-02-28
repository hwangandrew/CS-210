/*
 * Account.h
 *
 *  Created on: Feb 5, 2021
 *      Author: Andrew Hwang
 */

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <string>
using namespace std;

class Account {
	public:
		void GetInput();
		void SetBalance();
		void SetMonthlyDeposit();
		void SetInterest();
		void SetYears();
		void ShowInterestTables();
		void InterestNoDeposit();
		void InterestWithDeposit();

	private:
		double balance;
		double deposit;
		double interest;
		int years;

};

#endif /* ACCOUNT_H_ */
