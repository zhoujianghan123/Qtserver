#include "logger.h"

logger::logger() {

    //文件验证
    file_log.open(name::FILE_NAME,ios::in|ios::out|ios::app);
    if(!file_log.is_open()){
        file_log.close();
        cout << "open file failed"<< endl;
        return;
    }
    file_log.close();
}


void logger::log(string& type,const string& info){

    file_log.open(name::FILE_NAME,ios::in|ios::out|ios::app);
    if(!file_log.is_open()){
        file_log.close();
        cout << "open file failed"<< endl;
        return;
    }

    time = system_clock::to_time_t(std::move(system_clock::now()));     //获取当前时间戳
    file_log << std::put_time(std::localtime(&time),"%c\t")             //日志输出
             << type << "\t" << info << "\n";
    file_log.close();

}

