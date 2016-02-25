#include <iostream>

#include "Windows/WindowFunctions.h"

void resetInputs(void *In, unsigned int Length){
	for(unsigned int i = 0; i < Length; i++){
		In[i] = 1;
	}
}

bool HanningTest(WindowFunctions *wf, void* in, void* out, unsigned int Length){
	wf->initHanning_32f(Length);
	wf->applyWindow((float*)in, Length, (float*)out, Length);
	wf->applyWindow((float*)in, Length);

	bool pass = true;
	for(unsigned int i = 0; i < Length; i++){
		pass &= (in[i] == out[i]);
	}
}

int main(int argv, char* args[]){
	unsigned int Length = 16;


	WindowFunctions wf;

	float *f_Input = new float[Length];
	float *f_Output = new float[Length];

	double *d_Input = new double[Length];
	double *d_Output = new double[Length];

	bool tests = true;

	resetInputs(f_Input, Length);
	if(!HanningTest(&wf, f_Input, f_Output, Length)){
		std::cout << "Hanning test failed!";
	}

	return 0;
}
