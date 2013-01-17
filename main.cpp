
#include	"SymbolicGenerator.h"

int main(void) {
	SBase * s = new SBlock(
		new SStatements(
			new SStatements(
				new SDeclare(new SStringAtom("int"), new SStringAtom("b")),
				new SAssign(new SStringAtom("b"), new SIntegerAtom(1))
			)
		)
	);
	string res = s->toCString();
	cout << res;
	return 0;
}

