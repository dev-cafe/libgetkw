/*
 * getkw -- a simple input parser
 * Copyright (C) 2019 Jonas Juselius and contributors.
 *
 * This file is part of getkw.

 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * For information on the complete list of contributors to the
 * getkw library, see: <http://getkw.readthedocs.io/>
 */

/*! \file Keyword.hpp
 *
 * \date Jun 3, 2009
 * \author Jonas Juselius <jonas.juselius@uit.no> \n
 *         CTCC, University of Tromsø
 *
 * \brief
 */

#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "GetkwError.hpp"

enum class KeyKinds : int {
  Unknown = -1,
  Undefined,
  Int,
  Dbl,
  Bool,
  Str,
  IntArray,
  DblArray,
  BoolArray,
  StrArray,
  Data
};

template <typename T> class Keyword final {
public:
  Keyword(const std::string _name, const T & _val, bool _isDefd = false)
      : name(_name), val(_val), isDefd(_isDefd) {
    if (!setKind(_val)) {
      GETKW_ERROR("Invalid key type!");
    }
  }

  ~Keyword() {}

  const T & get() const { return val; }
  void set(T & t) { val = t; }

  bool isDefined() const { return isDefd; }

  const std::string & getName() const { return name; }

  int getKind() const { return static_cast<int>(kind); }
  void setDefined(bool _isDefd) { isDefd = _isDefd; }

  void setName(const std::string & _name) { name = _name; }

  template <typename X> std::ostream & repr(std::ostream & o, X /* v */) const {
    if (kind == KeyKinds::Str) {
      o << "  " + name << " = "
        << "\"" << val << "\"";
    } else {
      o << "  " + name << " = " << val;
    }
    return o;
  }
  template <typename X>
  std::ostream & repr(std::ostream & o, const std::vector<X> & v) const {
    o << "  " << name << " = [ ";
    if (kind == KeyKinds::StrArray) {
      o << std::endl;
      o << "\"" << v[0] << "\"";
    } else {
      o << val[0];
    }

    for (unsigned int i = 1; i < val.size(); i++) {
      if (kind == KeyKinds::StrArray) {
        o << ", " << std::endl << "\"" << v[i] << "\"";
      } else {
        o << ", " << v[i];
      }
    }
    o << " ]";
    return o;
  }
  friend std::ostream & operator<<(std::ostream & o, const Keyword<T> & key) {
    return key.repr(o, key.get());
  }

  void print() const { std::cout << &repr(std::cout, val) << std::endl; }

  static const std::string & getNamedKind(KeyKinds i) {
    static const std::string INT = "Int";
    static const std::string DBL = "Dbl";
    static const std::string BOOL = "Bool";
    static const std::string STR = "Str";
    static const std::string INT_ARRAY = "IntArray";
    static const std::string DBL_ARRAY = "DblArray";
    static const std::string BOOL_ARRAY = "BoolArray";
    static const std::string STR_ARRAY = "StrArray";
    static const std::string UNDEF = "Undefined";
    static const std::string UNKN = "Unknown";
    static const std::string DATA = "Data";

    switch (i) {
      case (KeyKinds::Int):
        return INT;
      case (KeyKinds::Dbl):
        return DBL;
      case (KeyKinds::Bool):
        return BOOL;
      case (KeyKinds::Str):
        return STR;
      case (KeyKinds::IntArray):
        return INT_ARRAY;
      case (KeyKinds::DblArray):
        return DBL_ARRAY;
      case (KeyKinds::BoolArray):
        return BOOL_ARRAY;
      case (KeyKinds::StrArray):
        return STR_ARRAY;
      case (KeyKinds::Undefined):
        return UNDEF;
      case (KeyKinds::Data):
        return DATA;
      case (KeyKinds::Unknown):
        return UNKN;
      default:
        return UNKN;
    }
  }

protected:
  std::string name;
  T val;
  bool isDefd;
  bool isArray;
  KeyKinds kind;

  bool setKind(int /* t */) {
    isArray = false;
    kind = KeyKinds::Int;
    return true;
  }
  bool setKind(double /* t */) {
    isArray = false;
    kind = KeyKinds::Dbl;
    return true;
  }
  bool setKind(bool /* t */) {
    isArray = false;
    kind = KeyKinds::Bool;
    return true;
  }
  bool setKind(const std::string & /* t */) {
    isArray = false;
    kind = KeyKinds::Str;
    return true;
  }

  bool setKind(const std::vector<int> & /* t */) {
    isArray = true;
    kind = KeyKinds::IntArray;
    return true;
  }
  bool setKind(const std::vector<double> & /* t */) {
    isArray = true;
    kind = KeyKinds::DblArray;
    return true;
  }
  bool setKind(const std::vector<bool> & /* t */) {
    isArray = true;
    kind = KeyKinds::BoolArray;
    return true;
  }
  bool setKind(const std::vector<std::string> & /* t */) {
    isArray = true;
    kind = KeyKinds::StrArray;
    return true;
  }
  template <class X> bool setKind(const X & t) {
    std::cout << "Warning! Unknown kind:" << t << std::endl;
    kind = KeyKinds::Unknown;
    return false;
  }
};
