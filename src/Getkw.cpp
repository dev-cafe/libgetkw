/** \file Getkw.cpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

using namespace std;

#include "Getkw.h"

#define TEST_ARRAY if (len > 1) cout << "Warning, invalid length of 1 for " << name << endl

Getkw::Getkw(const string &file) {
	strict = false;
	verbose = false;

	if (file.empty() != 0 || file.compare("stdin") == 0
			|| file.compare("STDIN") == 0) {
		if (verbose)
			cout << "Reading from stdin " << endl;
		toplevel = readSect(cin);
	} else {
		const char *fname = file.data();
		if (verbose)
			cout << "Opening file, " << file << endl;
		ifstream fis(fname);
		if (fis.bad()) {
			string err = "Open failed: " + file;
			throw GetkwError(err);
		}
		toplevel = readSect(fis);

		cur = toplevel;
	}
}

Getkw::~Getkw() {
	delete toplevel;
}

void Getkw::setStrict(bool flag) {
	strict = flag;
}

void Getkw::setVerbose(bool flag) {
	verbose = flag;
}

void Getkw::print()
{
	cout << repr(cout) << endl;
}

ostream &Getkw::repr(ostream &o)
{
	return o << *toplevel;
}

template<class T> void Getkw::get(const string &path, T &val) {
	Keyword &key = cur->getKey(path);
	key.get(val);
}

template void Getkw::get(const string&, int&);
template void Getkw::get(const string&, double&);
template void Getkw::get(const string&, bool&);
template void Getkw::get(const string&, string&);
template void Getkw::get(const string&, vector<int>&);
template void Getkw::get(const string&, vector<double>&);
template void Getkw::get(const string&, vector<bool>&);
template void Getkw::get(const string&, vector<string>&);

Keyword &Getkw::getKey(const string &path) {
	return cur->getKey(path);
}

Section &Getkw::getSect(const string &path) {
	return cur->getSect(path);
}

void Getkw::pushSection(const string &path) {
	sstack.push(cur);
	try {
		Section &newsec = cur->getSect(path);
		cur = &newsec;
	} catch (string err) {
		cout << err;
		if (strict)
			exit(1);
	}

}

void Getkw::popSection() {
	if (sstack.empty()) {
		cout << "Error! Getkw stack is empty!" << endl;
		if (strict)
			exit(1);
	}
	cur = sstack.top();
	sstack.pop();
}

Section *Getkw::readSect(istream &fis) {
	istringstream isi;
	string name;
	string tag;
	string dum1, dum2;
	string set;
	int nsect, nkeys, i;
	bool isSet, hasTag;

	readline(fis, isi);
	isi >> dum1 >> name >> nsect >> set;
	readline(fis, isi);
	isi >> dum1 >> tag >> dum2 >> nkeys;

	isSet = convBool(set);
	hasTag = convBool(tag);

	Keyword *key;
	Section *sect;
	Section *thissect = new Section(name);
	thissect->setDefined(isSet);
	if (hasTag) {
		readline(fis, isi);
		isi >> tag;
		thissect->setTag(tag);
	}

	for (i = 0; i < nkeys; i++) {
		key = readKey(fis);
		thissect->addKey(key);
	}
	for (i = 0; i < nsect; i++) {
		sect = readSect(fis);
		thissect->addSect(sect);
	}

	return thissect;
}

Keyword *Getkw::readKey(istream &fis) {
	istringstream isi;
	string type, name, set;
	int len;

	readline(fis, isi);
	isi >> type >> name >> len >> set;

	bool setf = convBool(set);
	int kind = convKind(type);

	Keyword *key;
	string ss;
	vector<int> iv;
	vector<double> dv;
	vector<bool> bv;
	vector<string> sv;

	switch (kind) {
	case Keyword::Int:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		int is;
		readline(fis, isi);
		isi >> is;
		key = new Keyval<int> (name, is, setf);
		break;
	case Keyword::Dbl:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		double ds;
		readline(fis, isi);
		isi >> ds;
		key = new Keyval<double> (name, ds, setf);
		break;
	case Keyword::Bool:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		bool bs;
		readline(fis, isi);
		isi >> ss;
		bs = convBool(ss);
		key = new Keyval<bool> (name, bs, setf);
		break;
	case Keyword::Str:
		TEST_ARRAY;
		if (len == 0)
			return NULL;
		getline(fis, ss);
		key = new Keyval<string> (name, ss, setf);
		break;
	case Keyword::IntArray:
		if (len == 0)
			return NULL;
		int ival;
		for (int i = 0; i < len; i++) {
			readline(fis, isi);
			isi >> ival;
			iv.push_back(ival);
		}
		key = new Keyvec<int> (name, iv, setf);
		break;
	case Keyword::DblArray:
		if (len == 0)
			return NULL;
		double dval;
		for (int i = 0; i < len; i++) {
			readline(fis, isi);
			isi >> dval;
			dv.push_back(dval);
		}
		key = new Keyvec<double> (name, dv, setf);
		break;
	case Keyword::BoolArray:
		if (len == 0)
			return NULL;
		bool bval;
		for (int i = 0; i < len; i++) {
			readline(fis, isi);
			isi >> ss;
			bval = convBool(ss);
			bv.push_back(bval);
		}
		key = new Keyvec<bool> (name, bv, setf);
		break;
	case Keyword::StrArray:
	case Keyword::Data:
		if (len == 0)
			return NULL;
		for (int i = 0; i < len; i++) {
			getline(fis, ss);
			sv.push_back(ss);
		}
		key = new Keyvec<string> (name, sv, setf);
		break;
	default:
		string err = "Unknown keyword type: " + name + " <> " + type;
		throw GetkwError(err);
		break;
	}
	return key;

}

void Getkw::readline(istream &fis, istringstream &isi) {
	static string buf;
	getline(fis, buf);
	isi.clear();
	isi.str(buf);
}

bool Getkw::convBool(const string &val) {
	if (val[0] == 'T' or val[0] == 't')
		return true;
	return false;

}

int Getkw::convKind(const string &typ) {
	static const string INT = "INT";
	static const string DBL = "DBL";
	static const string BOOL = "BOOL";
	static const string STR = "STR";
	static const string DATA = "DATA";
	static const string INT_ARRAY = "INT_ARRAY";
	static const string DBL_ARRAY = "DBL_ARRAY";
	static const string BOOL_ARRAY = "BOOL_ARRAY";
	static const string STR_ARRAY = "STR_ARRAY";

	if (typ.compare(INT) == 0)
		return Keyword::Int;
	if (typ.compare(DBL) == 0)
		return Keyword::Dbl;
	if (typ.compare(BOOL) == 0)
		return Keyword::Bool;
	if (typ.compare(STR) == 0)
		return Keyword::Str;
	if (typ.compare(DATA) == 0)
		return Keyword::Data;
	if (typ.compare(INT_ARRAY) == 0)
		return Keyword::IntArray;
	if (typ.compare(DBL_ARRAY) == 0)
		return Keyword::DblArray;
	if (typ.compare(BOOL_ARRAY) == 0)
		return Keyword::BoolArray;
	if (typ.compare(STR_ARRAY) == 0)
		return Keyword::StrArray;
	return -1;
}

