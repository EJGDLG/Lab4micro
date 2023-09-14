#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;
struct Producto {
    string nombre;
    double precioVenta;
    double costoFijo;
    int unidadesVendidasJulio;
    int unidadesVendidasAgosto;
    double ventasJulio;
    double ventasAgosto;
    double utilidadJulio;
    double utilidadAgosto;
};


void calcularVentasYUtilidad(Producto &producto, double costoVariableJulio, double costoVariableAgosto) {
    producto.ventasJulio = producto.precioVenta * producto.unidadesVendidasJulio;
    producto.utilidadJulio = producto.ventasJulio - (producto.costoFijo * producto.unidadesVendidasJulio + costoVariableJulio);

    this_thread::sleep_for(chrono::seconds(1));

    producto.ventasAgosto = producto.precioVenta * producto.unidadesVendidasAgosto;
    producto.utilidadAgosto = producto.ventasAgosto - (producto.costoFijo * producto.unidadesVendidasAgosto + costoVariableAgosto);
}

int main() {

    vector<Producto> productos = {
        {"Porcion pastel de chocolate", 10.0, 5.0, 100, 120},
        {"White mocha", 15.0, 7.0, 80, 90},
        {"Café americano 8onz", 20.0, 8.0, 60, 70},
        {"Latte 8onz", 25.0, 10.0, 40, 50},
        {"Toffee coffee", 30.0, 12.0, 30, 35},
        {"Cappuccino 8onz", 35.0, 15.0, 20, 25},
        {"S'mores Latte", 40.0, 18.0, 10, 12},
        {"Café tostado molido", 45.0, 20.0, 5, 6}
    };


    double costoVariableJulio = 45640.0;
    double costoVariableAgosto = 40590.0;


    vector<thread> threads;
    for (Producto &producto : productos) {
        threads.emplace_back(calcularVentasYUtilidad, ref(producto), costoVariableJulio, costoVariableAgosto);
    }

    for (thread &t : threads) {
        t.join();
    }

    // Imprimir resultados
    cout << "REPORTE DEL MES DE JULIO" << endl;
    cout << "Ventas por producto" << endl;
    for (const Producto &producto : productos) {
        cout << producto.nombre << ": Q" << producto.ventasJulio << endl;
    }
    cout << "Utilidad por producto" << endl;
    for (const Producto &producto : productos) {
        cout << producto.nombre << ": Q" << producto.utilidadJulio << endl;
    }

    double totalVentasJulio = 0.0;
    double totalUtilidadJulio = 0.0;

    for (const Producto &producto : productos) {
        totalVentasJulio += producto.ventasJulio;
        totalUtilidadJulio += producto.utilidadJulio;
    }

    cout << "Total ventas: Q" << totalVentasJulio << endl;
    cout << "Costos variables: Q" << costoVariableJulio << endl;
    cout << "Utilidad del mes: Q" << totalUtilidadJulio << endl;

    cout << "REPORTE DEL MES DE AGOSTO" << endl;
    cout << "Ventas por producto" << endl;
    for (const Producto &producto : productos) {
        cout << producto.nombre << ": Q" << producto.ventasAgosto << endl;
    }
    cout << "Utilidad por producto" << endl;
    for (const Producto &producto : productos) {
        cout << producto.nombre << ": Q" << producto.utilidadAgosto << endl;
    }

    double totalVentasAgosto = 0.0;
    double totalUtilidadAgosto = 0.0;

    for (const Producto &producto : productos) {
        totalVentasAgosto += producto.ventasAgosto;
        totalUtilidadAgosto += producto.utilidadAgosto;
    }

    cout << "Total ventas: Q" << totalVentasAgosto << endl;
    cout << "Costos variables: Q" << costoVariableAgosto << endl;
    cout << "Utilidad del mes: Q" << totalUtilidadAgosto << endl;

    return 0;
}
