#include <QtTest>
#include "../cheapestRouteFinder/functions.h"
#include <iostream>
//#include "../cheapestRouteFinder/graph.h"

// add necessary includes here

class TestRouteFinder : public QObject
{
    Q_OBJECT

private slots:
    void test_calculateMinRoute_connected();
    void test_calculateMinRoute_singleconnected();
    void test_calculateMinRoute_manyconnected();
    void test_calculateMinRoute_notconnected();

    void test_getAllRoutes_connected();
    void test_getAllRoutes_notconnected();
    void test_getAllRoutes_singleconnection();
    void test_getAllRoutes_manyconnection();

    void test_addEdge1();
    void test_addEdge2();

};

void TestRouteFinder::test_calculateMinRoute_connected()
{
    int ex_cheapest = 11;
    QStringList routes_to_des = {"1","2","3","4","6","-","1","2","3","6","-","1","4","3","6","-"};
    QStringList prices = {"3","4","6","2","7","8"};

    int cheapest = calculateMinRoute(routes_to_des, prices);

    Q_ASSERT(ex_cheapest == cheapest);
}

void TestRouteFinder::test_calculateMinRoute_singleconnected()
{
    int ex_cheapest = 9;
    QStringList routes_to_des = {"1","3","6","-"};
    QStringList prices = {"3","4","6","2","7","8"};

    int cheapest = calculateMinRoute(routes_to_des, prices);

    Q_ASSERT(ex_cheapest == cheapest);
}

void TestRouteFinder::test_calculateMinRoute_manyconnected()
{
    int ex_cheapest = 8;
    QStringList routes_to_des = {"1","2","5","6","-","1","3","6","-","1","3","4","6","-"};
    QStringList prices = {"3","4","5","6","7","8"};

    int cheapest = calculateMinRoute(routes_to_des, prices);

    Q_ASSERT(ex_cheapest == cheapest);
}

void TestRouteFinder::test_calculateMinRoute_notconnected()
{
    int ex_cheapest = 0;
    QStringList routes_to_des = {};
    QStringList prices = {"3","4","6","2","7","8"};

    int cheapest = calculateMinRoute(routes_to_des, prices);

    Q_ASSERT(ex_cheapest == cheapest);
}

void TestRouteFinder::test_getAllRoutes_connected()
{
    int cityNum = 6;
    Graph matrix(cityNum);
    int routes[] = {1,2,1,4,2,3,3,4,3,6};
    QStringList ex_routes_to_des = {"1","2","3","6","-","1","4","3","6","-"};
    QStringList routes_to_des;

    for(int i=0; i < 10; i ++)
    {
        int u = routes[i];
        int v = routes[i + 1];
       matrix.addEdge(u - 1, v - 1);
       matrix.addEdge(v - 1, u - 1);
       i += 1;
    }

    matrix.getAllRoutes(&routes_to_des, cityNum - 1);

    QCOMPARE(routes_to_des, ex_routes_to_des);

}

void TestRouteFinder::test_getAllRoutes_singleconnection()
{
    int cityNum = 6;
    Graph matrix(cityNum);
    int routes[] = {1,2,2,3,3,4,3,5,5,6};
    QStringList ex_routes_to_des = {"1","2","3","5","6","-"};
    QStringList routes_to_des;

    for(int i=0; i< 10; i ++)
    {
        int u = routes[i];
        int v = routes[i + 1];
       matrix.addEdge(u - 1, v - 1);
       matrix.addEdge(v - 1, u - 1);
       i += 1;
    }

    matrix.getAllRoutes(&routes_to_des, cityNum - 1);

    QCOMPARE(routes_to_des, ex_routes_to_des);

}

void TestRouteFinder::test_getAllRoutes_manyconnection()
{
    int cityNum = 6;
    Graph matrix(cityNum);
    int routes[] = {1,2,1,4,1,5,2,3,3,4,3,5,3,6,4,6,5,6};
    QStringList ex_routes_to_des = {"1","2","3","4","6","-","1","2","3","5","6","-",
                                    "1","2","3","6","-","1","4","3","5","6","-",
                                    "1","4","3","6","-","1","4","6","-",
                                    "1","5","3","4","6","-","1","5","3","6","-","1","5","6","-"};
    QStringList routes_to_des;

    for(int i=0; i < 18; i ++)
    {
        int u = routes[i];
        int v = routes[i + 1];
       matrix.addEdge(u - 1, v - 1);
       matrix.addEdge(v - 1, u - 1);
       i += 1;
    }

    matrix.getAllRoutes(&routes_to_des, cityNum - 1);

    QCOMPARE(routes_to_des, ex_routes_to_des);
}

void TestRouteFinder::test_getAllRoutes_notconnected()
{
    int cityNum = 6;
    Graph matrix(cityNum);
    int routes[] = {2,3,3,4,3,6};
    QStringList ex_routes_to_des = {};
    QStringList routes_to_des;

    for(int i=0; i < 6; i ++)
    {
        int u = routes[i];
        int v = routes[i + 1];
       matrix.addEdge(u - 1, v - 1);
       matrix.addEdge(v - 1, u - 1);
       i += 1;
    }

    matrix.getAllRoutes(&routes_to_des, cityNum - 1);

    QCOMPARE(routes_to_des, ex_routes_to_des);

}

void TestRouteFinder::test_addEdge1()
{
    int cityNum = 6;
    Graph matrix(cityNum);
    list<int>* expected;
    int routes[] = {1,2,1,4,2,3,3,4,3,6};

    expected = new list<int>[6];

    for(int i=0; i< 10; i ++)
    {
        int u = routes[i];
        int v = routes[i + 1];
       expected[u - 1].push_back(v - 1);
       expected[v - 1].push_back(u - 1);
       matrix.addEdge(u - 1, v - 1);
       matrix.addEdge(v - 1, u - 1);
       i += 1;
    }

    QCOMPARE(matrix.adj->size(), expected->size());

}

void TestRouteFinder::test_addEdge2()
{
    int cityNum = 6;
    Graph matrix(cityNum);
    list<int>* expected;
    int routes[] = {1,2,1,4,1,5,1,6};

    expected = new list<int>[6];

    for(int i=0; i< 8; i ++)
    {
        int u = routes[i];
        int v = routes[i + 1];
       expected[u - 1].push_back(v - 1);
       expected[v - 1].push_back(u - 1);
       matrix.addEdge(u - 1, v - 1);
       matrix.addEdge(v - 1, u - 1);
       i += 1;
    }

    QCOMPARE(matrix.adj->size(), expected->size());

}

QTEST_APPLESS_MAIN(TestRouteFinder)

#include "tst_testroutefinder.moc"
