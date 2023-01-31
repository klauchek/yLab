# HW3D: Triangles intersection

## Task: 
<p> Print the numbers of all triangles that intersect with any other </p>

#
### *Input*:
amount of triangles N <br>
N sets of points representing a three-dimensional triangle 
### *Output*:
intersected triangles' numbers

<br>

# How to build the project

build with:
```
cmake -S ./ -B build/ -DCMAKE_BUILD_TYPE=Release
cd build
make
```
run task with any end2end test:
```
./intersect_trs < ../test/end2end/test_1.txt
```
run task with all end2end tests:
```
for f in ../test/end2end/test_*.txt; do ./intersect_trs < $f; printf '\n'; done
```
# Unit tests (using google test)
if you want to run with unit tests for flat map:
```
cmake -S ./ -B build/ -DCMAKE_BUILD_TYPE=Release -DWITH_TESTS=on
cd build
make
ctest
```
or to see full log:
```
ctest --verbose
```

----------------------------
### Based on algorithm by Olivier Devillers and Philippe Guigue - [Faster Triangle-Triangle Intersection Tests](https://hal.inria.fr/inria-00072100/document)
----------------------------
