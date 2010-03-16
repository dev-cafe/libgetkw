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
	Keyvec(const std::string &name, std::vector<T> &xarg, bool isDefd = false);
	virtual ~Keyvec();
	virtual bool get(std::vector<T> &t);
	virtual void set(std::vector<T> &t);
	virtual Keyvec<T> *clone();
	virtual std::ostream &repr(std::ostream &o) const;
	friend std::ostream& operator <<(std::ostream& o, Keyvec<T> &key) {
		return key.repr(o);
	}
protected:
	std::vector<T> arg;
};

#endif /* KEYVEC_H_ */
