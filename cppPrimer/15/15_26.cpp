#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Quote {
public:
	Quote() { 
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Quote(const string& s, double p) 
		: bookNo(s), price(p) 
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Quote(const Quote& rhs) 
		: bookNo(rhs.bookNo), price(rhs.price) 
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Quote& operator=(const Quote& rhs) 
	{
		cout << __PRETTY_FUNCTION__ << endl;

		bookNo = rhs.bookNo;
		price = rhs.price;

		return *this;
	}

	Quote(Quote&& rhs) noexcept
		: bookNo(std::move(rhs.bookNo)), price(std::move(rhs.price)) 
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Quote& operator=(Quote&& rhs) noexcept
	{
		cout << __PRETTY_FUNCTION__ << endl;

		bookNo = std::move(rhs.bookNo);
		price = std::move(rhs.price);

		return *this;
	}

	virtual Quote* clone() const &{
		return new Quote(*this);
	}

	virtual Quote* clone() && {
		return new Quote(std::move(*this));
	}

	virtual ~Quote() 
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	const string& isbn() const { return bookNo; }

	virtual double net_price(size_t n) const {
		return n * price;
	}

protected:
	double price = 0.0;
private:
	string bookNo;
};

class Bulk_Quote : public Quote
{
public:
	Bulk_Quote() : Quote() 
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Bulk_Quote(const string& s, double p, double disc, size_t min_qty) 
		: Quote(s, p), discount(disc), min_qty(min_qty) 
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Bulk_Quote(const Bulk_Quote& rhs) 
		: Quote(rhs), discount(rhs.discount), min_qty(rhs.min_qty) 
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Bulk_Quote& operator=(const Bulk_Quote& rhs) {
		cout << __PRETTY_FUNCTION__ << endl;

		Quote::operator=(rhs);
		discount = rhs.discount;
		min_qty = rhs.min_qty;
	
		return *this;
	}

	Bulk_Quote(Bulk_Quote&& rhs) noexcept 
		: Quote(rhs), discount(std::move(rhs.discount)), min_qty(std::move(rhs.min_qty))
	{
		cout << __PRETTY_FUNCTION__ << endl;
	}

	Bulk_Quote& operator=(Bulk_Quote &&rhs) noexcept 
	{
		cout << __PRETTY_FUNCTION__ << endl;

		Quote::operator=(rhs);
		discount = std::move(rhs.discount);
		min_qty = std::move(rhs.min_qty);

		return *this;
	}

	~Bulk_Quote() override {
		cout << __PRETTY_FUNCTION__ << endl;
	};

	virtual Bulk_Quote* clone() const & override {
		return new Bulk_Quote(*this);
	}

	virtual Bulk_Quote* clone() && override {
		return new Bulk_Quote(std::move(*this));
	}

	double net_price(size_t n) const override {
		if (n <= min_qty) {
			return n * price;
		}
		else {
			return n * price * (1 - discount);
		}
	}

private:
	double discount = 0.0;
	size_t min_qty;
};

double
print_total(ostream &os, const Quote &item, size_t n) 
{
	double price = item.net_price(n);

	os << "ISBN: " << item.isbn() << " #sold: " << n << "due: " << price << endl;

	return price;
}

