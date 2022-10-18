#ifndef WAVHIST_H
#define WAVHIST_H

#include <iostream>
#include <vector>
#include <map>
#include <sndfile.hh>
#include <fstream>

class WAVHist {
  private:
	std::vector<std::map<short, size_t>> counts;
	std::map<short,size_t> average;
	std::map<short,size_t> difference;
  public:
	WAVHist(const SndfileHandle& sfh) {
		counts.resize(sfh.channels());
	}

	void update(const std::vector<short>& samples) {
		size_t n { };
		for(auto s : samples)
			counts[n++ % counts.size()][s]++;
			
		for(size_t i=0;i < samples.size();i+=2) {
			short mid = (samples[i] + samples[i+1]) / 2;
			average[mid]++;
			short side = (samples[i] - samples[i+1]) / 2;
			difference[side]++;
		}
	}

	void dump(const size_t channel) const {
		for(auto [value, counter] : counts[channel])
			std::cout << value << '\t' << counter << '\n';
			
		std::ofstream outf;
		outf.open("./average.txt");
		for(auto [value, counter] : average)
			outf << value << '\t' << counter << '\n';
			
		outf.close();
							
		outf.open("./difference.txt");
		for(auto [value, counter] : difference)
			outf << value << '\t' << counter << '\n';
		
	}
};

#endif

