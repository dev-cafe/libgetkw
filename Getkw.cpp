/** \file Getkw.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>

#include "macros.h"
#include "Getkw.h"

Getkw::Getkw(string file) {

	if (file.empty() || file.compare("stdin") == 0 || file.compare("STDIN")) {
		toplevel = read_input(cin);
	} else {
		const char *fname=file.data();
		ifstream fis(fname);
		if (fis.bad()) {
			cout << "Open failed: " << file << endl;
			throw 256;
		}
		toplevel = read_input(fis);

		cur = toplevel;
	}
}

Getkw::~Getkw() {
	// TODO Auto-generated destructor stub
}

void Getkw::set_strict(bool flag) {
}

void Getkw::set_verbose(bool flag) {
}

Section *Getkw::read_input(istream &fis) {
	return NULL;
}

