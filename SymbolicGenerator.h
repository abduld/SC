
#ifndef __SYMBOLIC_GENERATOR_H__
#define __SYMBOLIC_GENERATOR_H__

#include	<vector>
#include	<string>
#include	<ostream>
#include	<iostream>
#include	<sstream>
#include	<cstring>

using namespace std;


template <typename T> static inline string toString(const T & x);

static inline string toString(void) {
	string s = "";
	return s;
}

template <> 
inline string toString(const bool & x) {
  return x ? "true" : "false";
}

template <typename T>
static inline string toString(const T & x) {
	stringstream ss;
	ss << x;
	return ss.str();
}

class SStatement;

class SBase {
public:
	SBase() {}
	~SBase() {}
	virtual inline string toCString() { return ""; }
	virtual inline SBase * toStatement();
	virtual inline bool isStatement() { return false; }
};

class SStatementBase : public SBase {
public:
	inline SBase * toStatement() { return this;}
	inline bool isStatement() { return false; }
};

template <typename T>
class SAtom : public SBase {
private:
	T data;
public:
	inline SAtom(const T & data0) : SBase() { data = data0; }

	inline string toCString() {
		return toString<T>(data);
	}
};

typedef SAtom<bool> SBooleanAtom;
typedef SAtom<int> SIntegerAtom;
typedef SAtom<double> SRealAtom;
typedef SAtom<string> SStringAtom;

class SDeclare : public SBase {
private:
	SBase * type;
	SBase * var;
public:
	SDeclare(SBase * type, SBase * var) : SBase(), type(type), var(var) {}
	~SDeclare() {
		if (type) {
			delete type;
		}
		if (var) {
			delete var;
		}
	}
	inline string toCString() {
		string res = "";
		if (type) {
			res += type->toCString();
			res += " ";
		}
		if (var) {
			res += var->toCString();
		}
		return res;
	}
};

class SAssign : public SBase {
private:
	SBase * to;
	SBase * from;
public:
	SAssign(SBase * to, SBase * from) : SBase(), to(to), from(from) {}
	~SAssign() {
		if (to) {
			delete to;
		}
		if (from) {
			delete from;
		}
	}
	inline string toCString() {
		string res = "";
		if (to) {
			res += to->toCString();
			res += " ";
		}
		res += "= ";
		if (from) {
			res += from->toCString();
		}
		return res;
	}

};

class SStatements : public SStatementBase {
private:
	vector<SBase *> stmts;
public:
	SStatements(SBase * s1) : SStatementBase() {
		stmts.push_back(s1);
	}
	SStatements(SBase * s1, SBase * s2) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
	}
	SStatements(SBase * s1, SBase * s2, SBase * s3) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
	}
	SStatements(SBase * s1, SBase * s2, SBase * s3, SBase * s4) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
		stmts.push_back(s4);
	}
	SStatements(SBase * s1, SBase * s2, SBase * s3, SBase * s4, SBase * s5) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
		stmts.push_back(s4);
		stmts.push_back(s5);
	}
	SStatements(vector<SBase *> stmts) : SStatementBase(), stmts(stmts) {}
	~SStatements() {
		for (vector<SBase *>::iterator iter = stmts.begin(); iter != stmts.end(); iter++) {
			delete *iter;
		}
	}
	inline string toCString() {
		string res = "";
		for (vector<SBase *>::iterator iter = stmts.begin(); iter != stmts.end(); iter++) {
			SBase * val = *iter;
			if (val) {
				val = val->toStatement();
				res += val->toCString();
			}
		}
		return res;
	}
};

typedef SStatements SProgram;

class SStatement : public SStatementBase {
private:
	SBase * stmt;
public:
	SStatement(SBase * stmt) : SStatementBase(), stmt(stmt) {}
	~SStatement() {
		if (stmt) {
			delete stmt;
		}
	}
	inline string toCString() {
		string res = "";
		if (stmt) {
			res += stmt->toCString();	
			if (!stmt->isStatement()) {
				res += ";\n";
			}
		}
		return res;
	}
};

class SBlock : public SStatementBase {
private:
	SBase * body;
public:
	SBlock(SBase * body) : SStatementBase(), body(body) {}
	~SBlock() {
		if (body) {
			delete body;
		}
	}
	inline string toCString() {
		string res = "{\n";
		if (body) {
			if (dynamic_cast<SStatements *>(body)) {
				res += body->toCString();
			} else {
				res += body->toStatement()->toCString();
			}
		}
		res += "}\n";
		return res;
	}
};

class SWhile : public SStatementBase {
private:
	SBase * cond;
	SBase * body;
public:
	SWhile(SBase * cond, SBase * body) : SStatementBase(), cond(cond), body(body) {}
	~SWhile() {
		if (cond) {
			delete cond;
		}
		if (body) {
			delete body;
		}
	}
	inline string toCString() {
		string res = "while (";
		if (cond) {
			res += cond->toCString();
		}
		res += ") ";
		res += (new SBlock(body))->toCString();
		return res;
	}
};

class SDo : public SStatementBase {
private:
	SBase * cond;
	SBase * body;
public:
	SDo(SBase * body, SBase * cond) : SStatementBase(), cond(cond), body(body) {}
	~SDo() {
		if (cond) {
			delete cond;
		}
		if (body) {
			delete body;
		}
	}
	inline string toCString() {
		string res = "do ";
		res += (new SBlock(body))->toCString();
		res += "while (";
		if (cond) {
			res += cond->toCString();
		}
		res += ");";
		return res;
	}
};

class SString : public SBase {
private:
	SBase * str;
public:
	SString(SBase * str) : SBase(), str(str) {}
	SString(string str) : SBase(), str(new SStringAtom(str)) {}
	~SString() {
		if (str) {
			delete str;
		}
	}
	inline string toCString() {
		string res = "\"";
		if (str) {
			/* TODO: escape string */
			res += str->toCString();
		}
		res += "\"";
		return res;
	}
};

class SInclude : public SStatementBase {
private:
	string str;
public:
	SInclude(string str) : SStatementBase(), str(str) {}
	~SInclude() {}
	inline string toCString() {
		string res = "#include ";
		res += (new SString(str))->toCString();
		return res;
	}
};

class SDef : public SStatementBase {
private:
	string str;
public:
	SDef(string str) : SStatementBase(), str(str) {}
	~SDef() {}
	inline string toCString() {
		string res = "#def ";
		res += str;
		return res;
	}
};

class SIfdef : public SStatementBase {
private:
	string str;
public:
	SIfdef(string str) : SStatementBase(), str(str) {}
	~SIfdef() {}
	inline string toCString() {
		string res = "#ifdef ";
		res += str;
		return res;
	}
};

class SIfndef : public SStatementBase {
private:
	string str;
public:
	SIfndef(string str) : SStatementBase(), str(str) {}
	~SIfndef() {}
	inline string toCString() {
		string res = "#ifndef ";
		res += str;
		return res;
	}
};

class SUndef : public SStatementBase {
private:
	string str;
public:
	SUndef(string str) : SStatementBase(), str(str) {}
	~SUndef() {}
	inline string toCString() {
		string res = "#undef ";
		res += str;
		return res;
	}
};

class SIf : public SStatementBase {
private:
	SBase * cond;
	SBase * trueBody;
	SBase * falseBody;
public:
	SIf(SBase * cond, SBase * trueBody) : SStatementBase(), cond(cond), trueBody(trueBody), falseBody(NULL) {}
	SIf(SBase * cond, SBase * trueBody, SBase * falseBody) : SStatementBase(), cond(cond), trueBody(trueBody), falseBody(falseBody) {}
	~SIf() {
		if (cond) {
			delete cond;
		}
		if (trueBody) {
			delete trueBody;
		}
		if (falseBody) {
			delete falseBody;
		}
	}
	inline string toCString() {
		string res = "if (";
		if (cond) {
			res += cond->toCString();
		}
		res += ") ";
		res += (new SBlock(trueBody))->toCString();
		if (falseBody) {
			res += "else ";
			res += (new SBlock(falseBody))->toCString();
		}
		return res;
	}
	inline bool isStatement() {
		return true;
	}
};

static inline int presidence(const string & op) {
	return 0;
}

class SArithmeticOperator : public SBase {
private:
	int pres;
	string op;
	SBase * lhs;
	SBase * rhs;
public:
	SArithmeticOperator(string str, SBase * lhs) : SBase(), op(op), lhs(lhs) {
		pres = presidence(op);
	}
	SArithmeticOperator(string str, SBase * lhs, SBase * rhs) : SBase(), op(op), lhs(lhs), rhs(rhs) {
		pres = presidence(op);
	}
	~SArithmeticOperator() {}
	inline string toCString() {
		string res = "";
		if (lhs) {
		}
		if (rhs) {
		}
		return res;
	}
};


class SComment : public SBase {
};

class SFunction : public SBase {
};

class SCall : public SBase {
};

class SStandardMathCall : public SCall {
};

class SSwitch : public SStatementBase {
};

class SDefault : public SStatementBase {
};

class SLabel: public SStatementBase {
};

class SReturn: public SStatementBase {
};

class STypedef: public SStatementBase {
};

class SCast: public SStatementBase {
};

class SEnum: public SStatementBase {
};

class SPointerType: public SStatementBase {
};

class SStruct: public SStatementBase {
};

class SMember: public SStatementBase {
};

class SUnion: public SStatementBase {
};

class SSizeOf: public SStatementBase {
};

class SBreak: public SStatementBase {
};

class SContinue: public SStatementBase {
};

class SGoto: public SStatementBase {
};

class SPointerMember: public SStatementBase {
};

class SAddress: public SStatementBase {
};

class SDereference: public SStatementBase {
};

class SLine: public SStatementBase {
};

class SPragma: public SStatementBase {
};

class SArray: public SStatementBase {
};

class SError: public SStatementBase {
};


inline SBase * SBase::toStatement() {
	if (isStatement()) {
		return this;
	} else {
		return new SStatement(this);
	}
}

#endif /* __SYMBOLIC_GENERATOR_H__ */


