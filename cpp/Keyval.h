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
	Keyval(const std::string &name, T &xarg, bool isDefd=false);
	virtual ~Keyval();
	virtual bool get(T &t) const;
	virtual void set(T &t);
	virtual Keyval<T> *clone();
	virtual std::ostream &repr(std::ostream &o) const;
	friend std::ostream& operator <<(std::ostream& o, Keyval<T> &key) {
		return key.repr(o);
	}
protected:
	T arg;
};

#endif /* KEYVAL_H_ */
