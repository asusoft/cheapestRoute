#include "functions.h"

QString getFileLocation(char* path)
{
    QString result(path);
    // Если введенная строка содержит “\”;
    if (result.contains(R"(\)"))
        result.replace(R"(\)", R"(/)"); // заменить “\” на “ / ”;

    // Если введенная строка начинается с “.”;
    if (result.startsWith(QChar('.')))
        result = QDir::currentPath() + result.mid(1); // заменить “.” На текущий путь программы;

    // Return path, абсолютный путь к файлу;
    return result;
}

bool readFile(QString priceFilePath, QString routeFilePath, QString outputFilePath, int* cityNum, QStringList* prices, QStringList* routes)
{
    QStringList error;

    try //попробуйте открыть и прочитать все содержимое файлов по одному;
    {
        *cityNum = getFileData(priceFilePath)[0].toInt(); // попробуйте открыть файл цены, чтобы получить его первую строку(представляющую количество городов);
        *prices = getFileData(priceFilePath)[1].split(QChar(' ')); // попробуйте открыть файл цены, чтобы получить его вторую строку(представляющую стоимость бензина в кождом городе);
        *routes = getFileData(routeFilePath); // попробуйте открыть файл маршруты, чтобы получить все маршруты между городами;

        return true; // если нет ощибки при счтение файлов, return true (указывает на то, что файлы были успешно прочитаны);
    }
    catch (int i) // ловить ошибки при чтении файлов;
    {
        switch (i)
        {
        case 1: // при возникновении ошибки № 1, записать в выходной файл, что один или оба файла не существуют;
            error.append("One or both of the files does not exist!!!");
            writeOutput(outputFilePath, error);
            break;
        case 2: // при возникновении ошибки № 2, записать в выходной файл, что в одном или обоих файлах чего - то не хватает или что - то введено неправильно;
            error.append("Something is missen in the file or it is entered incorrectly!!!");
            writeOutput(outputFilePath, error);
            break;
        case 3: // при возникновении ошибки № 3, записать запишите в выходной файл, что Один или оба файла не могут быть открыты;
            error.append("Cannot open one or both of the files!!!");
            writeOutput(outputFilePath, error);
            break;
        }
        return false; // return false (указывает на то, что файлы не были успешно прочитаны);
    }
}

QStringList getFileData(QString filePath) throw(int)
{
    QStringList string;
    QFile inputFile(filePath);

    QRegExp re("[0-9 ]+");
    //|| !re.exactMatch(line)

    //---------------открыть файл--------------------------//

    if (!inputFile.exists()) //если файл не существует, выбросить исключение в целочисленном типе(1);
    {
        throw 1;
    }
    else // если файл существует;
    {
        if (inputFile.open(QIODevice::ReadOnly)) //если открыть не удалось;
        {
            QTextStream in(&inputFile);
            while (!in.atEnd()) // пока строки файла не заканчивались;
            {
                QString line = in.readLine(); //считать текущую строку

                if (line.isEmpty() || !re.exactMatch(line)) //если стока пустая или введен неправильно - выбросить исключение в целочисленном типе(2);
                {
                    //выдайте сообщение об ошибке и завершите работу
                    throw 2;
                }
                else
                {
                    string.append(line); //сохранить текущую строку;
                }
            }
            inputFile.close(); //закрить файл
        }
        else //если открыть не удалось - выбросить исключение в исключение в целочисленном типе(3);
        {
            throw 3;
        }
    }
    return string; //return сохраненные строки
}

void makeMatrix(QStringList* routes_to_des, int cityNum, QStringList routes) throw(int)
{
    QList<int> routesLine;

    Graph matrix(cityNum); //Создайте граф с числом вершин равным числу городов
    QStringList routesElements = routes[0].split(QChar(' ')); //Создайте список номеров, разделив маршруты пробелом

    for (int i = 1; i < routesElements.length(); i++)
    {

        for (int j = 0; j < routesElements.length(); j++)
        {
            routesLine.append(routesElements[j].toInt());
        }
    }

    for (int i = 0; i < routesElements.length(); i++)//для всех элементов списка;
    {
        //если текущий или следующий элемент больше количества городов - выбросить исключение в исключение в целочисленном типе(1);
        if (routesLine[i] > cityNum || routesLine[i + 1] > cityNum)
        {
            throw 1;
        }
        // установить текущий и следующий элементы на ребра графика
        int u = routesLine[i];
        int v = routesLine[i + 1];
        matrix.addEdge(u - 1, v - 1);
        matrix.addEdge(v - 1, u - 1);
        i += 1; //пропустисть следующий элемент и перейдите к элементу после него
    }

    matrix.getAllRoutes(routes_to_des, cityNum - 1); //получить все маршруты от первого города до последнего

    if (routes_to_des->size() == 0) // если нет маршрута от первого города до последнего - выбросить исключение в исключение в целочисленном типе(2);
    {
        throw 2;
    }
}

int calculateMinRoute(QStringList routes_to_des, QStringList prices)
{
    QList<int> priceList;
    QList<int> routeList;
    QList<int> minRoute;
    int m = 0;

    if(routes_to_des.size() < 1)
    {
        return 0;
    }

    QStringList routesElements = routes_to_des[0].split(' ');

    for (int j = 0; j < prices.length(); j++)
    {
        priceList.append(prices[j].toInt());
    }

    for (int j = 0; j < routes_to_des.length(); j++)
    {
        routeList.append(routes_to_des[j].toInt());
    }

    //для всех маршруты от первого города до последнего;
    for (int l = 0; l < routeList.length(); l++)
    {
        if (routeList[l] != 0) // если текущий элемент маршрута (отдельный город) не равен нулю
        {
            m += priceList[routeList[l] - 1]; // добавлять цену бензина в текущем городе к цене бензина для маршрута
        }
        else // иначе
        {
            m -= priceList[priceList.length() - 1]; // вычитать цену бензина в последнем городе из цены бензина для маршрута
            minRoute.append(m); // сохранить текущую цену на бензин для маршрута
            m = 0;
        }
    }

    //установить минимальную цену бензина для маршрута от первого до последнего города в качестве цены первого маршрута;
    int minimum = minRoute[0];
    for (int l = 0; l < minRoute.length(); l++) //для всех цен на бензин по маршруту от первого до последнего города
    {
        // установите минимальную цену бензина для маршрута от первого до последнего города как минимум между текущим минимумом и текущей ценой
        minimum = min(minimum, minRoute[l]);
    }

    return minimum;
}

void writeOutput(QString filePath, QStringList lines)
{
    QFile outputFile(filePath);

    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) // открыть файл;
    {
        QTextStream stream(&outputFile);

        for (int i = 0; i < lines.length(); i++) //для всех строк выходных данных;
            stream << lines[i] << endl; //записать строку в выходной файл;

        outputFile.close(); // закрыть файл;
    }
}
