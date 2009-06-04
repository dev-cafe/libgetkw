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
	Section *read_input(istream &fis);
};


#endif /* GETKW_H_ */
