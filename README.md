# kdz2-ratexpr

## Сборка проекта

Для сборки проекта выполните команды:

```bash
cmake -S . -B build-debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build-debug -j
cmake -S . -B build-release -DCMAKE_BUILD_TYPE=Release && cmake --build build-release -j
```

## Запуск программ

```bash
./build-debug/apps/demo_fraction
```

```bash
./build-debug/apps/demo_expression
```

