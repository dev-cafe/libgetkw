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

class Keyword {
public:
	Keyword(const string name, bool isDefd=false);
	virtual ~Keyword();

	static Keyword *readKey(ifstream &fis);

	virtual Keyword *clone() {
		return 0;
	}

	virtual bool get(int &t) {
		return false;
	}

	virtual bool get(double &t) {
		return false;
	}

	virtual bool get(bool &t) {
		return false;
	}

	virtual bool get(string &t) {
		return false;
	}

	virtual bool get(vector<int> &t) {
		return false;
	}

	virtual bool get(vector<double> &t) {
		return false;
	}

	virtual bool get(vector<bool> &t) {
		return false;
	}

	virtual bool get(vector<string> &t) {
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

	void setDefined(bool isDefd) {
		this->isDefd = isDefd;
	}

	void setName(string name) {
		this->name = name;
	}

	friend ostream& operator <<(ostream& o, Keyword &key) {
		return key.print(o);
	}

	virtual ostream &print(ostream &o) {
		return o << "No value";
	}

	enum KeyType {
		Int, Dbl, Bool, Str, Data, IntArray, DblArray, BoolArray, StrArray
	};
protected:
	string name;
	bool isDefd;
	int kind;
	static bool convBool(const string val);
	static int convKind(const string typ);
};

#endif /* KEYWORD_H_ */
