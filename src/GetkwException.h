/*
 * \file GetkwException.h
 *
 *  \date Jul 2, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \breif
 */

#ifndef GETKWEXCEPTION_H_
#define GETKWEXCEPTION_H_

#include <exception>
#include <iostream>
#include <string>

using namespace std;

class GetkwException: public exception {
public:
	GetkwException(const string &err, bool verbose = true): msg(err), verbose(verbose)  {};
	virtual ~GetkwException() throw() {
	}
	friend ostream& operator<<(ostream &o, const GetkwException &e) {
		if (e.verbose) {
			return o << e.msg;
		}
		return o;
	}
	virtual const char *what() {
		return msg.data();
	}
private:
	string msg;
	bool verbose;
};

#endif /* GETKWEXCEPTION_H_ */
