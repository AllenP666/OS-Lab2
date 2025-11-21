@echo off
echo Updating repository...
git pull
if %errorlevel% neq 0 (
  echo Git pull failed
  exit /b %errorlevel%
)

echo Creating build directory...
if not exist build mkdir build
cd build

echo Running CMake...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
if %errorlevel% neq 0 (
  echo CMake configuration failed
  exit /b %errorlevel%
)

echo Building project...
cmake --build .
if %errorlevel% neq 0 (
  echo Build failed
  exit /b %errorlevel%
)

echo.
echo Build succeeded. Running test utility...
.\test_utility\test_utility.exe
if %errorlevel% neq 0 (
  echo Test utility failed!
  exit /b %errorlevel%
)

echo Test utility finished successfully.
pause