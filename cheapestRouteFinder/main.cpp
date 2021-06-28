#include <QtCore/QCoreApplication>
#include <conio.h>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <iostream>
#include "functions.h"


/*! функция, решающая главную задачу
\param[in] priceFilePath путь к файлу с количеством городов и стоимостью бензина в каждом городе
\param[in] routeFilePath путь к файлу с маршрутами между городами
\param[in] outputFilePath путь к файлу, в который будут записаны выходные данные
\param[out] outputFile файл, c выходными данными
*/
int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QStringList error;
    QStringList prices;
    QStringList routes;
    QStringList routes_to_des;
    int cityNum;
    int cheapest;

    char path[14] = "errorFile.txt";
    QString errorFilePath = getFileLocation(path);
    QStringList string;
    QFile errorFile("errorFile.txt");


    // если указаны не все параметры командной строки - записать в «errorFile.txt»  файл ошибку и закончить работу программы;
    if (argc < 4)
    {
        string.append("Insuficient parameters!!! ");

        writeOutput(errorFilePath, string);
        errorFile.close(); //закрить файл
        return 0;
    }
    // получить абсолютный пути к файлам

    QString priceFilePath = getFileLocation(argv[1]);
    QString routeFilePath = getFileLocation(argv[2]);
    QString outputFilePath = getFileLocation(argv[3]);
    QFile outputFile(outputFilePath);

    if (!outputFile.open(QIODevice::WriteOnly)) // если невозможно создать или открыть указанный выходной файл;
    {
        //записать в «errorFile.txt»  файл что неверно указан файл для выходных данных.Возможно указанного расположения не существует;
        string.append("Cannot open or create output file!!!");
        writeOutput(errorFilePath, string);

        return 0;
    }

    //-------------------------- считать входные данные из файла(readFile) -----------------------------------------------------------
    if (readFile(priceFilePath, routeFilePath, outputFilePath, &cityNum, &prices, &routes))//при удачном чтении файлов
    {

        if (cityNum <= 1) // если количество городов равен один;
        {
            // записать в выходной файл что Есть только один город, нет никакого маршрута
            error.append("Number of cities should be more than 1");
            writeOutput(outputFilePath, error);
            return 0; // завершить работу программы;
        }
        else if (cityNum > prices.size())
        {
            // записать в выходной файл что список цен на бензин неполон
            error.append("Price of petrol in some city or cities missing!!!");
            writeOutput(outputFilePath, error);
            return 0; // завершить работу программы;
        }
        else if (cityNum < prices.size())
        {
            // записать в выходной файл что список цен на бензин неполон
            error.append("Price of petrol exceeded the number of cities!!!");
            writeOutput(outputFilePath, error);
            return 0; // завершить работу программы;
        }
        try
        {
            // пробовать cоздать матрицу смежности городов и пути между городами(makeMatrix);
            makeMatrix(&routes_to_des, cityNum, routes); // при удачном cоздание матрицу;

            // рассчитать самый дешевый маршрут от первого города до  последнего;
            cheapest = calculateMinRoute(routes_to_des, prices);

            QTextStream stream(&outputFile);

            stream << cheapest << endl;

            outputFile.close(); // закрыть выходной файл;

            //return 0;// завершить работу программы;
        }
        // при неудачном cоздание матрицу;
        catch (int err) // ловить ошибки;
        {
            switch (err)
            {
            case 1:// при возникновении ошибки № 1,
                //записать в выходной файл, что маршруты должны быть среди заявленных городов
                error.append("Routes should be among cities");
                writeOutput(outputFilePath, error);
                break; //завершить работу программы;
            case 2: // при возникновении ошибки № 2
                //записать в выходной файл, что нет никакого маршрута от первого до последнего города
                error.append("There is no route to the last city");
                writeOutput(outputFilePath, error);
                break; //завершить работу программы;
            }
            return 0;
        }
    }
    // при неудачном чтении файлов
    //return 0; //завершить работу программы;
}

