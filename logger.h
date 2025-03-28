#ifndef LOGGER_H
#define LOGGER_H
#pragma once
#include<iostream>
#include<fstream>
#include<chrono>        //c++11
#include<string>
#include<iomanip>       //c++11
//#include<filesystem>    //c++17

using std::cout;
using std::endl;
using std::chrono::system_clock;
using std::string;
using std::ios;


namespace fs = std::filesystem;

namespace name{

inline string FILE_NAME="./log/log.txt";

}

namespace runtype{

inline string RUNNING="running:";
inline string DEBUG="debug:";
inline string WARNING="warning:";
inline string ERROR="error:";

}



//日志类 记录程序执行的状态
class logger
{
public:
    logger();

public:

    /**
    * @brief 向日志中写入信息
    * @param 日志种类
    * @param 日志内容
    * @return 无
    */
    void log(string& type,const string& info);

private:
    std::fstream file_log;              //日志文件
    time_t time;                        //时间戳变量
};

#endif // LOGGER_H
