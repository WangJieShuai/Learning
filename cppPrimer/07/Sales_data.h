
#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

struct Sales_data{
	string isbn() const { return bookNo;};
	double avg_price() const;
	Sales_data& combine(const Sales_data &rhs);

	string bookNo;
	unsigned units_sold = 0;
	double revenue = 0.0;
};

Sales_data
&Sales_data::combine(const Sales_data &rhs) {
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

double 
Sales_data::avg_price() const {
	if (units_sold) {
		return revenue/units_sold;
	}
	else {
		return 0;
	}
}

istream
&read(istream &is, Sales_data &item) {
	double price;
	is >> item.bookNo >> item.units_sold >> price; 
	item.revenue = price * item.units_sold; // item can't be const, if it is const object, >> change bookNo's value is legal??
	return is;
}

ostream
&print(ostream &os, const Sales_data &item) {
	os << item.bookNo << " " << item.units_sold << " " << item.revenue 
		<< " " << item.avg_price();
	return os;
}

Sales_data
add(Sales_data &lhs, Sales_data&rhs) {
	Sales_data sum;
	sum = lhs;
	lhs.combine(rhs);
	return sum;
}