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
	Keyvec(const string &name, vector<T> &xarg, bool isDefd = false);
	virtual ~Keyvec();
	virtual bool get(vector<T> &t);
	virtual void set(vector<T> &t);
	virtual Keyvec<T> *clone();
	virtual ostream &repr(ostream &o);
	friend ostream& operator <<(ostream& o, Keyvec<T> &key) {
		return key.repr(o);
	}
protected:
	vector<T> arg;
};

#endif /* KEYVEC_H_ */
