#include <windows.h>
#include <cstddef>
#include <vector>
#include <thread>
#include <random>
#include <ctime>

// thanks ChatGPT
const char* errorMessages[] = {
    "Welcome to the Miserable Fail Program!",
    "Loading failed! Please wait forever.",
    "Error: Coffee not found! Insert coffee and try again.",
    "Out of cheese error. Redo from start.",
    "Error: The system is overloaded with happiness. Please try again later.",
    "Error: Windows has detected a keyboard error. Press 'F' to pay respects.",
    "Error: Your computer has been infected by a dancing virus. Please dance along.",
    "Error: Your mouse has been replaced by a cat. Please pet the cat to continue.",
    "Error: Insufficient laughter. The program will now terminate."
};

void setPlaySound()
{
	static std::mt19937 rgen(std::time(nullptr));
	const char *errs[] = {
		"C:\\Windows\\Media\\Critical Stop.wav",
		"C:\\Windows\\Media\\Windows Error.wav"
	};
	PlaySoundA(errs[rgen() % (sizeof(errs) / sizeof(errs[0]))], NULL, SND_FILENAME | SND_ASYNC);
}

void displayErrorMessage(const char* message)
{
	static std::mt19937 rgen(std::time(nullptr));
	
	// add some nice style
	UINT tp = MB_TASKMODAL | MB_RTLREADING | MB_SETFOREGROUND | MB_RIGHT;
	
	const UINT tps[] = {
		MB_ABORTRETRYIGNORE,
		MB_CANCELTRYCONTINUE,
		MB_HELP,
		MB_OK,
		MB_OKCANCEL,
		MB_RETRYCANCEL,
		MB_YESNO,
		MB_YESNOCANCEL
	};
	
	const UINT ics[] = {
		MB_ICONEXCLAMATION,
		MB_ICONWARNING,
		MB_ICONINFORMATION,
		MB_ICONASTERISK,
		MB_ICONQUESTION,
		MB_ICONSTOP,
		MB_ICONERROR,
		MB_ICONHAND
	};
	
	// pick random set of buttons and icons for the messagebox
	tp |= rgen() % sizeof(tps) / sizeof(tps[0]);
	tp |= rgen() % sizeof(ics) / sizeof(ics[0]);
	
	// repeat the message random number of times
	// (this also adds some lag =))) )
	std::string box(message);
	int r = rgen() & 0xFFF;
	while (r) {
		if (r & 1)
			box += message;
		r >>= 1;
	}
	
    MessageBox(NULL, box.c_str(), message, tp);
	setPlaySound();
	
	if (rgen() % 32 == 0)
		exit(*(int*)nullptr);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	std::vector<std::thread> threads;
	
	for (int i = 0; i < 20; ++i)
	{
		for (const char* errorMessage : errorMessages)
		{
			threads.emplace_back(displayErrorMessage, errorMessage);
			setPlaySound();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	}
	
	for (auto& thr : threads)
		thr.join();
	
	int i = 0;
	int j = 0;
	
	return *(int*)nullptr;
}
