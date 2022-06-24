# PermsCalc

Unix chmod permission calculator utility tool.

## Usage

Pass one or more parameter(s):

```
$ permscalc 777
rwxrwxrwx

$ permscalc rw-r-x-wx
653

$ permscalc d------rwx
007

$ permscalc 644 720 -rw-rw-r--
rw-r--r--
rwx-w----
664
```

Interactive mode (from `stdin`):

```
$ permscalc
> 007
  ------rwx
> rw-r-x-wx
  653

$ ls -ld example.txt | awk '{ print $1; }' | permscalc
644
```

## Build

Compile with make

```
make
```

## Test

```
make test
```
