#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include"logger.h"
#include<thread>            //线程 c++11
#include<vector>            //stl vector
#include<queue>             //stl queue
#include<functional>        //funtion c++11
#include<condition_variable>        //condition_variable c++11
#include<future>
#include<mutex>
#include<iostream>

using std::vector;
using std::thread;
using std::queue;
using std::condition_variable;
using std::mutex;
using std::function;
using std::cout;
using std::endl;



namespace thread_pool{


/**
 * 线程池功能概述
 *  1.管理线程(线程创建、销毁、挂起)
 *  2.任务队列
 *  3.任务执行
 *
 *
 */
class pool
{
public:

    /**
     * @brief 线程池创建和线程执行函数定义
     * @param 获取硬件支持的线程数 预留4个线程用于数据库或者日志等其他操作
     * @return 无
    */
    pool(int threads = thread::hardware_concurrency()-4);

    /**
    * @brief 将不同参数和返回值的函数封装成void()类型并放入任务队列
    * @param 函数指针
    * @param 函数变长参数
    * @return 函数指针指向的函数返回值的期物
    */
    template<typename F,typename... Args>
    auto enqueue(F&& f,Args&&... args) ->std::future<std::invoke_result_t<F,Args...>>{

        //返回值类型别名
        using return_type = std::invoke_result_t<F,Args...>;

        //函数封装成packaged_task
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f),std::forward<Args>(args)...));

        //返回值封装成期物
        std::future<return_type> res = task->get_future();

        //添加到任务队列
        std::unique_lock<mutex> lock(queue_lock);
        task_list.emplace([task](){(*task)();});
        lock.unlock();

        //唤醒线程
        condition.notify_one();
        return res;
    };

    /**
     * @brief 回收所有线程
     * @param 无
     * @return 无
     */
    ~pool();

    pool(const pool&) = delete;
    pool& operator=(const pool&) = delete;
private:

    vector<thread> workers;      //线程向量组
    queue<function<void()>> task_list;  //任务队列
    condition_variable condition;   //条件变量
    mutex queue_lock;   //任务队列锁
    int max_thread;     //线程池中线程数
    bool stop;          //线程池停止标志位
};

}





#endif // THREAD_POOL_H
