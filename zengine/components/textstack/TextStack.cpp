#include "TextStack.h"

TextStack::TextStack(uint32_t cap) :
		sizeCap(cap) {
}

TextStack::~TextStack() {
}

void TextStack::add(std::string s) {
	if (data.size() == sizeCap) {
		data.pop_back();
	}

	data.push_front(s);
}

std::vector<std::string> TextStack::getLines() {
	std::vector<std::string> lines;

	for (std::string &line : data) {
		lines.push_back(line);
	}

	return lines;
}
