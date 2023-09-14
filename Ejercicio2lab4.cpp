#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

const int capacidadSilo = 100;
const int capacidadBodega = 500;
int silo = 0;
int bodega = 0;

mutex mutexSilo;
mutex mutexBodega;
condition_variable cvSilo;
condition_variable cvBodega;

void tostadora1() {
    while (bodega < 400) {
        this_thread::sleep_for(chrono::seconds(1));
        
        {
            lock_guard<mutex> lock(mutexSilo);
            silo++;
            cout << "Tostadora 1 produjo: 1 lb de café tostada\n";
            cout << "Lbs de café en silo: " << silo << endl;
        }
        
        cvSilo.notify_one();
    }
}

void tostadora2() {
    while (bodega < 400) {
        this_thread::sleep_for(chrono::seconds(1));
        
        {
            lock_guard<mutex> lock(mutexSilo);
            silo++;
            cout << "Tostadora 2 produjo: 1 lb de café tostada\n";
            cout << "Lbs de café en silo: " << silo << endl;
        }
        
        cvSilo.notify_one();
    }
}

void empacadora() {
    while (bodega < 400) {
        unique_lock<mutex> lockSilo(mutexSilo);
        cvSilo.wait(lockSilo, []{ return silo >= 5; });

        this_thread::sleep_for(chrono::seconds(1));
        
        {
            lock_guard<mutex> lock(mutexBodega);
            silo -= 5;
            bodega += 1;
            cout << "Empacadora produjo: 1 bolsa de 1 lb de café\n";
            cout << "Lbs de café en bodega: " << bodega << endl;
        }
        
        cvBodega.notify_one();
    }
}

int main() {
    thread t1(tostadora1);
    thread t2(tostadora2);
    thread t3(empacadora);

    t1.join();
    t2.join();
    t3.join();

    cout << "Lbs de café en silo: " << silo << endl;
    cout << "Lbs de café en bodega: " << bodega << endl;

    return 0;
}
