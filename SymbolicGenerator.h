
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
	SStatements(SBase * s1, SBase * s2, SBase * s3, SBase * s4, SBase * s5,
				SBase * s6) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
		stmts.push_back(s4);
		stmts.push_back(s5);
		stmts.push_back(s6);
	}
	SStatements(SBase * s1, SBase * s2, SBase * s3, SBase * s4, SBase * s5,
				SBase * s6, SBase * s7) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
		stmts.push_back(s4);
		stmts.push_back(s5);
		stmts.push_back(s6);
		stmts.push_back(s7);
	}
	SStatements(SBase * s1, SBase * s2, SBase * s3, SBase * s4, SBase * s5,
				SBase * s6, SBase * s7, SBase * s8) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
		stmts.push_back(s4);
		stmts.push_back(s5);
		stmts.push_back(s6);
		stmts.push_back(s7);
		stmts.push_back(s8);
	}
	SStatements(SBase * s1, SBase * s2, SBase * s3, SBase * s4, SBase * s5,
				SBase * s6, SBase * s7, SBase * s8, SBase * s9) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
		stmts.push_back(s4);
		stmts.push_back(s5);
		stmts.push_back(s6);
		stmts.push_back(s7);
		stmts.push_back(s8);
		stmts.push_back(s9);
	}
	SStatements(SBase * s1, SBase * s2, SBase * s3, SBase * s4, SBase * s5,
				SBase * s6, SBase * s7, SBase * s8, SBase * s9, SBase * s10) : SStatementBase() {
		stmts.push_back(s1);
		stmts.push_back(s2);
		stmts.push_back(s3);
		stmts.push_back(s4);
		stmts.push_back(s5);
		stmts.push_back(s6);
		stmts.push_back(s7);
		stmts.push_back(s8);
		stmts.push_back(s9);
		stmts.push_back(s10);
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
		res += ");\n";
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
		res += "\n";
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
		res += "\n";
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
		res += "\n";
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
		res += "\n";
		return res;
	}
};

class SIf : public SStatementBase {
private:
	SBase * cond;
	SBase * trueBody;
	SBase * falseBody;
public:
	SIf(SBase * cond, SBase * trueBody) : SStatementBase(),
										  cond(cond),
										  trueBody(trueBody),
										  falseBody(NULL) {}
	SIf(SBase * cond, SBase * trueBody, SBase * falseBody) :
										  SStatementBase(),
										  cond(cond),
										  trueBody(trueBody),
										  falseBody(falseBody) {}
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
private:
	SBase * cmt;
public:
	SComment(string cmt0) : SBase() {
		cmt = new SStringAtom(cmt0);
	}
	SComment(SBase * cmt) : SBase(), cmt(cmt) {}
	~SComment() {
		if (cmt) {
			delete cmt;
		}
	}
	inline string toCString() {
		string res = "/*";
		if (cmt) {
			res += cmt->toCString();
		}
		res += "*/\n";
		return res;
	}
};

class SFunctionArgument : public SBase {
private:
	SBase * decl;
	SBase * name;
public:
	SFunctionArgument(string decl, string name) : SBase(),
												  decl(new SStringAtom(decl)),
												  name(new SStringAtom(name)) {}
	SFunctionArgument(string decl, SBase * name) : SBase(),
												   decl(new SStringAtom(decl)),
												   name(name) {}
	SFunctionArgument(SBase * decl, string name) : SBase(),
												   decl(decl),
												   name(new SStringAtom(name)) {}
	SFunctionArgument(SBase * decl, SBase * name) : SBase(), decl(decl), name(name) {}
	~SFunctionArgument() {
		if (decl) {
			delete decl;
		}
		if (name) {
			delete name;
		}
	}
	inline string toCString() {
		string res = "";
		if (decl) {
			res += decl->toCString();
		}
		if (name) {
			res += " ";
			res += name->toCString();
		}
		return res;
	}
};

class SFunctionArguments : public SBase {
private:
	vector<SBase *> args;
public:
	SFunctionArguments(SBase * a1) : SBase() {
		args.push_back(a1);
	}
	SFunctionArguments(SBase * a1, SBase * a2) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3, SBase * a4) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
					   SBase * a6) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
					   SBase * a6, SBase * a7) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
					   SBase * a6, SBase * a7, SBase * a8) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
		args.push_back(a8);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
					  SBase * a6, SBase * a7, SBase * a8, SBase * a9) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
		args.push_back(a8);
		args.push_back(a9);
	}
	SFunctionArguments(SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
					   SBase * a6, SBase * a7, SBase * a8, SBase * a9, SBase * a10) : SBase() {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
		args.push_back(a8);
		args.push_back(a9);
		args.push_back(a10);
	}
	SFunctionArguments(vector<SBase *> args) : SBase(), args(args) {}
	~SFunctionArguments() {
		for (vector<SBase *>::iterator iter = args.begin(); iter != args.end(); iter++) {
			delete *iter;
		}
	}
	inline string toCString() {
		string res = "";
		for (vector<SBase *>::iterator iter = args.begin(); iter != args.end(); iter++) {
			SBase * val = *iter;
			if (val) {
				res += val->toCString();
				res += ", ";
			}
		}
		return res;
	}
};

class SFunction : public SStatementBase {
private:
	SBase * retDecl;
	SBase * name;
	SFunctionArguments * args;
	SBase * body;
public:
	SFunction(SBase * retDecl, string name, SFunctionArguments * args) :
								SStatementBase(),
								retDecl(retDecl),
								name(new SStringAtom(name)),
								args(args),
								body(NULL) {}
	SFunction(SBase * retDecl, SBase * name, SFunctionArguments * args) :
								SStatementBase(),
								retDecl(retDecl),
								name(name),
								args(args),
								body(NULL) {}
	SFunction(SBase * retDecl, string name, SFunctionArguments * args, SBase * body) :
								SStatementBase(),
								retDecl(retDecl),
								name(new SStringAtom(name)),
								args(args),
								body(new SBlock(body)) {}
	SFunction(SBase * retDecl, SBase * name, SFunctionArguments * args, SBase * body) :
								SStatementBase(),
								retDecl(retDecl),
								name(name),
								args(args),
								body(new SBlock(body)) {}
	~SFunction() {
		if (retDecl) {
			delete retDecl;
		}
		if (name) {
			delete name;
		}
		if (args) {
			delete args;
		}
		if (body) {
			delete body;
		}
	}
	inline string toCString() {
		string res = "";
		if (retDecl) {
			res += retDecl->toCString();
			res += " ";
		}
		if (name) {
			res += name->toCString();
		}
		res += "(";
		if (args) {
			res += args->toCString();
		}
		res += ")";
		if (body) {
			res += " ";
			res += body->toCString();
		} else {
			res += ";\n";
		}
		return res;
	}
};

class SCall : public SBase {
private:
	SBase * fun;
	vector<SBase *> args;
public:
	SCall(SBase * fun, SBase * a1) : SBase(), fun(fun) {
		args.push_back(a1);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3, SBase * a4) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
		  SBase * a6) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
		  SBase * a6, SBase * a7) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
		  SBase * a6, SBase * a7, SBase * a8) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
		args.push_back(a8);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
		  SBase * a6, SBase * a7, SBase * a8, SBase * a9) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
		args.push_back(a8);
		args.push_back(a9);
	}
	SCall(SBase * fun, SBase * a1, SBase * a2, SBase * a3, SBase * a4, SBase * a5,
		  SBase * a6, SBase * a7, SBase * a8, SBase * a9, SBase * a10) : SBase(), fun(fun) {
		args.push_back(a1);
		args.push_back(a2);
		args.push_back(a3);
		args.push_back(a4);
		args.push_back(a5);
		args.push_back(a6);
		args.push_back(a7);
		args.push_back(a8);
		args.push_back(a9);
		args.push_back(a10);
	}
	SCall(SBase * fun, vector<SBase *> args) : SBase(), fun(fun), args(args) {}
	~SCall() {
		if (fun) {
			delete fun;
		}
		for (vector<SBase *>::iterator iter = args.begin(); iter != args.end(); iter++) {
			delete *iter;
		}
	}
	inline string toCString() {
		string res = "";
		if (fun) {
			res += fun->toCString();
		}
		res += "(";
		for (vector<SBase *>::iterator iter = args.begin(); iter != args.end(); iter++) {
			SBase * val = *iter;
			if (val) {
				res += val->toCString();
				res += ", ";
			}
		}
		res += ")";
		return res;
	}
};

class SCaseStatement : public SStatementBase {
};

class SCaseStatements : public SStatementBase {
};

class SSwitch : public SStatementBase {
};

class SDefault : public SStatementBase {
public:
	SDefault() : SStatementBase() {}
	~SDefault() {}

	inline string toCString() {
		return toString("default:\n");
	}
};

class SLabel: public SStatementBase {
private:
	SBase * val;
public:
	SLabel(SBase * val) : SStatementBase(), val(val) {}
	~SLabel() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "";
		if (val) {
			res += val->toCString();
		}
		res += ":\n";
		return res;
	}
};

class SReturn: public SStatementBase {
private:
	SBase * val;
public:
	SReturn() : SStatementBase(), val(NULL) {}
	SReturn(SBase * val) : SStatementBase(), val(val) {}
	~SReturn() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "return ";
		if (val) {
			res += val->toCString();
		}
		res += ";\n";
		return res;
	}
};

class STypedef: public SStatementBase {
private:
	SBase * from;
	SBase * to;
public:
	STypedef(SBase * from, SBase * to) : SStatementBase(), from(from), to(to) {}
	~STypedef() {
		if (from) {
			delete from;
		}
		if (to) {
			delete to;
		}
	}

	inline string toCString() {
		string res = "typedef ";
		if (from) {
			res += from->toCString();
		}
		if (to) {
			res += to->toCString();
		}
		res += ";\n";
		return res;
	}
};

class SCast: public SBase {
private:
	SBase * from;
	SBase * to;
public:
	SCast(SBase * to, SBase * from) : SBase(), from(from), to(to) {}
	~SCast() {
		if (from) {
			delete from;
		}
		if (to) {
			delete to;
		}
	}

	inline string toCString() {
		string res = "(";
		if (from) {
			res += to->toCString();
		}
		res += ")";
		if (from) {
			res += from->toCString();
		}
		return res;
	}
};

class SParentheses: public SBase {
private:
	SBase * val;
public:
	SParentheses(SBase * val) : SBase(), val(val) {}
	~SParentheses() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "";
		if (dynamic_cast<SParentheses *>(val)) {
			res = val->toCString();
		} else {
			res += "(";
			res += val->toCString();
			res += ")";
		}
		return res;
	}
};

class SStruct: public SStatementBase {
};

class SEnum: public SStatementBase {
};

class SPointerType: public SBase {
private:
	SBase * val;
public:
	SPointerType(SBase * val) : SBase(), val(val) {}
	~SPointerType() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "";
		if (val) {
			res += val->toCString();
		}
		res += " *";
		return res;
	}
};

class SMember: public SBase {
private:
	SBase * lhs;
	SBase * rhs;
public:
	SMember(string lhs, string rhs) : SBase(),
									  lhs(new SStringAtom(lhs)),
									  rhs(new SStringAtom(rhs)) {}
	SMember(SBase * lhs, string rhs) : SBase(),
									   lhs(lhs),
									   rhs(new SStringAtom(rhs)) {}
	SMember(string lhs, SBase * rhs) : SBase(),
									   lhs(new SStringAtom(lhs)),
									   rhs(rhs) {}
	SMember(SBase * lhs, SBase * rhs) : SBase(),
									    lhs(lhs),
									    rhs(rhs) {}
	~SMember() {
		if (lhs) {
			delete lhs;
		}
		if (rhs) {
			delete rhs;
		}
	}
	inline string toCString() {
		string res = "";
		if (lhs) {
			res += lhs->toCString();
		}
		res += ".";
		if (rhs) {
			res += rhs->toCString();
		}
		return res;
	}
};

class SPointerMember: public SBase {
private:
	SBase * lhs;
	SBase * rhs;
public:
	SPointerMember(string lhs, string rhs) : SBase(),
											 lhs(new SStringAtom(lhs)),
											 rhs(new SStringAtom(rhs)) {}
	SPointerMember(SBase * lhs, string rhs) : SBase(),
											  lhs(lhs),
											  rhs(new SStringAtom(rhs)) {}
	SPointerMember(string lhs, SBase * rhs) : SBase(),
											  lhs(new SStringAtom(lhs)),
											  rhs(rhs) {}
	SPointerMember(SBase * lhs, SBase * rhs) : SBase(),
											   lhs(lhs),
											   rhs(rhs) {}
	~SPointerMember() {
		if (lhs) {
			delete lhs;
		}
		if (rhs) {
			delete rhs;
		}
	}
	inline string toCString() {
		string res = "";
		if (lhs) {
			res += lhs->toCString();
		}
		res += "->";
		if (rhs) {
			res += rhs->toCString();
		}
		return res;
	}
};

class SUnion: public SStatementBase {
};

class SSizeOf: public SBase {
private:
	SBase * val;
public:
	SSizeOf(SBase * val) : SBase(), val(val) {}
	~SSizeOf() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "sizeof(";
		if (val) {
			res += val->toCString();
		}
		res += ")";
		return res;
	}
};

class SBreak: public SStatementBase {
public:
	SBreak() : SStatementBase() {}
	~SBreak() {}

	inline string toCString() {
		return "break ;\n";
	}
};

class SContinue: public SStatementBase {
public:
	SContinue() : SStatementBase() {}
	~SContinue() {}

	inline string toCString() {
		return "continue ;\n";
	}
};

class SGoto: public SStatementBase {
private:
	SBase * val;
public:
	SGoto(SBase * val) : SStatementBase(), val(val) {}
	~SGoto() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "goto ";
		if (val) {
			res += val->toCString();
		}
		res += ";\n";
		return res;
	}
};

class SAddress: public SBase {
private:
	SBase * val;
public:
	SAddress(SBase * val) : SBase(), val(val) {}
	~SAddress() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "&";
		if (val) {
			res += val->toCString();
		}
		return res;
	}
};

class SDereference: public SBase {
private:
	SBase * val;
public:
	SDereference(SBase * val) : SBase(), val(val) {}
	~SDereference() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "*";
		if (val) {
			res += val->toCString();
		}
		return res;
	}
};

class SLine: public SStatementBase {
private:
	SBase * val;
public:
	SLine(SBase * val) : SStatementBase(), val(val) {}
	~SLine() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "#line ";
		if (val) {
			res += val->toCString();
		}
		res += "\n";
		return res;
	}
};

class SPragma: public SStatementBase {
private:
	SBase * val;
public:
	SPragma(SBase * val) : SStatementBase(), val(val) {}
	~SPragma() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "#pragma ";
		if (val) {
			res += val->toCString();
		}
		res += "\n";
		return res;
	}
};

class SArray: public SStatementBase {
};

class SError: public SStatementBase {
private:
	SBase * val;
public:
	SError(SBase * val) : SStatementBase(), val(val) {}
	~SError() {
		if (val) {
			delete val;
		}
	}

	inline string toCString() {
		string res = "#error ";
		if (val) {
			res += val->toCString();
		}
		res += "\n";
		return res;
	}
};


inline SBase * SBase::toStatement() {
	if (isStatement()) {
		return this;
	} else {
		return new SStatement(this);
	}
}

#endif /* __SYMBOLIC_GENERATOR_H__ */


