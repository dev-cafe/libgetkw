/*
 * \file GetkwError.h
 *
 *  \date Jul 2, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \breif
 */

#ifndef GETKWERROR_H_
#define GETKWERROR_H_

#include <exception>
#include <iostream>
#include <string>

using namespace std;

class GetkwError: public exception {
public:
	GetkwError(const string &err, bool verbose = true);
	virtual ~GetkwError() throw();
	friend ostream& operator<<(ostream &o, const GetkwError &e) {
			return o << e.msg;
	}
	virtual const char *what() {
		return msg.data();
	}
private:
	string msg;
	bool verbose;
};

#endif /* GETKWERROR_H_ */
