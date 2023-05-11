#pragma once
#pragma once
#include<iostream>

using namespace std;


class WebSite
{

public:

	class IP
	{
	public:
		IP() {
			counter++;
			srand(IP::counter);
			for (int i = 0; i < 4; i++) {
				this->adress[i] = rand() % 999;
			}
		}

		friend istream& operator>>(istream& input, WebSite::IP& object);
		friend ostream& operator<<(ostream& output, WebSite::IP& object);

		short& operator [](int index)
		{
			if (index < 0 || index>4) {
				cout << "IP index error" << endl;
				index = 0;
			}
			return this->adress[index];
		}

		bool operator==(const IP& other)
		{
			for (int i = 0; i < 4; i++) {
				if (this->adress[i] != other.adress[i])
					return false;
				return true;
			}
		}

		IP& operator=(const IP& other)
		{
			for (short i = 0; i < 4; i++) {
				this->adress[i] = other.adress[i];
			}

			return *this;
		}

		void setIP(short* arr) {
			for (short i = 0; i < 4; i++) {
				this->adress[i] = *(arr + i);
			}
		}

		static int counter;
		short adress[4];
	};

	WebSite()
	{
		srand(time(NULL));
		short size = 4 + rand() % 6;
		char* generate_name;
		generate_name = new char[size];
		for (short i = 0; i < size; i++) {
			if (i == size - 1) {
				generate_name[i] = '\0';
			}
			else
				generate_name[i] = 'a' + rand() % 26;

		}
		this->Domain = generate_name;
	}

	WebSite(string domain)
	{
		this->Domain = domain;
	}

	WebSite(IP adress) {
		this->IP_adress = adress;
		this->Domain = " ";
	}

	WebSite& operator = (const WebSite& other) {
		this->Domain = other.Domain;
		this->IP_adress = other.IP_adress;
		return *this;
	}

	bool operator > (WebSite& other)
	{
		short this_IPsumm = 0, other_IPsumm = 0;
		for (short i = 0; i < 4; i++) {
			this_IPsumm += this->IP_adress[i];
			other_IPsumm += other.IP_adress[i];
		}
		return this_IPsumm > other_IPsumm;

	}

	bool operator < (WebSite& other)
	{
		short this_IPsumm = 0, other_IPsumm = 0;
		for (short i = 0; i < 4; i++) {
			this_IPsumm += this->IP_adress[i];
			other_IPsumm += other.IP_adress[i];
		}
		return this_IPsumm < other_IPsumm;
	}

	string GetDomainFromIP(const IP& IPadress)
	{
		if (this->IP_adress == IPadress)
			return this->Domain;
		return "error";

	}

	friend ostream& operator<<(ostream& output, WebSite& object);

	friend class AssociativeArr;

	void PrintIP() {
		cout << IP_adress;
	}

private:

	string Domain;
	IP IP_adress;

};


int WebSite::IP::counter = 0;


//operator of input and output for class ASSOCIATIVE
ostream& operator<<(ostream& output, WebSite& object) {
	output << "Domain: " << object.Domain << "\nIP: ";
	for (int i = 0; i < 4; i++) {
		output << object.IP_adress[i];
		if (i < 3)
			output << '.';
	}
	return output;
}

//operator of input and output for class IP
ostream& operator<<(ostream& output, WebSite::IP& object) {
	for (int i = 0; i < 4; i++) {
		output << object[i];
		if (i < 3)
			output << '.';
	}
	return output;
}

istream& operator>>(istream& input, WebSite::IP& object) {
	for (int i = 0; i < 4; i++) {
		input >> object[i];
	}
	return input;
}

/// <summary>
/// CLASS ARRAY OF ASSOCIATED OBJECTS
/// </summary>
class AssociativeArr
{
public:
	AssociativeArr(WebSite initial_element) :size(1) {
		arr = new WebSite[1];
		arr[0] = initial_element;
	}

	AssociativeArr(const AssociativeArr& other)
	{
		if (this->arr != nullptr) {
			delete[]this->arr;
		}
		this->size = other.size;
		this->arr = new WebSite[other.size];
		for (int i = 0; i < other.size; i++) {
			this->arr[i] = other.arr[i];
		}
	}

	WebSite& operator[](WebSite::IP IPkey)
	{
		for (int i = 0; i < this->size; i++) {
			if (IPkey == this->arr[i].IP_adress)
				return arr[i];
		}
		cout << "ERROR incorrect input of IP" << endl;
		WebSite error("ERROR of input");
		for (int i = 0; i < 4; i++) {
			error.IP_adress.adress[i] = -1;
		}
		return error;
	}

	//void push_back(Associated& new_element)
	//{
	//	AssociativeArr temp(*this);
	//	delete[]this->arr;
	//	this->arr = new Associated[size + 1];
	//	for (int i = 0; i < this->size; i++) {
	//		this->arr[i] = temp.arr[i];
	//	}
	//	this->arr[size] = new_element;
	//	++this->size;
	//	//cout << "CHEcking: " << endl << "temp: " << temp << endl << "this: " << *this;
	//}

	void operator()(WebSite& new_element)
	{
		AssociativeArr temp(*this);
		delete[]this->arr;
		this->arr = new WebSite[size + 1];
		for (int i = 0; i < this->size; i++) {
			this->arr[i] = temp.arr[i];
		}
		this->arr[size] = new_element;
		++this->size;
	}

	friend ostream& operator<<(ostream& output, AssociativeArr& object);

private:
	WebSite* arr;
	short size;

};

ostream& operator<<(ostream& output, AssociativeArr& object)
{
	for (int i = 0; i < object.size; i++) {
		output << object.arr[i] << endl;
	}
	return output;
}

