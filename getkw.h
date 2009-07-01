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
#include <stack>

#include "Section.h"
#include "Keyword.h"
#include "Keyval.h"
#include "Keyvec.h"

class Getkw {
public:
	Getkw(string file);
	virtual ~Getkw();
	void set_strict(bool flag);
	void set_verbose(bool flag);
	Section &pushSection(const string path);
	Section &popSection();
	Section &getSect(const string path);
	Keyword &getKey(const string path);
	template <class T> void get(const string path, T &val);
protected:
	enum KeyType {
		Int, Dbl, Bool, Str, Data, IntArray, DblArray, BoolArray, StrArray
	};
	static Section *readSect(istream &fis);
	static Keyword *readKey(istream &fis);
	static bool convBool(const string val);
	static int convKind(const string typ);
private:
	string file;
	Section *toplevel;
	Section *cur;
	stack<Section *> sstack;
};

#endif /* GETKW_H_ */
