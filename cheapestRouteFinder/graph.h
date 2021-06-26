#pragma once

#include <iostream>
#include <list>
#include <QTextStream>
using namespace std;

class Graph
{
    private:

        /// <summary>
        /// Количество вершин в графе
        /// </summary>
        int V;

        /// <summary>
        /// Рекурсивная функция, используемая getAllRoutes()
        /// </summary>
        void getIndRoutes(QStringList* routes_to_dec, int, int, bool[], int[], int&);

    public:
        /// <summary>
        /// Ориентированный график с использованием
        /// представление списка смежности
        /// </summary>
        /// <param name="V">Количество городов. В первой строке файла цен на бензин</param>
        Graph(int V);

        /// <summary>
        /// Указатель на массив, содержащий списки смежности
        /// </summary>
        list<int>* adj;

        /// <summary>
        /// Coздает маршрут между двумя точками
        /// Добавляет v в список u.
        /// </summary>
        /// <param name="u">исходная точка</param>
        /// <param name="v">пункт назначения</param>
        void addEdge(int u, int v);

        /// <summary>
        /// Получаает все маршруты между первым и последним городом
        /// </summary>
        /// <param name="cityNum">Кол-во городов</param>
        void getAllRoutes(QStringList* routes_to_dec, int cityNum);
};
