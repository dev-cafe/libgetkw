/** \file Keyword.h
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#ifndef KEYWORD_H_
#define KEYWORD_H_

using namespace std;
#include <string>
#include <vector>
#include <fstream>

#include "GetkwError.h"

class Keyword {
public:
	Keyword(const string name, bool isDefd = false);
	virtual ~Keyword();

	virtual Keyword *clone() {
		return 0;
	}

	int getInt();
	double getDbl();
	bool getBool();
	string getStr();

	vector<int> getIntVec();
	vector<double> getDblVec();
	vector<bool> getBoolVec();
	vector<string> getStrVec();
	vector<string> getData() { return getStrVec(); }

	virtual bool get(int &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(double &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(bool &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(string &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(vector<int> &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(vector<double> &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(vector<bool> &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual bool get(vector<string> &t) {
		throwErrorWrongKind(t);
		return false;
	}

	virtual void set(int &t) {
	}

	virtual void set(double &t) {
	}

	virtual void set(bool &t) {
	}

	virtual void set(string &t) {
	}

	virtual void set(vector<int> &t) {
	}

	virtual void set(vector<double> &t) {
	}

	virtual void set(vector<bool> &t) {
	}

	virtual void set(vector<string> &t) {
	}

	bool isDefined() const {
		return isDefd;
	}

	string getName() const {
		return name;
	}

	int getKind() const {
		return kind;
	}
	void setDefined(bool isDefd) {
		this->isDefd = isDefd;
	}

	void setName(string name) {
		this->name = name;
	}

	friend ostream& operator <<(ostream& o, Keyword &key) {
		return key.repr(o);
	}

	virtual void print() {
		cout << repr(cout) << endl;
	}

	virtual ostream &repr(ostream &o) {
		return o << "Warning! Keyword: Unknown key type.";
	}

	enum KeyType {
		Unknown = -1,
		Undefined,
		Int,
		Dbl,
		Bool,
		Str,
		IntArray,
		DblArray,
		BoolArray,
		StrArray,
		Data
	};

	const static string &getNamedKind(int i);
	template<class T> void throwErrorWrongKind(T &t);
protected:
	int isKind(int &t) {
		return Int;
	}
	int isKind(double &t) {
		return Dbl;
	}
	int isKind(bool &t) {
		return Bool;
	}
	int isKind(string &t) {
		return Str;
	}
	int isKind(vector<int> &t) {
		return IntArray;
	}
	int isKind(vector<double> &t) {
		return DblArray;
	}
	int isKind(vector<bool> &) {
		return BoolArray;
	}
	int isKind(vector<string> &t) {
		return StrArray;
	}
	template<class T> int setKind(T &t) {
		cout << "Warning! Unknown kind:" << t << endl;
		return Unknown;
	}
	string name;
	bool isDefd;
	int kind;
};

#endif /* KEYWORD_H_ */
