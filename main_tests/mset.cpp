/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mset.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 11:51:13 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/01/30 19:54:39 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include<iostream>

#ifndef LEET
	#define LEET 1337
#endif

#if LEET != 1337
	# include<set>
	namespace CCLIB = std;
#else
	# include"../set.hpp"
	namespace CCLIB = ft;
#endif

#define test(str) std::cout << std::endl << "\e[36********************* < " << str <<" > *********************\e[0m" << std::endl



int main() {


    try { test ("iterator/reverse");

        CCLIB::set<int> s1;

        s1.insert(1);
        s1.insert(2);
        s1.insert(3);
        s1.insert(4);

        CCLIB::set<int> s2(s1.begin(), s1.end());
        CCLIB::set<int> s3(s1);

        std::cout << "*********** s1 < normal > ************" << std::endl;
        for (CCLIB::set<int>::iterator it = s1.begin() ; it != s1.end(); it++)
            std::cout << "\t" << *it;
        std::cout << std::endl;

        std::cout << "*********** s1 < reverse > ************" << std::endl;
        for (CCLIB::set<int>::reverse_iterator it = s1.rbegin() ; it != s1.rend(); it++)
            std::cout << "\t" << *it;
        std::cout << std::endl;

        std::cout << "*********** s2 < normal > ************" << std::endl;
        for (CCLIB::set<int>::iterator it = s2.begin() ; it != s2.end(); it++)
            std::cout << "\t" << *it;
        std::cout << std::endl;

        std::cout << "*********** s2 < reverse > ************" << std::endl;
        for (CCLIB::set<int>::reverse_iterator it = s2.rbegin() ; it != s2.rend(); it++)
            std::cout << "\t" << *it;
        std::cout << std::endl;

        std::cout << "*********** s3 < normal > ************" << std::endl;
        for (CCLIB::set<int>::iterator it = s3.begin() ; it != s3.end(); it++)
            std::cout << "\t" << *it;
        std::cout << std::endl;

        std::cout << "*********** s3 < reverse > ************" << std::endl;
        for (CCLIB::set<int>::reverse_iterator it = s3.rbegin() ; it != s3.rend(); it++)
            std::cout << "\t" << *it;
        std::cout << std::endl;

    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


    try { test ("capacity");

        CCLIB::set<int> s1;
        CCLIB::set<char> s2;
        CCLIB::set<std::string> s3;

        std::cout << "s1 empty : " << s1.empty() << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;
        s1.insert(1);
        std::cout << "s1 empty : " << s1.empty() << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;
        s1.insert(2);
        std::cout << "s1 size : " << s1.size() << std::endl;
        s1.insert(3);
        std::cout << "s1 size : " << s1.size() << std::endl;
        s1.insert(4);
        std::cout << "s1 size : " << s1.size() << std::endl;

    
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


    try { test ("insertion");

        CCLIB::set<int> s1;
        CCLIB::pair<CCLIB::set<int>::iterator, bool> p;

        p = s1.insert(1);
        std::cout << std::boolalpha;
        std::cout << "insert a : " << "[ " << *p.first << " ] | Added : " << p.second << std::endl;
        p = s1.insert(1);
        std::cout << "insert a : " << "[ " << *p.first << " ] | Added : " << p.second << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;

        p = s1.insert(2);
        std::cout << "insert b : " << "[ " << *p.first << " ] | Added : " << p.second << std::endl;
        p = s1.insert(2);
        std::cout << "insert b : " << "[ " << *p.first << " ] | Added : " << p.second << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;

        CCLIB::set<int> s2;
        CCLIB::set<int>::iterator it;
        s2.insert(1);
        s2.insert(2);
        s2.insert(4);
        s2.insert(5);
        s2.insert(6);
        s2.insert(7);
        s2.insert(8);
        std::cout << "*********** s2 before ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = s2.begin() ; it2 != s2.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;

        it = s2.insert(s2.begin(), 3);
        std::cout << "*********** s2 after ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = s2.begin() ; it2 != s2.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;
        std::cout << "insert c : " << "[ " << *it << " ]" << std::endl;
        std::cout << "s2 size : " << s2.size() << std::endl;

        CCLIB::set<int> m3;
        m3.insert(1);
        m3.insert(2);

        std::cout << "*********** m3 before ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = m3.begin() ; it2 != m3.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;
        std::cout << "m3 size : " << m3.size() << std::endl;

        m3.insert(s2.begin(), s2.end());
        std::cout << "*********** m3 after ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = m3.begin() ; it2 != m3.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;
        std::cout << "m3 size : " << m3.size() << std::endl;

    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


    try { test ("erase");

        CCLIB::set<int> s1;

        s1.insert(1);
        s1.insert(2);
        s1.insert(3);
        s1.insert(4);
        s1.insert(5);
        s1.insert(6);

        std::cout << "*********** s1 before ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = s1.begin() ; it2 != s1.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;
        s1.erase(s1.begin());
        std::cout << "*********** s1 after 1 ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = s1.begin() ; it2 != s1.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;
        std::cout << "elements erased : " << s1.erase(4) << std::endl;
        std::cout << "elements erased : " << s1.erase(4) << std::endl;
        std::cout << "*********** s1 after 2 ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = s1.begin() ; it2 != s1.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;
        s1.erase(s1.begin(), ++(++s1.begin()));
        std::cout << "*********** s1 after 3 ************" << std::endl;
        for (CCLIB::set<int>::iterator it2 = s1.begin() ; it2 != s1.end(); it2++)
            std::cout << "\t" << *it2;
        std::cout << std::endl;
        std::cout << "s1 size : " << s1.size() << std::endl;

    
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


    try { test ("swap");

        CCLIB::set<int> foo,bar;

        foo.insert(100);
        foo.insert(200);

        bar.insert(11);
        bar.insert(22);
        bar.insert(33);

        std::cout << "foo contains:\n";
        for (CCLIB::set<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "foo size : " << foo.size() << std::endl;

        std::cout << "bar contains:\n";
        for (CCLIB::set<int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "bar size : " << bar.size() << std::endl;

        foo.swap(bar);

        std::cout << "foo contains:\n";
        for (CCLIB::set<int>::iterator it=foo.begin(); it!=foo.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "foo size : " << foo.size() << std::endl;

        std::cout << "bar contains:\n";
        for (CCLIB::set<int>::iterator it=bar.begin(); it!=bar.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "bar size : " << bar.size() << std::endl;

    
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


    try { test ("clear");

        CCLIB::set<int> m1;

        m1.insert(100);
        m1.insert(200);
        m1.insert(300);

        std::cout << "m1 contains:\n";
        for (CCLIB::set<int>::iterator it=m1.begin(); it!=m1.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "m1 size : " << m1.size() << std::endl;

        m1.clear();
        std::cout << "m1 contains:\n";
        for (CCLIB::set<int>::iterator it=m1.begin(); it!=m1.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "m1 size : " << m1.size() << std::endl;

        m1.insert(1101);
        m1.insert(2202);

        std::cout << "m1 contains:\n";
        for (CCLIB::set<int>::iterator it=m1.begin(); it!=m1.end(); ++it)
            std::cout << *it << '\n';
        std::cout << "m1 size : " << m1.size() << std::endl;

    
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


    try { test ("key_comp , value_comp");

        {
            CCLIB::set<int> m1;

            CCLIB::set<int>::key_compare _comp = m1.key_comp();

            m1.insert(100);
            m1.insert(200);
            m1.insert(300);

            std::cout << "m1 contains:\n";

            int highest = *m1.rbegin();     // key value of last element

            CCLIB::set<int>::iterator it = m1.begin();
            do {
                std::cout << *it << '\n';
            } while ( _comp(*(it++), highest) );

            std::cout << '\n';
        }

        {
            CCLIB::set<int> s2;

            CCLIB::set<int>::value_compare _comp = s2.value_comp();

            for (int i=0; i<=5; i++) s2.insert(i);

            std::cout << "s2 contains:";

            int highest=*s2.rbegin();
            CCLIB::set<int>::iterator it=s2.begin();
            do {
                std::cout << ' ' << *it;
            } while ( _comp(*(++it),highest) );

            std::cout << '\n';
        }

    
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


    try { test ("find");

        CCLIB::set<int> m1;
        CCLIB::set<int>::iterator it;

        m1.insert(50);
        m1.insert(100);
        m1.insert(150);
        m1.insert(200);

        it = m1.find(100);
        if (it != m1.end())
            m1.erase (it);

        std::cout << "elements in m1:" << '\n';
        std::cout << "a => " << *m1.find(50) << '\n';
        std::cout << "c => " << *m1.find(150) << '\n';
        std::cout << "d => " << *m1.find(200) << '\n';

    
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }



    try { test ("count");

        CCLIB::set<char> m1;
        char c;

        m1.insert('a');
        m1.insert('b');
        m1.insert('c');


        for (c='a'; c<'h'; c++) {

            std::cout << c;
            if (m1.count(c)>0)
            std::cout << " is an element of m1.\n";
            else
            std::cout << " is not an element of m1.\n";
        }

    
    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }

    try { test ("lower_bound , upper_bound , equal_range");

        CCLIB::set<int> s1;
        CCLIB::set<int>::iterator low,up;

        for (int i=1; i<10; i++) s1.insert(i*10);

        low=s1.lower_bound (30);
        up=s1.upper_bound (60);

        s1.erase(low,up);

        std::cout << "s1 contains:";
        for (CCLIB::set<int>::iterator it=s1.begin(); it!=s1.end(); ++it)
            std::cout << ' ' << *it;
        std::cout << '\n';


        CCLIB::set<int> m2;

        for (int i=1; i<=5; i++) m2.insert(i*10);

        CCLIB::pair<CCLIB::set<int>::const_iterator,CCLIB::set<int>::const_iterator> ret;
        ret = m2.equal_range(20);

        std::cout << "\tequal_range for existing key: " << '\n';
        std::cout << "lower bound points to: ";
        std::cout << *ret.first << " => " << *ret.second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << *ret.second << " => " << *ret.second << '\n';

        ret = m2.equal_range(35);


        std::cout << "\tequal_range for non-existing key: " << '\n';
        std::cout << "lower bound points to: ";
        std::cout << *ret.first << " => " << *ret.second << '\n';

        std::cout << "upper bound points to: ";
        std::cout << *ret.first << " => " << *ret.second << '\n';

    } catch(const std::exception& e) { std::cerr << e.what() << '\n'; }


}