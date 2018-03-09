/*
 * getkw -- a simple input parser
 * Copyright (C) 2018 Jonas Juselius and contributors.
 *
 * This file is part of getkw.

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on the complete list of contributors to the
 * getkw library, see: <http://getkw.readthedocs.io/>
 */

/*! \file Getkw.hpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#pragma once

#include <iosfwd>
#include <stack>
#include <string>
#include <vector>

class Section;
template <typename T> class Keyword;

class Getkw {
public:
  Getkw(std::string file, bool _verbose = false, bool _strict = false);
  Getkw(const Getkw & kw);
  Getkw & operator=(const Getkw & kw);
  Getkw();
  virtual ~Getkw();
  void setStrict(bool flag);
  void setVerbose(bool flag);
  void pushSection(const std::string & path);
  void popSection();
  const Section & getSect(const std::string & path) const;
  template <typename T>
  const Keyword<T> & getKeyword(const std::string & path) const;
  template <typename T> const T & get(const std::string & path) const;

  int getInt(const std::string & path) const { return get<int>(path); }
  double getDbl(const std::string & path) const { return get<double>(path); }
  bool getBool(const std::string & path) const { return get<bool>(path); }
  const std::string & getStr(const std::string & path) const {
    return get<std::string>(path);
  }
  const std::vector<int> getIntVec(const std::string & path) const {
    return get<std::vector<int>>(path);
  }
  const std::vector<double> getDblVec(const std::string & path) const {
    return get<std::vector<double>>(path);
  }
  const std::vector<bool> getBoolVec(const std::string & path) const {
    return get<std::vector<bool>>(path);
  }
  const std::vector<std::string> getStrVec(const std::string & path) const {
    return get<std::vector<std::string>>(path);
  }
  const std::vector<std::string> getData(const std::string & path) const {
    return getStrVec(path);
  }

  void print() const;
  std::ostream & repr(std::ostream & o) const;
  friend std::ostream & operator<<(std::ostream & o, const Getkw & gkw) {
    return gkw.repr(o);
  }

protected:
  static Section * readSect(std::istream & fis);
  static bool readKey(Section * sect, std::istream & fis);
  static void readline(std::istream & fis, std::istringstream & isi);
  static bool convBool(const std::string & val);
  static int convKind(const std::string & typ);

private:
  bool verbose;
  bool strict;
  std::string file;
  Section * toplevel;
  const Section * cur;
  std::stack<const Section *> sstack;
};
