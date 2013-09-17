#ifndef _THREAD_WRAPPER_LH_
#define _THREAD_WRAPPER_LH_

#include<process.h>
#include<iostream>
namespace lh{

class ThreadWrapper {
public:
	typedef void* ThreadFuncParameterType;
	typedef unsigned int  (_stdcall *ThreadFuncType)(ThreadFuncParameterType);

	ThreadFuncParameterType _param;
public:
	ThreadWrapper(ThreadFuncType func, 
				  ThreadFuncParameterType param): 
				  _func(func), 
				  _param(param){}

	void start(){
		_handle = _beginthreadex(0, 
					   0,
					   run,
					   (void*)this,
					   0,
					   &_id);

	}

	int id(){
		return _id;
	}

	unsigned int getHandle(){
		return _handle;
	}

private:
	static unsigned int _stdcall run(void* param){
		ThreadWrapper *t = static_cast<ThreadWrapper*>(param);
//		std::cout << "Thread#" << t->_id << "#:";
		t->_func(param);	
		return 0;
	}



private:
	unsigned int _handle;
	ThreadFuncType _func;
	unsigned int _id;

};

};//namespace

#endif