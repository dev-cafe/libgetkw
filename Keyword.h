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
	Keyword(const string name, bool is_set);
	virtual ~Keyword();

	bool isSet(void) {return isset;};
	void setState(bool state) {isset=state;};
	string &getName(void) { return name;};

	static Keyword *readKey(ifstream &fis);

	virtual bool get(int &t) {return false;};
	virtual bool get(double &t) {return false;};
	virtual bool get(bool &t) {return false;};
	virtual bool get(string &t) {return false;};
	virtual bool get(vector<int> &t) {return false;};
	virtual bool get(vector<double> &t) {return false;};
	virtual bool get(vector<bool> &t) {return false;};
	virtual bool get(vector<string> &t) {return false;};

	virtual void set(int &t) {};
	virtual void set(double &t) {};
	virtual void set(bool &t) {};
	virtual void set(string &t) {};
	virtual void set(vector<int> &t) {};
	virtual void set(vector<double> &t) {};
	virtual void set(vector<bool> &t) {};
	virtual void set(vector<string> &t) {};

	virtual ostream &print(ostream &o) {return o << "nil" << endl; };

	friend ostream& operator << (ostream& o, Keyword &kw)
	{
		return kw.print(o);
	}
	enum KeyType {Int, Dbl, Bool, Str, Data, IntArray,
		DblArray, BoolArray, StrArray};
protected:
	static bool convBool(string val);
	static int convType(string typ);
	string name;
	bool isset;
};


#endif /* KEYWORD_H_ */
