/** \file Keyvec.h
 *
 * \date Jun 4, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#ifndef KEYVEC_H_
#define KEYVEC_H_

#include <vector>
#include "Keyval.h"

template<class T>
class Keyvec: public Keyword {
public:
	Keyvec(const string name, vector<T> xarg, bool isDefd) :
		Keyword(name, isDefd), arg(xarg) {};
	virtual ~Keyvec();
	virtual bool get(vector<T> &t) {t=arg; return this->isDefd;};
	virtual void set(vector<T> &t) {arg=t; this->isDefd=true;};
	virtual Keyvec<T> *clone();
	virtual ostream &print(ostream &o);

protected:
	vector<T> arg;
};

#endif /* KEYVEC_H_ */
