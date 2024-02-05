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
	std::cout << "delete int: " << num_of_delete << std::endl; // objeto eliminado
	std::cout << "constructor_default: " << num_of_const_d << std::endl; // constructora del objeto creado
	std::cout << "construtora_copia: " << num_of_const_c << std::endl; // objeto copiado
	std::cout << "constructora_move: " << num_of_const_m << std::endl; // obejto movido
	std::cout << "assig_copia: " << num_of_assig_c << std::endl; // objeto asignado por copia
	std::cout << "assig_move: " << num_of_assig_m << std::endl; // objeto asignado por movimiento
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
		std::cout << "Move. assign. *p=" << *p << ", moved " << &o << " to " << this << std::endl;
		return *this;
	}

	~A() {
		std::cout << "Destructor." << std::endl;
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
	std::vector<A> v;
	v.push_back(A(1));

	std::cout << "------------BUENOS DIAS------------" << std::endl;
}

void test1() {
	std::vector<A> v;
	A x(1);
	v.push_back(x);

	std::cout << "------------BUENOS DIAS------------" << std::endl;
}

void test2() {
	std::vector<A> v;
	A x(1);
	v.push_back(std::move(x));

	std::cout << "------------BUENOS DIAS------------" << std::endl;
}

void test3() {
	std::vector<A> v;
	v.emplace_back(1);

	std::cout << "------------BUENOS DIAS------------" << std::endl;
}

void test4() {
	std::vector<A> v;

	for (int i = 0; i < 10; i++) {
		std::cout << "# adding " << i << " using emplace_back" << std::endl;
		if (v.capacity() == v.size()) {
			std::cout << "# The vector is about to be resized!" << std::endl;
		}
		v.emplace_back(i);
	}
}

void test5() {
	std::vector<A> v;
	v.reserve(20);
	for (int i = 0; i < 10; i++) {
		std::cout << "# adding " << i << " using emplace_back" << std::endl;
		if (v.capacity() == v.size()) {
			std::cout << "# The vector is about to be resized!" << std::endl;
		}
		v.emplace_back(i);
	}
}

int main(int, char**) {
	reset_stats();

	test0();
	test1();
	test2();
	test3();
	test4();
	test5();

	print_stats();

	return 0;
}


