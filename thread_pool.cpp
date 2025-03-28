#include "thread_pool.h"

thread_pool::pool::pool(int threads) : stop(false){

    this->max_thread = threads;
    for(int i = 0;i< max_thread;i++){

        workers.emplace_back([this](){

            for(;;){
                function<void()> task;

                {
                    std::unique_lock<mutex> lock(this->queue_lock);

                    //线程终止或者队列不为空则向下执行
                    this->condition.wait(lock,[this](){
                        return (this->stop || !this->task_list.empty());
                    });

                    //满足停止条件 结束线程
                    if(this->stop && this->task_list.empty()){
                        return;
                    }

                    //取任务
                    task=std::move(this->task_list.front());
                    this->task_list.pop();
                    lock.unlock();
                }
                task();
            }
        });
    }
};


thread_pool::pool::~pool(){

    std::unique_lock<mutex> lock(queue_lock);
    stop = true;

    condition.notify_all();
    lock.unlock();
    for(std::thread& worker : workers){
        worker.join();
    }
}




