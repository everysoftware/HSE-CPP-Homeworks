#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

#define TASK_2

#ifdef TASK_1
bool is_palindrom(std::string const& s) {
	auto it = s.begin();
	auto it_r = s.rbegin();
	auto it_mid = s.begin() + (s.size() / 2);
	while (it != it_mid) {
		if (*it != *it_r) {
			return false;
		}
		++it;
		++it_r;
	}
	return true;
}

void solve() {
	std::string s;
	std::cin >> s;
	std::cout << is_palindrom(s) << std::endl;
}
#endif
#ifdef TASK_2

std::vector<std::string> str_split(std::string const& s, char delim) {
	std::vector<std::string> v;
	std::string word = "";
	for (auto c : s) {
		if (c == delim) {
			if (!word.empty()) {
				v.push_back(word);
				word = "";
			}
		}
		else {
			word += c;
		}
	}
	if (!word.empty()) {
		v.push_back(word);
	}
	return v;
}

std::vector<std::string> str_split_improved(std::string const& s, char delim) {
	std::stringstream ss(s);
	std::vector<std::string> v;
	std::string word = "";
	while (std::getline(ss, word, delim)) {
		v.push_back(word);
	}
	return v;
}

std::string str_join(std::vector<std::string> const& v, std::string const& delim) {
	std::stringstream ss;
	std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(ss, delim.c_str()));
	return ss.str();
}

std::string sort_by_word_len(std::string const& s) {
	auto v = str_split(s, ' ');
	std::sort(v.begin(), v.end(), [](std::string const& s1, std::string const& s2) {
		return s1.size() < s2.size();
		});
	return str_join(v, " ");
}

void solve() {
	std::string s;
	std::getline(std::cin, s);
	std::cout << sort_by_word_len(s) << std::endl;
}
#endif

int main() {
	solve();
	return 0;
}
