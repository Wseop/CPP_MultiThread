// Reader-Writer Lock
// ���� ���°�? -> Write�� �ſ� �幰�� ��κ� Read �۾��� �ִ� ���
// (�����ڸ� Write ������ ��� ��)
// W -> R (O) / R -> W (X)
// Write -> Exclusive Lock (����)
// Read  -> Shared Lock (����)

#pragma once

#include <cstdint>
#include <atomic>

class RWSpinLock
{
	enum : uint32_t
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x0000'0000
	};

public:
	void WriteLock();
	void WriteUnlock();
	void ReadLock();
	void ReadUnlock();

private:
	// write : threadId
	// read  : read count
	std::atomic<uint32_t> _lockFlag = EMPTY_FLAG;
	uint32_t _writeCount = 0;
};

// RAII
class ReadLockGuard
{
public:
	ReadLockGuard(RWSpinLock& lock);
	~ReadLockGuard();

private:
	RWSpinLock& _lock;
};

class WriteLockGuard
{
public:
	WriteLockGuard(RWSpinLock& lock);
	~WriteLockGuard();

private:
	RWSpinLock& _lock;
};
