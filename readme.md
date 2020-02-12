# Конфигурация проекта

## Требования перед конфигурацией

1. Установленный `cmake` (версией не менее 3.8) и путь к нему, прописанный в переменную среды `PATH`
2. Установленный `Qt5` (версией не менее 5.11) и путь к нему `QTDIR`, прописанный в переменную среды `PATH`

## Конфигурация

1. mkdir build
2. cd build
3. cmake ./.. (либо явно указать целевую платформу через параметр -G)

### Пример конфигурирования:

```
>mkdir build

>cd build

>cmake -G"Visual Studio 15 2017 Win64" ./..
-- Selecting Windows SDK version 10.0.17763.0 to target Windows 10.0.18362.
-- The C compiler identification is MSVC 19.16.27035.0
-- The CXX compiler identification is MSVC 19.16.27035.0
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe
-- Check for working C compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe
-- Check for working CXX compiler: C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Tools/MSVC/14.16.27023/bin/Hostx86/x64/cl.exe -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: C:/Users/vladislav/source/repos/path_finder/build
```

## Сборка под Visual Studio
После успешной конфигурации в директории `build` находится файл solution-а с названием `path_finder.sln`. Открываем его в `Visual Studio`. После подгрузки всех необходимых компонентов в `Solution Exlorer` появятся все проекты и предопределенные цели. Также можно сразу открыть папку с проектом в `Visual Studio` и произвести все манипуляции с `cmake` внутри нее без работы в командной строке.

Для того, чтобы собрать, например, все проекты, надо построить предопределенную цель `ALL_BUILD`.