#include <iostream>
#include <Windows.h>
#include <random>
#include <thread>

bool config = true;
bool enabled = false;
std::string status = "enabled";
POINT pt;
HWND window;
int min_delay;
int max_delay;


inline int random_int(int min, int max) {
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(generator);
}

int main()
{
	std::cout << "simple autoclicker\n\n";
	std::cout << "config: \n\n";
	std::cout << "toggle: Z\n";

	if (config) {
		std::cout << "min delay in ms: ";
		std::cin >> min_delay;
		std::cout << "max delay in ms: ";
		std::cin >> max_delay;
		if (min_delay > max_delay) {
			std::cout << "\n\n min delay is greater than max delay \n";
			exit(0);
		}
		config = false;
	}
	if (std::cin.fail()) { std::cout << "\n\ninput a number\n"; exit(0); }

	while (true) {
		if (!config) {

			window = GetForegroundWindow();

			if (GetAsyncKeyState(0x5A) & 1) {
				enabled = !enabled;
				for (int i = 0; i < status.length(); i++) {
					std::cout << "\b";
				}
				if (!enabled) { status = "disabled "; std::cout << status; }
				else if (enabled) { status = "enabled "; std::cout << status; }
			}

			if (enabled) {
				if (GetAsyncKeyState(1)) {

					GetCursorPos(&pt);
					Sleep(random_int(min_delay, max_delay));
					PostMessage(window, WM_LBUTTONDOWN, MKF_LEFTBUTTONDOWN, LPARAM((pt.x, pt.y)));
					Sleep(random_int(min_delay, max_delay));
					PostMessage(window, WM_LBUTTONUP, 0, LPARAM((pt.x, pt.y)));
				}
				else { Sleep(1); }
			}
			else { Sleep(1); }
		}
	}
}