/*
 * \file Envelope.h
 *
 *  \date Jun 26, 2009
 *  \author Jonas Juselius <jonas.juselius@uit.no> \n
 *          CTCC, University of Tromsø
 *
 * \breif
 */

#ifndef ENVELOPE_H_
#define ENVELOPE_H_

#include <iostream>
#include <string>
using namespace std;

class Envelope {
public:
	Envelope(string name, bool isDefd);
	virtual ~Envelope();
	virtual ostream &print(ostream &o) { return o; }
    int getType() const
    {
        return type;
    }

    friend ostream& operator <<(ostream& o, Envelope &e) {
		return e.print(o);
	}

	bool isDefined() const {
		return isDefd;
	}

	string getName() const {
		return name;
	}

	void setDefined(bool isDefd) {
		this->isDefd = isDefd;
	}

	void setName(string name) {
		this->name = name;
	}

protected:
	enum Type {Env, Key, Sect};
	int type;
	string name;
	bool isDefd; //! True if explicitly set (i.e. not a default value)

};

#endif /* ENVELOPE_H_ */
