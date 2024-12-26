#pragma once
#include <string>

class User final
{
	std::string id_;
	int sum_;
public:
	User(std::string id) noexcept: id_(std::move(id)), sum_(0){}
	int getSum() const noexcept
	{
		return sum_;
	}
	std::string getId() const noexcept
	{
		return id_;
	}
	void addPay(int pay) noexcept
	{
		sum_ += pay;
	}
};
