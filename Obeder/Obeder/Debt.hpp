#pragma once
#include "User.hpp"

class Debt final
{
	User debtor_;
	User borrower_;
	int sum_;
public:
	Debt(User debtor, User borrower, int sum) noexcept:
		debtor_(std::move(debtor)), borrower_(std::move(borrower)), sum_(sum) {}
	const User& getDebtor() const noexcept
	{
		return debtor_;
	}
	const User& getBorrower() const noexcept
	{
		return borrower_;
	}
	int getSum() const noexcept
	{
		return sum_;
	}
};
