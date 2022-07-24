// Reader-Writer Lock
// 언제 쓰는가? -> Write는 매우 드물고 대부분 Read 작업만 있는 경우
// (관리자만 Write 가능한 경우 등)
// W -> R (O) / R -> W (X)
// Write -> Exclusive Lock (소유)
// Read  -> Shared Lock (공유)

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
