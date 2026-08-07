#include "jit.h"

int	main(void) {

	for (char c = 'h'; c <= 'z'; ++c) {
		void (*f)() = compile(genTestFile, &c);
		f();
	}
}
