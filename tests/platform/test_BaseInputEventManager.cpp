#include <gtest/gtest.h>

#include "platform/input/BaseInputEventManager.h"

using namespace Platform::Input;

class TestInputManager : public BaseInputEventManager {
public:
	TestInputManager() {
		// Here we can have a jthread run and call setSnapshot on a 
		// interval
		// The test will then call getSnapshot and should receive valid data.
		// Let's say that there will be a final event with a value 100
		// The last getSnapshot should see that state.
	}
};

TEST(BaseInputManager, Init)
{

}