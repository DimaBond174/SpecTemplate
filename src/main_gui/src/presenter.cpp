#include "presenter.h"
// #include "signals/Magic.h"
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <i/itasks/itask1.h>

Presenter::~Presenter()
{
  stopWorker();
}

bool Presenter::stopWorker()
{
  bool re = false;
  keepRun.store(false, std::memory_order_release);
  try {
    if (worker_thread.joinable())
    {
      worker_thread.join();
    }
    re = true;
  } catch (...) {

  }

  return re;
} // stopWorker

void Presenter::setCallback(IDataCallback *in_callback)
{
    if (stopWorker())
    {
      keepRun.store(true, std::memory_order_release);
      worker_thread = std::thread(&Presenter::s_workerWork,  this, in_callback);
    }
    return;
} //setCallback

void Presenter::removeCallback()
{
  stopWorker();
} //removeCallback

void * Presenter::s_workerWork(void  *arg, IDataCallback *in_callback)
{
  Presenter  *p  =  static_cast<Presenter*>(arg);
  p->l_workerWork(in_callback);
  return nullptr;
} //s_workerWork

void Presenter::l_workerWork(IDataCallback *callback)
{
  try {
    std::unique_lock<std::mutex> lk(worker_mutex);
    while (keepRun.load(std::memory_order_acquire) )
    {
      // Send ready results to GUI
      sendResult_toGUI(callback);
      // Send tasks to work
      parse_GUItasks();

      worker_condition.wait_for(lk, std::chrono::milliseconds(100));
    } // while (keepRun
  } catch (...) {

  }
  // TODO clear containers
  keepRun.store(false, std::memory_order_release);
  return;
} //l_workerWork


void Presenter::setTask_fromGUI(Data_Decor *task)
{
  stack_GUItasks.push(task);
} //setTask_fromGUI

void Presenter::parse_GUItasks()
{
  SpecStack<Data_Decor> list;
  list.swap(stack_GUItasks.getReverse());
  while  (Data_Decor *data = list.pop()) {
    switch (data->type) {
    case 1:
      loadImg(data);
      queue_Results.add_head(data);
      break;
    default:
      break;
    }
  }
  return;
} // parse_GUItasks


void Presenter::sendResult_toGUI(IDataCallback *callback)
{
  for (Data_Decor *data = queue_Results.pop_tail();
       data && keepRun.load(std::memory_order_acquire);
       data = queue_Results.pop_tail())
  {
    callback->onCallResult(data);
  }
} // sendResult_toGUI


void Presenter::loadImg(Data_Decor *task1)
{
  if (Data_Decor::isValid(task1))
  {
    task1->res = -1;
    ITask1 *task = static_cast<ITask1 *>(task1->source_data);
    if (ITask1::isValid(task))
    {
      cv::Mat image = cv::imread(task->filename, cv::IMREAD_COLOR);
      if (!image.empty())
      {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
        ITask1_Result *res = ITask1_Result::newObj();
        res->mat_cols = image.cols;
        res->mat_rows = image.rows;
        const int len = image.cols * image.rows * 3;
        res->mat_data = static_cast<unsigned char *>(malloc(len));
        memcpy(res->mat_data, image.data, len);
        task1->res_data = res;
        task1->res = 1;
      }
    }
  } //if

} //loadImg
