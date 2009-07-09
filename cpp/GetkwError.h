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

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>

using namespace std;

class GetkwError: public exception {
public:
	GetkwError();
	GetkwError(const string &err);
	virtual ~GetkwError() throw();
	void trigger(const string &msg);
	static void setVerbose(bool flag);
	static void setStrict(bool flag);
	friend ostream& operator<<(ostream &o, const GetkwError &e) {
			return o << e.msg;
	}
//	virtual const char *what() {
//		return err.c_str();
//	}
private:
	string msg;
	static bool verbose;
	static bool strict;
};

#endif /* GETKWERROR_H_ */
