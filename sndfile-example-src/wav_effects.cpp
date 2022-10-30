#include <iostream>
#include <vector>
#include <sndfile.hh>
#include "wav_hist.h"

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading frames

int main(int argc, char *argv[]) {

	if(argc < 3) {
		cerr << "Usage: " << argv[0] << " <input file> <channel>\n";
		return 1;
	}

	SndfileHandle sfhIn { argv[argc-2] };
	if(sfhIn.error()) {
		cerr << "Error: invalid input file\n";
		return 1;
    }

	if((sfhIn.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) {
		cerr << "Error: file is not in WAV format\n";
		return 1;
	}

	if((sfhIn.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) {
		cerr << "Error: file is not in PCM_16 format\n";
		return 1;
	}

	int channel { stoi(argv[argc-1]) };
	if(channel >= sfhIn.channels()) {
		cerr << "Error: invalid channel requested\n";
		return 1;
	}

	size_t nFrames;
	vector<short> samples(FRAMES_BUFFER_SIZE * sfhIn.channels());
	WAVHist hist { sfhIn };

	SndfileHandle sfhOut { "./effects.wav", SFM_WRITE, sfhIn.format(),
	  sfhIn.channels(), sfhIn.samplerate() };
	if(sfhOut.error()) {
		cerr << "Error: invalid output file\n";
		return 1;
    }



	vector<short> samples_echo(FRAMES_BUFFER_SIZE * sfhIn.channels());

	while((nFrames = sfhIn.readf(samples.data(), FRAMES_BUFFER_SIZE))) {
        for (size_t i = 0; i < samples.size();i++){
            samples_echo[i] = samples[i] + (0.2 * samples_echo[i]);		
        }
        sfhOut.writef(samples_echo.data(), nFrames);
	}
	

	hist.dump(channel);
	return 0;
}

