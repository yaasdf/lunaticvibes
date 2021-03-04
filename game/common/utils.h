#pragma once
#include <string>
#include <filesystem>
#include <vector>
#include <utility>

namespace fs = std::filesystem;

inline fs::path executablePath;

// Following LR2skin path rules:
// Only filename (not including folders) could have wildcards "*"
// Searching is not recursive.
std::vector<fs::path> findFiles(fs::path path);

bool isParentPath(fs::path parent, fs::path dir);

// For LR2 skin .csv parsing:
// op1~4 may include a '!' before the number, split it out
std::pair<unsigned, bool> stoub(const std::string&);
int stoine(const std::string& str) noexcept;
double stodne(const std::string& str) noexcept;

constexpr unsigned base36(char c)
{
	return (c > '9') ? (c >= 'a' ? 10 + c - 'a' : 10 + c - 'A') : (c - '0');
}

constexpr unsigned base36(char first, char second)
{
	return 36 * base36(first) + base36(second);
}

constexpr unsigned base36(const char* c)
{
	return base36(c[0], c[1]);
}

constexpr unsigned base16(char c)
{
	return (c > '9') ? (c >= 'a' ? 10 + c - 'a' : 10 + c - 'A') : (c - '0');
}

constexpr unsigned base16(char first, char second)
{
	return 16 * base16(first) + base16(second);
}

constexpr unsigned base16(const char* c)
{
	return base16(c[0], c[1]);
}

std::string md5(const std::string& str);
std::string md5(const char* str, size_t len);
std::string md5file(const fs::path& filePath);

std::string toLower(const std::string& s);
std::string toUpper(const std::string& s);

enum class eFileEncoding
{
	LATIN1,
	SHIFT_JIS,
	EUC_KR,
	UTF8,
};
eFileEncoding getFileEncoding(const fs::path& path);
std::string to_utf8(const std::string& str, eFileEncoding fromEncoding);