#include <QCoreApplication>
#include"sever.h"



int sum(int x,int y){
    cout << "thread:"<<std::this_thread::get_id() << endl;
    return x+y;
}


void runtine(){

    thread_pool::pool p;
    int x = 10,y = 20;
    while(x < 100){
        auto res = p.enqueue(std::move(sum),x++,y++);
        res.wait();
        cout << res.get() << endl;
    }

}



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.
    //logger l;
    //l.log(runtype::ERROR,"error");
    runtine();
    return a.exec();
}
