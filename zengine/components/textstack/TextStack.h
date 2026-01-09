#ifndef ENGINE_COMPONENTS_TEXTSTACK_TEXTSTACK_H_
#define ENGINE_COMPONENTS_TEXTSTACK_TEXTSTACK_H_

#include <vector>
#include <deque>
#include <string>

/**
 * Called 'Stack' because the new text comes at the top, although implemented with Deque.
 */
class TextStack {
public:
	TextStack(uint32_t sizeCap = 10);
	virtual ~TextStack();

	void add(std::string);
	std::vector<std::string> getLines();
private:
	uint32_t sizeCap;
	std::deque<std::string> data;
};

#endif /* ENGINE_COMPONENTS_TEXTSTACK_TEXTSTACK_H_ */
