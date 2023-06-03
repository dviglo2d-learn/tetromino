:: Меняем кодировку консоли на UTF-8
chcp 65001

:: При запуске батника от Админа меняется текущий путь. Фиксим это
cd /D "%~dp0"

:: Указываем путь к cmake.exe
set "PATH=c:\programs\cmake\bin"

:: Создаём проекты для Visual Studio 2022 в папке build_vs, используя конфиг CMakeLists.txt из папки game
cmake.exe game -B build_vs -G "Visual Studio 17" -D DV_SHARED=1

:: Ждём нажатие Enter перед закрытием консоли
pause
