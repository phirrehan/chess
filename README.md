# Chess

A console based chess made in pure C++.

# Build Instructions

Clone this repository:

```
git clone https://github.com/phirrehan/chess
cd chess
```

Compile the project using cmake:

```
cmake -B build
cmake --build build
```

If you are on `Windows` and have `MinGW`, then instead use the following:

```
cmake -B build -G "MinGW Makefiles"
cmake --build build
```

> Ensure cmake and c++ compiler are added in PATH

Run the binary:

```
./build/chess
```
