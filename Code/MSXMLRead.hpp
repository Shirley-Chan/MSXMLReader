#ifndef __MSXMLREAD_HPP__
#define __MSXMLREAD_HPP__
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <msxml.h>
#include <tchar.h>

class Node {
private:
	IXMLDOMNodeList* NodeList;
	long Length;
public:
	Node() = default;
	Node(const std::basic_string<TCHAR> NodePath, IXMLDOMNodeList* NodeList);
	std::basic_string<TCHAR> NodePath;
	std::basic_string<TCHAR> operator [] (const long Count) const; // ちょっと長いからcpp側に定義
	long GetLength() const noexcept { return this->Length; }
};

class MSXMLRead {
private:
	IXMLDOMDocument* lpXmlDoc;
	IXMLDOMNodeList* XmlSetNodeList(const std::basic_string<TCHAR> NodePath);
	std::vector<Node> Data;
	std::basic_string<TCHAR> CommonPath;
	void LoadFromFile(const std::basic_string<TCHAR> NodePath);
public:
	MSXMLRead(const std::basic_string<TCHAR> FileName, const std::basic_string<TCHAR> CommonPath = TEXT(""));
	~MSXMLRead() { 
		this->lpXmlDoc->Release();
		this->Data.clear();
	}
	long GetLength(const std::basic_string<TCHAR> NodePath) const noexcept;
	void Load(const std::basic_string<TCHAR> NodePath) { this->LoadFromFile(NodePath); }
	template<class ...Args> void Load(const std::basic_string<TCHAR> NodePath, Args ...arg) {
		this->LoadFromFile(NodePath);
		this->Load(std::forward<Args>(arg)...);
	}
	bool NodeDataExists(const std::basic_string<TCHAR> NodePath) const noexcept;
	size_t size() const noexcept { return this->Data.size(); }
	Node at(const size_t Count) const noexcept { return this->Data[Count]; }
	void clear() { this->Data.clear(); }
	void ChangeCommonPath(const std::basic_string<TCHAR> NewRoot);
	Node operator [] (const size_t Count) const { return this->at(Count); }
	Node operator [] (const std::basic_string<TCHAR> NodePath) const; // WStringToStringを使う関係でcpp側に定義
};
#endif
