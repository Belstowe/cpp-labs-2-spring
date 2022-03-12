# Современные технологии программирования

## Весенний семестр. 2021-2022 гг.

Ковалев Максим Игоревич, гр. ИВ-923.

## Лабораторные работы

1. [Перегрузка операторов](#перегрузка-операторов)
2. [Умные указатели](#умные-указатели)
3. [Контейнеры и алгоритмы STL](#контейнеры-и-алгоритмы-stl)

## Перегрузка операторов

Структура:
```
src/libcsc/libcsc/time
`-- time.hpp
test/libcsc/libcsc
`-- time.cpp
```

## Умные указатели

Структура:
```
src/libcsc/libcsc/smartptr
|-- SharedPtr.hpp
`-- UniquePtr.hpp
test/libcsc/libcsc
`-- smartptr.cpp
```

## Контейнеры и алгоритмы STL

Структура:
```
src/libcsc/libcsc/soundex
|-- soundex.cpp
`-- soundex.hpp
src/soundex_groupby/soundex_groupby
`-- main.cpp
test/libcsc/libcsc
`-- soundex.cpp
```

### Запуск

После компиляции необходимая утилита для обработки файла (и сам тестировочный файл) будет находиться по следующему пути:

```
build/bin
|-- soundex_groupby
`-- names2020.csv
```

Чтобы запустить программу:

```bash
./soundex_groupby -i names2020.csv {-o output.json}
```

Если выходной файл `-o` не будет указан, вывод будет производиться в консоль.