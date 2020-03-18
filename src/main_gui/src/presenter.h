#ifndef Presenter_H
#define Presenter_H
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <i/idatacallback.h>
#include <tools/specstack.h>

class Presenter
{
public:
  ~Presenter();
  void setCallback(IDataCallback *in_callback);
  void removeCallback();

  // Set tasks from GUI:
  void setTask_fromGUI(Data_Decor *task);
private:
  std::atomic_bool keepRun { true };
  std::thread worker_thread;
  // Tasks:
  SpecSafeStack<Data_Decor> stack_GUItasks;

  // Results (mutex for sync workload with GUI):
  SpecQueue<Data_Decor> queue_Results;
  std::mutex worker_mutex;
  std::condition_variable worker_condition;

  bool stopWorker();
  static  void * s_workerWork(void  *arg, IDataCallback *in_callback);
  void l_workerWork(IDataCallback *in_callback);
  void parse_GUItasks();
  void sendResult_toGUI(IDataCallback *callback);

  // TODO del:
  void loadImg(Data_Decor *task1);
};
#endif //Presenter_H
