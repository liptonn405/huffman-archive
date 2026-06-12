# Архиватор на базе алгоритма Хаффмана

Консольное приложение для сжатия и разжатия файлов по алгоритму Хаффмана. Поддерживает произвольные бинарные файлы - текст, изображения, архивы и другие форматы.

## Алгоритм

Алгоритм Хаффмана - алгоритм сжатия без потерь, основанный на построении префиксных кодов. Частым символам назначаются короткие коды, редким - длинные. Это позволяет сократить размер файла без потери данных.

## Структура проекта

```
huffman-archive/
├── src/                  # Исходный код
│   ├── main.cpp          # Точка входа, CLI
│   ├── huffman.cpp       # Алгоритм Хаффмана
│   ├── encoder.cpp       # Сжатие файла
│   ├── decoder.cpp       # Разжатие файла
│   ├── bit_writer.cpp    # Побитовая запись
│   └── bit_reader.cpp    # Побитовое чтение
├── include/              # Заголовочные файлы
│   ├── tree.h            # Бинарное дерево
│   ├── huffman.h         # Алгоритм Хаффмана
│   ├── huffman_code.h    # Код Хаффмана
│   ├── encoder.h         # Сжатие
│   ├── decoder.h         # Разжатие
│   ├── bit_writer.h      # Буфер записи битов
│   ├── bit_reader.h      # Буфер чтения битов
│   └── format.h          # Формат сжатого файла
├── tests/                # Модульные и интеграционные тесты
├── experiments/          # Эксперименты и замеры
│   ├── benchmark.cpp     # Замеры производительности
│   ├── data/             # Тестовые файлы
│   └── results/          # Результаты замеров
└── CMakeLists.txt
```

## Требования

- CMake >= 3.20
- Компилятор с поддержкой C++17 (g++ или clang++)

## Сборка

```bash
mkdir cmake-build-debug && cd cmake-build-debug
cmake ..
make
```

## Использование

### Сжатие

```bash
./cmake-build-debug/huffman_archive -c input.txt output.huf
```

### Разжатие

```bash
./cmake-build-debug/huffman_archive -d output.huf result.txt
```
## Запуск тестов

```bash
./cmake-build-debug/tests_bin
```

Ожидаемый вывод:
```
[Running test] test_countFrequency
[OK] test_countFrequency
[Running test] test_buildTree
[OK] test_buildTree
...
[PASSED]: 46
[FAILED]: 0
```

## Эксперименты

Положите файлы в `experiments/data/` и запустите:

```bash
./cmake-build-debug/benchmark
```

Результаты сохранятся в `experiments/results/results.csv`.

### Выводы

- Текстовые файлы сжимаются на **25-50%**
- Бинарные файлы сжимаются на **~27%**
- Уже сжатые файлы **не сжимаются** - размер увеличивается из-за заголовка
- Разжатие **медленнее** сжатия - decoder читает побитово и обходит дерево для каждого символа
