#ifndef CONST_COMMON_H
#define CONST_COMMON_H
/*
 * Если в mainwindow.cpp кликнуть по
setWindowTitle(Constants::IDE_DISPLAY_NAME);
то попадаешь в автосгенерированный
/tmp/QtCreator-nVTtBI/qtc-cmake-dUzfxtpO/src/app/app_version.h
Где строковые константы собраны.
Так можно делать локализацию константную: с помощью CMake менять в прототипе .h ника все названия на целевые чтобы в runtime сэкономить CPU
*/

namespace Retail {

//const int kVERSION_MAJOR = 1;
//const int kVERSION_MINOR = 0;
//const int kVERSION_RELEASE = 1;

const char VERSION_LONG[] = SPEC_VERSION;
const char AUTHOR[]       = "Bondarenko D.A.";
const char YEAR[]         = "2020";

const char IDE_DISPLAY_NAME[] = "Retail monitor";
const char IDE_ID[]           = "retail_mon";
}
#endif // CONST_COMMON_H
