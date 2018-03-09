# libgetkw: User input parsing and validation library.

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
