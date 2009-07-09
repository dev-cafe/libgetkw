/** \file Getkw.h
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#ifndef GETKW_H_
#define GETKW_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

#include "Section.h"
#include "Keyword.h"
#include "Keyval.h"
#include "Keyvec.h"
#include "GetkwError.h"

class Getkw {
public:
	Getkw(const string &file);
	virtual ~Getkw();
	void setStrict(bool flag);
	void setVerbose(bool flag);
	void pushSection(const string &path);
	void popSection();
	Section &getSect(const string &path);
	Keyword &getKey(const string &path);
	template<class T> void get(const string &path, T &val);

	int getInt(const string &path) {
		return getKey(path).getInt();
	}
	double getDbl(const string &path) {
		return getKey(path).getDbl();
	}
	bool getBool(const string &path) {
		return getKey(path).getBool();
	}
	string getStr(const string &path) {
		return getKey(path).getStr();
	}
	vector<int> getIntVec(const string &path) {
		return getKey(path).getIntVec();
	}
	vector<double> getDblVec(const string &path) {
		return getKey(path).getDblVec();
	}
	vector<bool> getBoolVec(const string &path) {
		return getKey(path).getBoolVec();
	}
	vector<string> getStrVec(const string &path) {
		return getKey(path).getStrVec();
	}
	vector<string> getData(const string &path) {
		return getKey(path).getData();
	}

	void print();
	ostream &repr(ostream &o);
	friend ostream &operator<<(ostream &o, Getkw &gkw) {
		return gkw.repr(o);
	}
protected:
	static Section *readSect(istream &fis);
	static Keyword *readKey(istream &fis);
	static void readline(istream &fis, istringstream &isi);
	static bool convBool(const string &val);
	static int convKind(const string &typ);
private:
	bool strict;
	bool verbose;
	string file;
	Section *toplevel;
	Section *cur;
	stack<Section *> sstack;
};

#endif /* GETKW_H_ */
