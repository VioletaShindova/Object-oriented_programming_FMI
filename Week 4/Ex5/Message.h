#pragma once

class Message
{
public:
	Message() = default;

	explicit Message(int size);

	Message(int size, int key);

	Message(unsigned* messageContent, size_t size, unsigned key);

	Message(const Message& other);

	Message& operator=(const Message& other);

	~Message();

	bool setSize(int size);

	bool setKey(int key);

	bool writeToBinaryFile(const char* fileName) const;

	bool writeToBinaryFileUsingKey(const char* fileName);

	bool readFromBinaryFile(const char* fileName);

	void print() const;

private:
	bool isValidSize(int size) const;

	bool isValidKey(int key) const;

	void copyDynamic(const Message& other);

	void freeDynamic();

	void encrypt(unsigned* message);

	unsigned* messageContent = nullptr;
	size_t size = 0;
	unsigned key = 0;
};