#include <gtest/gtest.h>

#include <thread>
#include <chrono>

#include "platform/input/BaseInputEventManager.h"

using namespace Platform::Input;
using namespace Core::Errors;
using namespace Platform::System;

class TestInputManager : public BaseInputEventManager {
public:
	ErrorCode update(Phase phase) override {
		InputSnapshot input{};
		input.mouseX = i;
		setSnapshot(input);
		return ErrorCode();
	}

	void setI(int val) {
		this->i = val;
	}
private:
	int i = 0;
};

TEST(BaseInputManager, Init)
{
	TestInputManager inputMgr;

	ASSERT_TRUE(&inputMgr);
}

TEST(BaseInputManager, NormalUse)
{
	TestInputManager inputMgr;
	// Let's pretend that there is a engine running and its spinning a loop 
	// And is updating the input on an interval.
	auto engineThread = std::thread([&inputMgr]() {
		for (int i = 0; i <= 100; i++) {
			inputMgr.setI(i);
			// Hmm...why did i make the setSnapshot protected...
			// Ahhh...ok, so the class that will inherit from the base input manager
			// will poll from SDL, so that's why the setSnapshot method is protected.
			inputMgr.update(Phase::Input);

			// Simulating a usual frame update time
			std::this_thread::sleep_for(std::chrono::milliseconds(16));
		}
	});

	// Here we are simulating checking the snapshot state at some interval
	int prevMouseX = 0;
	for (int i = 0; i < 10; i++) {
		InputSnapshot s1 = inputMgr.getSnapshot();
		// it's hard to check specific points in time and their respective value...
		EXPECT_TRUE(s1.mouseX >= prevMouseX);
		prevMouseX = s1.mouseX;
		std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	engineThread.join();

	InputSnapshot finalSnapshot = inputMgr.getSnapshot();
	EXPECT_TRUE(finalSnapshot.mouseX == 100);
}
