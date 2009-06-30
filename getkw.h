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

#include <stack>

#include "Section.h"
#include "Keyword.h"
#include "Keyval.h"
#include "Keyvec.h"

class Getkw {
protected:
	string file;
	Section *toplevel;
	Section *cur;
	//Section *stack[MAX_SECT_STACK];
	//int sp;
public:
	Getkw(string file);
	virtual ~Getkw();
	void set_strict(bool flag);
	void set_verbose(bool flag);
protected:
	enum KeyType {
		Int, Dbl, Bool, Str, Data, IntArray, DblArray, BoolArray, StrArray
	};
	static Section *read_input(istream &fis);
	static Section *readSect(ifstream &fis);
	static Keyword *readKey(ifstream &fis);
	static bool convBool(const string val);
	static int convKind(const string typ);
};


#endif /* GETKW_H_ */
