#include <iostream>
#include <fstream>
#include <ctime>
#include <tchar.h>
#include <cstdlib>
#include <random>

std::vector<std::string> signals;
void signalInit(){
	signals.emplace_back("1011");
	signals.emplace_back("11010101");
	signals.emplace_back("110101101");
	signals.emplace_back("110101");
	signals.emplace_back("1");
	signals.emplace_back("10101101");
	signals.emplace_back("1101101");
	signals.emplace_back("1010101");
	signals.emplace_back("101");
	signals.emplace_back("1011011011");
	signals.emplace_back("1101011");
	signals.emplace_back("10110101");
	signals.emplace_back("11011");
	signals.emplace_back("1101");
	signals.emplace_back("11011011");
	signals.emplace_back("101101101");
	signals.emplace_back("1101101011");
	signals.emplace_back("101101");
	signals.emplace_back("10101");
	signals.emplace_back("11");
	signals.emplace_back("101011");
	signals.emplace_back("10101011");
	signals.emplace_back("1011011");
	signals.emplace_back("110101011");
	signals.emplace_back("1101011011");
	signals.emplace_back("110110101");
	return;
}



//one morse_code_nals are going to be about 1.3+-0.08
//zero morse_code_nals are going to be about 0.7+-0.08
double addNoise(double value){
	std::random_device rd;
	value-=0.08;
	value += (rd()%16000)/100000.0f;
	return value;
}

// we can just say when we
// get to the end begin writing from the start
// of the string again.
void writeSignal(TCHAR * filename){
	std::random_device rd;
	int random_num = rd()%26;
	std::cout << random_num << std::endl;
	std::string signal = signals[random_num];
	double time, intensity;
	int zerocount = 0, pos = 0;
	//append three terminating zeroes for spaces in between letters
	signal +=  "000";
	
	std::ofstream fout;
	fout.open(filename);
	

	for(int i = 0; i < 1000; i+=5){
		time = i/100.0f;//gives us our time value
		if(i%20 == 0){
			++pos;
			if(pos == signal.length()){
				pos = 0;
			}
		}
		if(signal[pos] == '1'){
			intensity = addNoise(1.3);
		}else{
			intensity = addNoise(0.7);
		}
		
		fout << time << " " << intensity << std::endl;
	}
	fout << "END" << std::endl;
	fout.flush();
	fout.close();
	
	return;

}



int main(int argc, TCHAR * args[]){
	if(argc ==1){
		std::cout << "Usage mCG <Output Filename>" << std::endl;
	}
	signalInit();
	writeSignal(args[1]);
}