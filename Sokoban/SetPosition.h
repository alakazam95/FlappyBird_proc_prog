#pragma once

#include <unordered_set>
#include <string>

class SetPosition {

public:
	static bool add(std::string position) {
		std::pair<std::unordered_set<std::string>::iterator, bool> ret = positions.insert(position);
		return ret.second;
	}

	static void del(std::string position) {
		std::unordered_set<std::string>::iterator iter = positions.find(position);
		if (iter != positions.end())
			positions.erase(iter);
	}

	static bool ifExists(std::string position) {
		return positions.find(position) != positions.end();
	}

	static void clear() {
		positions.clear();
	}

private:	
	static std::unordered_set<std::string> positions;
};

