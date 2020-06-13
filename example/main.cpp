#include <iostream>
#include <memory>

#include "emitter.h"

struct A {
	void foo(const std::string & s) {
		std::cout << "sending " << s << '\n';
	}
};

struct B {
	void bar(const std::string & s) {
		std::cout << "received "<< s << '\n';
	}
};

int main(int argc, char * argv[])
{
	std::unique_ptr<A> a{std::make_unique<A>()};
	std::unique_ptr<B> b{std::make_unique<B>()};
	auto emitter = Connector::connect(a.get(), &A::foo, b.get(), &B::bar);
	emitter.emit("some shit");

	return EXIT_SUCCESS;
}