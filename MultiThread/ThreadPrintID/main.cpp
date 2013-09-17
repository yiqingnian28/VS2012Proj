#include"thread_wrapper.h"
#include<Windows.h>
#include<iostream>

using namespace std;

struct Params{
	char _char;
	void* _hEventToWait;
	void* _hOnPrintEvent;
};

unsigned int _stdcall threadFunc(lh::ThreadWrapper::ThreadFuncParameterType param){
	lh::ThreadWrapper* t = static_cast<lh::ThreadWrapper*>(param);
	for(int i =0; i<10; i++){
		WaitForSingleObject(((Params*)t->_param)->_hEventToWait, INFINITE);
		cout << ((Params*)t->_param)->_char << ',';

		ResetEvent(((Params*)t->_param)->_hEventToWait);
		SetEvent(((Params*)t->_param)->_hOnPrintEvent);
	}
	return 0;
}




int main(){
	
	void* hEventA =  CreateEvent(NULL, TRUE, FALSE, NULL); //not triggered
	void* hEventB =  CreateEvent(NULL, TRUE, FALSE, NULL); //not triggered
	void* hEventC =  CreateEvent(NULL, TRUE, TRUE, NULL); //triggered

	Params a;
	a._char = 'A';
	a._hEventToWait = hEventC;
	a._hOnPrintEvent = hEventA;
	lh::ThreadWrapper threadA(threadFunc, (void *)&a);
	threadA.start();


	Params b;
	b._char = 'B';
	b._hEventToWait = hEventA;
	b._hOnPrintEvent = hEventB;
	lh::ThreadWrapper threadB(threadFunc, (void *)&b);
	threadB.start();

	Params c;
	c._char = 'C';
	c._hEventToWait = hEventB;
	c._hOnPrintEvent = hEventC;
	lh::ThreadWrapper threadC(threadFunc, (void *)&c);
	threadC.start();

	unsigned int obj[] = {threadA.getHandle(),
					threadB.getHandle(),
					threadC.getHandle()};



	WaitForMultipleObjects(3, (HANDLE*)obj, true, INFINITE);
	
	CloseHandle(hEventA);
	CloseHandle(hEventB);
	CloseHandle(hEventC);

	for(int i=0; i<3; i++){
		CloseHandle((HANDLE)obj[i]);
	}

	system("pause");
	return 0;
}