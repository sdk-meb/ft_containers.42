/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mstk.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mes-sadk <mes-sadk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:55:55 by mes-sadk          #+#    #+#             */
/*   Updated: 2023/02/04 12:06:59 by mes-sadk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"test.hpp"
# include<vector.hpp>

void stk_test() {

    try { test("constructor");

        ft::vector<int> v1(7, 89);
        std::vector<int> v3(7, 89);

        CCLIB::stack<int, ft::vector<int> > s1(v1);
        CCLIB::stack<int, std::vector<int> > s3(v3);

        CCLIB::stack<int, ft::vector<int> > s11(s1);
        CCLIB::stack<int, std::vector<int> > s33(v3);

    } catch (const std::exception &e) { std::cerr << e.what() << std::endl; }


    try { test("empty");

        ft::vector<int> v1;
        std::vector<int> v2;
        ft::vector<int> v3(7, 89);
        std::vector<int> v4(7, 89);

        CCLIB::stack<int, ft::vector<int> > s1(v1);
        CCLIB::stack<int, std::vector<int> > s2(v2);
        CCLIB::stack<int, ft::vector<int> > s3(v3);
        CCLIB::stack<int, std::vector<int> > s4(v4);

        std::cout << std::boolalpha;
        std::cout << "s1 is empty ? " << s1.empty() << std::endl;
        std::cout << "s2 is empty ? " << s2.empty() << std::endl;
        std::cout << "s3 is empty ? " << s3.empty() << std::endl;
        std::cout << "s4 is empty ? " << s4.empty() << std::endl;

    } catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    try { test("size");

        ft::vector<int> v1;
        std::vector<int> v2(40);
        ft::vector<int> v3(7, 89);
        std::vector<int> v4(7, 89);

        CCLIB::stack<int, ft::vector<int> > s1(v1);
        CCLIB::stack<int, std::vector<int> > s2(v2);
        CCLIB::stack<int, ft::vector<int> > s3(v3);
        CCLIB::stack<int, std::vector<int> > s4(v4);

        std::cout << "s1 size = " << s1.size() << std::endl;
        std::cout << "s2 size = " << s2.size() << std::endl;
        std::cout << "s3 size = " << s3.size() << std::endl;
        std::cout << "s4 size = " << s4.size() << std::endl;

    } catch (const std::exception &e) { std::cerr << e.what() << std::endl;; }

    try { test("top");

        ft::vector<int> v1;
        std::vector<int> v2(40);
        ft::vector<int> v3(7, 89);
        std::vector<int> v4(7, 89);

        CCLIB::stack<int, ft::vector<int> > s1(v1);
        CCLIB::stack<int, std::vector<int> > s2(v2);
        CCLIB::stack<int, ft::vector<int> > s3(v3);
        CCLIB::stack<int, std::vector<int> > s4(v4);

#if SG > 1
        std::cout << "s1 top = " << s1.top() << std::endl;
#endif
        std::cout << "s2 top = " << s2.top() << std::endl;
        std::cout << "s3 top = " << s3.top() << std::endl;
        std::cout << "s4 top = " << s4.top() << std::endl;

    } catch (const std::exception &e) { std::cerr << e.what() << std::endl;; }

    try { test("push");

        ft::vector<int> v1;
        std::vector<int> v2(30);

        CCLIB::stack<int, ft::vector<int> > s1(v1);
        CCLIB::stack<int, std::vector<int> > s2(v2);

        std::cout << "s2 top = " << s2.top() << std::endl;

        s1.push(1);
        s2.push(2);
        std::cout << "s1 top = " << s1.top() << std::endl;
        std::cout << "s2 top = " << s2.top() << std::endl;

    } catch (const std::exception &e) { std::cerr << e.what() << std::endl; }

    try { test("pop");

        ft::vector<int> v1;
        std::vector<int> v2(20);

        CCLIB::stack<int, ft::vector<int> > s1(v1);
        CCLIB::stack<int, std::vector<int> > s2(v2);

#if SG > 2
        std::cout << "s1 top = " << s1.top() << std::endl;
#endif
        std::cout << "s2 top = " << s2.top() << std::endl;

        s1.push(55);
        s2.push(66);
        std::cout << "s1 top = " << s1.top() << std::endl;
        std::cout << "s2 top = " << s2.top() << std::endl;

        s1.push(74);
        s2.push(84);
        std::cout << "s1 top = " << s1.top() << std::endl;
        std::cout << "s2 top = " << s2.top() << std::endl;

        s1.pop();
        s2.pop();
        std::cout << "s1 top = " << s1.top() << std::endl;
        std::cout << "s2 top = " << s2.top() << std::endl;

    } catch (const std::exception &e) { std::cerr << e.what() << std::endl;; }

    try { test("fun members");

        ft::vector<int> foo1(5, 199);
        ft::vector<int> bar1(5, 199);

        std::vector<int> foo2(9, 78);
        std::vector<int> bar2(9, 78);

        CCLIB::stack<int, ft::vector<int> > s1(foo1);
        CCLIB::stack<int, ft::vector<int> > s2(bar1);

        CCLIB::stack<int, std::vector<int> > s3(foo2);
        CCLIB::stack<int, std::vector<int> > s4(bar2);

        if (s1 == s2) std::cout << "s1 and s2 are equal\n";
        if (s1 not_eq s2) std::cout << "s1 and s2 are not equal\n";
        if (s1 < s2) std::cout << "s1 is less than s2\n";
        if (s1 > s2) std::cout << "s1 is greater than s2\n";
        if (s1 <= s2) std::cout << "s1 is less than or equal to s2\n";
        if (s1 >= s2) std::cout << "s1 is greater than or equal to s2\n";

        if (s3 == s4) std::cout << "s3 and s4 are equal\n";
        if (s3 not_eq s4) std::cout << "s3 and s4 are not equal\n";
        if (s3 < s4) std::cout << "s3 is less than s4\n";
        if (s3 > s4) std::cout << "s3 is greater than s4\n";
        if (s3 <= s4) std::cout << "s3 is less than or equal to s4\n";
        if (s3 >= s4) std::cout << "s3 is greater than or equal to s4\n";

    } catch (const std::exception &e) { std::cerr << e.what() << std::endl;; }

}

