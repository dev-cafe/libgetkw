[![License: MPL v2.0](https://img.shields.io/github/license/dev-cafe/libgetkw.svg?style=for-the-badge)](https://github.com/dev-cafe/libgetkw/blob/master/LICENSE)

[![Travis CI](https://img.shields.io/travis/dev-cafe/libgetkw.svg?style=for-the-badge)](https://travis-ci.org/dev-cafe/libgetkw)
[![AppVeyor CI](https://img.shields.io/appveyor/ci/dev-cafe/libgetkw.svg?style=for-the-badge)](https://ci.appveyor.com/project/dev-cafe/libgetkw)
[![Codecov](https://img.shields.io/codecov/c/github/dev-cafe/libgetkw.svg?style=for-the-badge)](https://codecov.io/gh/dev-cafe/libgetkw)

[![GitHub issues](https://img.shields.io/github/issues/dev-cafe/libgetkw.svg?style=for-the-badge)](https://github.com/dev-cafe/libgetkw/issues)
[![GitHub forks](https://img.shields.io/github/forks/dev-cafe/libgetkw.svg?style=for-the-badge)](https://github.com/dev-cafe/libgetkw/network)
[![GitHub stars](https://img.shields.io/github/stars/dev-cafe/libgetkw.svg?style=for-the-badge)](https://github.com/dev-cafe/libgetkw/stargazers)

# libgetkw: User input parsing and validation library.

![parse-all](https://github.com/dev-cafe/libgetkw/raw/master/assets/parse.jpg "Parse all the inputs!")

Copyright 2015-2018 Jonas Juselius <jonas.juselius@gmail.com>.
Licensed under [MPL v2.0](LICENSE).

### Development environment

You will need C++, C and Fortran compilers, plus a working Python interpreter.
You can get the Python dependencies using Pipenv:
```
pipenv install
pipenv shell
```

### Formatting

- We use `clang-format` for C and C++
  ```
  git ls-files C | xargs clang-format -i
  git ls-files C++ | xargs clang-format -i
  ```
- We use `yapf` for Python
  ```
  git ls-files Python | xargs yapf -i
  ```
- We use `fprettify` for Fortran
  ```
  git ls-files Fortran | xargs fprettify -i 2
  ```

### Git hooks

You can install Git hooks to keep in check formatting and licensing headers:

```
cd .git/hooks
cp --symbolic-link ../../.githooks/* .
```

### Build Doxygen docs

From the top-level directory run:
```
doxygen
```
