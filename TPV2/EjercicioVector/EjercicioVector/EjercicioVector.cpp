// Andres Garcia Navarro
// Pablo Iglesias Rodrigo

// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <vector>

int num_of_new_int = 0;
int num_of_delete = 0;
int num_of_const_d = 0;
int num_of_const_c = 0;
int num_of_const_m = 0;
int num_of_assig_c = 0;
int num_of_assig_m = 0;
int num_of_dest = 0;

void reset_stats() {
	num_of_new_int = 0;
	num_of_delete = 0;
	num_of_const_d = 0;
	num_of_const_c = 0;
	num_of_const_m = 0;
	num_of_assig_c = 0;
	num_of_assig_m = 0;
	num_of_dest = 0;
}

void print_stats() {
	std::cout << "--------------" << std::endl;
	std::cout << "new int: " << num_of_new_int << std::endl; // objeto creado(new)
	std::cout << "del int: " << num_of_delete << std::endl; // objeto eliminado
	std::cout << "const_d: " << num_of_const_d << std::endl; // destructora del objeto creado
	std::cout << "const_c: " << num_of_const_c << std::endl; // objeto copiado
	std::cout << "const_m: " << num_of_const_m << std::endl; // obejto movido
	std::cout << "assig_c: " << num_of_assig_c << std::endl; // objeto asignado por constructora normal
	std::cout << "assig_m: " << num_of_assig_m << std::endl; // objeto asignado por movimiento
	std::cout << "--------------" << std::endl;

}

class A {
public:
	int* p;

	A(int n) {
		p = new int(n);
		num_of_new_int++;
		num_of_const_d++;
		std::cout << "Def. const. *p=" << *p << std::endl;
	}

	A(const A& o) {
		p = new int(*o.p);
		num_of_new_int++;
		num_of_const_c++;
		std::cout << "Copy. const. *p=" << *p << ", copied " << &o << " to "
			<< this << std::endl;
	}

	/*A(A&& o) noexcept {
		p = o.p;
		o.p = nullptr;
		num_of_const_m++;
		std::cout << "Move. const. *p=" << *p << ", moved " << &o << " to "
			<< this << std::endl;
	}*/

	A& operator=(const A& o) {
		if (p != nullptr) { // we have something in p, we should release it first
			delete p;
			num_of_delete++;
		}

		if (o.p == nullptr)
			p = nullptr;
		else
			p = new int(*o.p);

		num_of_new_int++;
		num_of_assig_c++;
		std::cout << "Copy. assign. *p=" << *p << ", copied " << &o << " to "
			<< this << std::endl;
		return *this;
	}

	A& operator=(A&& o) noexcept {
		if (p != nullptr) { // we have something in p, we should release it first
			delete p;
			num_of_delete++;
		}
		p = o.p;
		o.p = nullptr;
		num_of_assig_m++;
		std::cout << "Move. assign. *p=" << *p << ", moved " << &o << " to "
			<< this << std::endl;
		return *this;
	}

	~A() {
		std::cout << "Dtor." << std::endl;
		num_of_dest++;
		if (p != nullptr) {
			num_of_delete++;
			delete p;
		}
	}

	operator int() const {
		return *p;
	}
};

template<typename T>
void print_vector(const std::vector<T>& v) {
	for (const T& a : v) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
}

void test0() {
	/*std::vector<A> v;
	v.push_back(A(1));*/

	/*std::vector<A> v;
	A x(1);
	v.push_back(x);*/

	std::vector<A> v;
	A x(1);
	v.push_back(std::move(x));

	/*std::vector<A> v;
	v.emplace_back(1);*/
}


int main(int, char**) {
	reset_stats();
	test0();
	print_stats();

	return 0;
}


