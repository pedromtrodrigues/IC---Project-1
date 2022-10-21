#include <iostream>
#include <vector>
#include <sndfile.hh>
#include <cmath>

using namespace std;

constexpr size_t FRAMES_BUFFER_SIZE = 65536; // Buffer for reading frames

int main(int argc, char *argv[])
{

	if (argc < 3)
	{
		cerr << "Usage: " << argv[0] << " <input_wav> <inputCompressed_wav>" << endl;
		return 1;
	}

	SndfileHandle input_wav{argv[1]};
	SndfileHandle input_comp{argv[2]};

	if (input_wav.error() || input_comp.error())
	{
		cerr << "Error: invalid input file \n";
		return 1;
	}

	if (((input_wav.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV) || ((input_comp.format() & SF_FORMAT_TYPEMASK) != SF_FORMAT_WAV))
	{
		cerr << "Error: One of the files is not in WAV format\n";
		return 1;
	}

	if (((input_wav.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16) || ((input_comp.format() & SF_FORMAT_SUBMASK) != SF_FORMAT_PCM_16))
	{
		cerr << "Error: One of the files is not PCM_16 format\n";
		return 1;
	}

	vector<double> normal_file(FRAMES_BUFFER_SIZE * input_wav.channels());
	vector<double> comp_file(FRAMES_BUFFER_SIZE * input_comp.channels());

	size_t n_frames;
	size_t n_compframes;

	double t_samples = input_wav.channels() * input_wav.samplerate();
	double SNR;
	double temp_error = 0, max_error = 0, signal = 0, noise = 0;
	n_frames = input_wav.readf(normal_file.data(), FRAMES_BUFFER_SIZE);
	n_compframes = input_comp.readf(comp_file.data(), FRAMES_BUFFER_SIZE);
	do
	{
		normal_file.resize(n_frames * input_wav.channels());
		comp_file.resize(n_frames * input_comp.channels());
		int i = 0;
		while (i < int(normal_file.size()))
		{
			signal = signal + pow(abs(normal_file[i]), 2);
			temp_error = abs(normal_file[i] - comp_file[i]);
			noise = noise + pow(temp_error, 2);
			if (temp_error > max_error)
				max_error = temp_error;
			i++;
		}
	} while (n_frames = input_wav.readf(normal_file.data(), FRAMES_BUFFER_SIZE), n_compframes = input_comp.readf(comp_file.data(), FRAMES_BUFFER_SIZE));

	signal = 1 / totalSamples * signal;
	noise = 1 / totalSamples * noise;

	SNR = 10 * log10(signal / noise);
	cout << "SNR value: " << Snr << "\n";
	cout << "Max error per sample: " << max_error << "\n";

	return 0;
}
