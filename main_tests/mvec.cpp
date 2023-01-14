/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvec.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdk-meb <sdk-meb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:54:39 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/20 20:11:22 by sdk-meb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<iostream>


#if LEET != 1337
	# include<vector>
	namespace CCLIB = std;
#else
	# include"../vector.hpp"
	namespace CCLIB = ft;
#endif

int main() {


std::cout	<< std::endl << "*************** < constructors , iterators > ******************** " << std::endl; {


	try {

		CCLIB::vector<int> v1;
		CCLIB::vector<int> v2(5, 5);
		CCLIB::vector<int> v3(v2.begin(), v2.end());
		CCLIB::vector<int> v4(v3);

		std::cout << "*********** v1 < normal > ************" << std::endl;
		for (CCLIB::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
			std::cout << "\t" << *it;

		std::cout << std::endl;

		std::cout << "*********** v1 < reverse > ************" << std::endl;
		for (CCLIB::vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;

		std::cout << "*********** v2 < normal > ************" << std::endl;
		for (CCLIB::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;

		std::cout << "*********** v2 < reverse > ************" << std::endl;
		for (CCLIB::vector<int>::reverse_iterator it = v2.rbegin(); it != v2.rend(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;

		std::cout << "*********** v3 < normal > ************" << std::endl;
		for (CCLIB::vector<int>::iterator it = v3.begin(); it != v3.end(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;

		std::cout << "*********** v3 < reverse > ************" << std::endl;
		for (CCLIB::vector<int>::reverse_iterator it = v3.rbegin(); it != v3.rend(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;

		std::cout << "*********** v4 < normal > ************" << std::endl;
		for (CCLIB::vector<int>::iterator it = v4.begin(); it != v4.end(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;

		std::cout << "*********** v4 < reverse > ************" << std::endl;
		for (CCLIB::vector<int>::reverse_iterator it = v4.rbegin(); it != v4.rend(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "********************** < resize > ******************************* " << std::endl; {


	try {

		int values = 10;
		CCLIB::vector<int> vec;

		for (int i = 0; i < values; i++)
			vec.push_back(i);

		std::cout << "size = " << vec.size() << std::endl;
		std::cout << "capacity = " << vec.capacity() << std::endl;

		vec.resize(0);
		std::cout << "size = " << vec.size() << std::endl;
		std::cout << "capacity = " << vec.capacity() << std::endl;
		std::cout << "-----------------------------" << std::endl;
		vec.resize(17);
		std::cout << "size = " << vec.size() << std::endl;
		std::cout << "capacity = " << vec.capacity() << std::endl;

		vec.resize(70);
		std::cout << "size = " << vec.size() << std::endl;
		std::cout << "capacity = " << vec.capacity() << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "******************* < max_size > ******************************** " << std::endl; {


	try {
		CCLIB::vector<int> v(10, 3);

		std::cout << v.max_size() << std::endl;

		for (CCLIB::vector<int>::iterator it = v.begin(); it != v.end(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;

		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
		v.resize(5);
		for (CCLIB::vector<int>::iterator it = v.begin(); it != v.end(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
		v.resize(11);
		for (CCLIB::vector<int>::iterator it = v.begin(); it != v.end(); it++)
			std::cout << "\t" << *it;
		std::cout << std::endl;
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "*************** < size , capacity > ********************* " << std::endl; {


	try {

		int values = 10;
		CCLIB::vector<int> v;

		for (int i = 0; i < values; i++) {

			std::cout << "size = " << v.size() << " | ";
			std::cout << "capacity = " << v.capacity() << std::endl;
			v.push_back(i);
		}
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "********************** < empty  > ******************************* " << std::endl; {


	try {

		int values = 10;
		CCLIB::vector<int> v(5);

		std::cout << "if initialised the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;

		v.resize(0);
		std::cout << "aCCLIBer resize the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;

		for (int i = 0; i < values; i++) v.push_back(i);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++) std::cout << "\t" << *i.base() << std::endl;

		std::cout << "aCCLIBer pushing the vector" << (v.empty() ? " is empty " : " isn't empty ") << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "********************** < reserve  > ***************************** " << std::endl; {
		
	try {

		int value = 5;
		CCLIB::vector<int> v(value);

		std::cout << "capacity = " << v.capacity() << std::endl;

		for (int i = 0; i < value; i++) v.push_back(i);

		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++) std::cout << "\t" << *i << std::endl;
		
		std::cout << "capacity = " << v.capacity() << std::endl;

		v.reserve(value * 3);
		std::cout << "capacity = " << v.capacity() << std::endl;

		v.reserve(value);
		std::cout << "capacity = " << v.capacity() << std::endl;

		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++) std::cout << "\t" << *i << std::endl;

		v.reserve(value * 4);
		std::cout << "capacity = " << v.capacity() << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "******************** < operator []  > *************************** " << std::endl; {


	try
	{
		CCLIB::vector<int> v(101);

		v[100] = 15;
		std::cout << v[100] << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "************************* < at > ******************************** " << std::endl; {


	try {

		CCLIB::vector<int> v(10);

		v.at(8) = 15;
		std::cout << v.at(8) << std::endl;
		std::cout << v.at(9) << std::endl;
		std::cout << v.at(10) << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "********************** < front, back > ************************** " << std::endl; {

	
	try {

		CCLIB::vector<int> v;

		v.push_back(11);
		std::cout << "front = " << v.front() << std::endl;
		std::cout << "back = " << v.back() << std::endl;

		v.push_back(5);
		std::cout << "front = " << v.front() << std::endl;
		std::cout << "back = " << v.back() << std::endl;

		v.front() = 1;
		v.back() = 15;
		std::cout << "front = " << v.front() << std::endl;
		std::cout << "back = " << v.back() << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "*********************** < push_back > *************************** " << std::endl; {

	try {

		int values = 10;
		CCLIB::vector<int> v;

		for (int i = 0; i < values; i++) v.push_back(i);

		for (CCLIB::vector<int>::iterator i = v.begin(); i != v.end(); i++)
			std::cout << "\t" << *i << std::endl;

		v.resize(0);
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;

		v.resize(10);
		for (CCLIB::vector<int>::iterator i = v.begin(); i != v.end(); i++)
			std::cout << "\t" << *i << std::endl;

		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "************************ < pop_back > *************************** " << std::endl; {
	
	try {

		int value = 5;
		CCLIB::vector<int> v;

		for (int i = 0; i < value; i++) v.push_back(i);

		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;

		std::cout << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;

		v.pop_back();
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
		std::cout << "last = " << *(v.end() - 1) << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "************************ < assign > ***************************** " << std::endl; {


	try {

		CCLIB::vector<int> v(10);
		CCLIB::vector<int> v2;

		v.push_back(5);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
		v.assign(15, 10);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "size = " << v[8] << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;

		std::cout << "size 2 = " << v2.size() << std::endl;
		std::cout << "capacity 2 = " << v2.capacity() << std::endl;

		v2.push_back(5);
		v2.assign(v.begin() + 1, v.end() - 1);
		for (CCLIB::vector<int>::iterator i = v2.begin(); i < v2.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;
		std::cout << "size 2 = " << v2.size() << std::endl;
		std::cout << "capacity 2 = " << v2.capacity() << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "************************ < INSERT > *************************** " << std::endl; {


	try {

		CCLIB::vector<int> v(3, 100);
		CCLIB::vector<int>::iterator it;

		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;

		it = v.begin();
		v.insert(it, 200);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;
		it = v.begin() + 2;
		v.insert(v.begin() + 2, 2, 10);
		v.insert(v.begin() + 2, 2, 20);
		v.insert(v.begin() + 2, 2, 30);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;

		it = v.begin();
		CCLIB::vector<int> v1(2, 400);
		v.insert((it + 2), v1.begin(), v1.end());
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "*************************** < eraes > *************************** " << std::endl; {


	try {

		CCLIB::vector<int> v;

		for (int i = 1; i <= 10; i++)
			v.push_back(i);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;
		v.erase(v.begin() + 5);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;

		v.erase(v.begin(), v.begin() + 2);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;

		std::cout << "\t" << *(v.end()) << std::endl;

		v.erase(v.begin() + 2, v.begin() + 5);
		for (CCLIB::vector<int>::iterator i = v.begin(); i < v.end(); i++)
			std::cout << "\t" << *i;
		std::cout << std::endl;

		std::cout << "\t" << *(v.end()) << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "*************************** < swap > *************************** " << std::endl; {


	try {

		CCLIB::vector<int> foo(3, 100);
		CCLIB::vector<int> bar(5, 200);

		std::cout << "foo size = " << foo.size() << '\n';
		std::cout << "foo capacity = " << foo.capacity() << '\n';
		std::cout << "foo addr  = " << &(*foo.begin()) << '\n';
		std::cout << "bar size = " << bar.size() << '\n';
		std::cout << "bar capacity = " << bar.capacity() << '\n';
		std::cout << "bar addr  = " << &(*bar.begin()) << '\n';
		foo.swap(bar);

		std::cout << "foo contains:";
		for (unsigned i = 0; i < foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << '\n';
		std::cout << "foo size = " << foo.size() << '\n';
		std::cout << "foo capacity = " << foo.capacity() << '\n';
		std::cout << "foo addr  = " << &(*foo.begin()) << '\n';

		std::cout << "bar contains:";
		for (unsigned i = 0; i < bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << '\n';
		std::cout << "bar size = " << bar.size() << '\n';
		std::cout << "bar capacity = " << bar.capacity() << '\n';
		std::cout << "bar addr  = " << &(*bar.begin()) << '\n';
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "*************************** < clear > *************************** " << std::endl; {


	try {

		CCLIB::vector<int> v;
		v.push_back(100);
		v.push_back(200);
		v.push_back(300);

		std::cout << "contains:";
		for (unsigned i = 0; i < v.size(); i++)
			std::cout << ' ' << v[i];
		std::cout << std::endl;
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;

		v.clear();
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
		v.push_back(1101);
		v.push_back(2202);

		std::cout << "contains:";
		for (unsigned i = 0; i < v.size(); i++)
			std::cout << ' ' << v[i];
		std::cout << std::endl;
		std::cout << "size = " << v.size() << std::endl;
		std::cout << "capacity = " << v.capacity() << std::endl;
		std::cout << "end = " << *v.end() << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

std::cout	<< std::endl << "********************** < non_members fun > ********************** " << std::endl; {


	try {

		CCLIB::vector<int> foo(3, 100);
		CCLIB::vector<int> bar(2, 200);

		if (foo == bar)
			std::cout << "foo and bar are equal\n";
		if (foo != bar)
			std::cout << "foo and bar are not equal\n";
		if (foo < bar)
			std::cout << "foo is less than bar\n";
		if (foo > bar)
			std::cout << "foo is greater than bar\n";
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar\n";
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar\n";

		foo.swap(bar);
		if (foo == bar)
			std::cout << "foo and bar are equal\n";
		if (foo != bar)
			std::cout << "foo and bar are not equal\n";
		if (foo < bar)
			std::cout << "foo is less than bar\n";
		if (foo > bar)
			std::cout << "foo is greater than bar\n";
		if (foo <= bar)
			std::cout << "foo is less than or equal to bar\n";
		if (foo >= bar)
			std::cout << "foo is greater than or equal to bar\n";

		std::cout << "foo: ";
		for (unsigned i = 0; i < foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << std::endl;
		std::cout << "bar: ";
		for (unsigned i = 0; i < bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << std::endl;
		std::swap(foo, bar);
		std::cout << "foo: ";
		for (unsigned i = 0; i < foo.size(); i++)
			std::cout << ' ' << foo[i];
		std::cout << std::endl;
		std::cout << "bar: ";
		for (unsigned i = 0; i < bar.size(); i++)
			std::cout << ' ' << bar[i];
		std::cout << std::endl;
	}
	catch (const std::exception &e) { std::cerr << e.what() << '\n'; }
}

}
