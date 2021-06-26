#include <QDir>
#include "graph.h"


/// <summary>
/// Получить абсолютный путь к файлу
/// <param name="path">абсолютный путь к файлу</param>
/// </summary>
QString getFileLocation(char* path);

/*! Cчитывает данные с входного файла
\param[in] priceFilePath файл с количеством городов и стоимостью бензина в каждом городе
\param[in] routeFilePath файл с маршрутами между городами
\param[in] outputFilePath файл, в который будут записаны выходные данные
\param[out] cityNum количеством городов
\param[out] prices стоимост бензина в каждом городе
\param[out] routes маршрути между городов
\return успешность считание файла
*/
bool readFile(QString priceFilePath, QString routeFilePath, QString outputFilePath, int* cityNum, QStringList* prices, QStringList* routes);

/*! Получить содержание файла
\param[in] file файл для чтения
\throw ошибка при чтения
\return lines cчитанные строки файла
*/
QStringList getFileData(QString filePath) throw(int);

/*! Создать матрицу смежности
  \param[in] cityNum количество городов
  \param[in] routes маршруты между городами
  \param[out] routes_to_des маршруты от первого города до последнего
  \throw ошибка создание матрицу
*/
void makeMatrix(QStringList* routes_to_des, int cityNum, QStringList routes) throw(int);

/*! Находит кратчайший путь из первого города в последний
  \param[in] cityNum массив всех возможных маршрутов от первого города до последнего
  \param[in] routes_to_des маршруты от первого города до последнего
  \param[in] prices стоимость бензина в каждом городе
  \param[in] outputFilePath файл, в который будут записаны выходные данные
  \return Стоимость кратчайший путь из первого города в последний
*/
int calculateMinRoute(QStringList routes_to_des, QStringList prices);

/*! Записать выходные данные
  \param[in] filePath файл, в который будут записаны выходные данные
  \param[in] lines строки выходных данных
*/
void writeOutput(QString filePath, QStringList lines);

