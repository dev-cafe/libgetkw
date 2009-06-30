/** \file Keyval.h
 *
 * \date Jun 4, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief Keyword with a value. Very useful.
 */

#ifndef KEYVAL_H_
#define KEYVAL_H_

#include "Keyword.h"
#include <iostream>
#include <vector>
#include <string>

template <class T>
class Keyval: public Keyword {
public:
	Keyval(const string name, T xarg, bool isDefd=false): Keyword(name, isDefd), arg(xarg) {};
//	Keyval(const string name, bool isDefd=false): Keyword(name, isDefd) {};
	virtual ~Keyval();
	virtual bool get(T &t) {t=arg; return isDefd;};
	virtual void set(T &t) {arg=t; isDefd=true;};
	virtual Keyval<T> *clone();
	virtual ostream &print(ostream &o);

protected:
	T arg;
};

#endif /* KEYVAL_H_ */
