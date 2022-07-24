#include "RWSpinLock.h"
#include "TLS.h"
#include <Windows.h>
#include <cassert>
#include <thread>

using namespace std;

void RWSpinLock::WriteLock()
{
	// �̹� ������ thread�� �����ϰ� ������ ������ ����
	uint32_t lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (lockThreadId == LThreadId)
	{
		_writeCount++;
		return;
	}

	// �ƹ��� ����, �����ϰ� ���� ���� �� �����Ͽ� �������� ����
	uint64_t beginTick = ::GetTickCount64();
	uint32_t desired = (LThreadId << 16) & WRITE_THREAD_MASK;
	while (true) 
	{
		for (uint32_t i = 0; i < MAX_SPIN_COUNT; i++) 
		{
			uint32_t expected = EMPTY_FLAG;
			if (_lockFlag.compare_exchange_strong(expected, desired))
			{
				_writeCount++;
				return;
			}
		}

		if (::GetTickCount64() - beginTick > ACQUIRE_TIMEOUT_TICK)
		{
			assert(false && "ACQUIRE TIMEOUT");
		}

		this_thread::yield();
	}
}

void RWSpinLock::WriteUnlock()
{
	// ReadLock�� ���������� WriteUnlock �Ұ��� (���������� case)
	if ((_lockFlag.load() & READ_COUNT_MASK) > 0)
	{
		assert(false && "INVALID CASE");
	}

	_writeCount--;
	if (_writeCount == 0)
	{
		_lockFlag.store(EMPTY_FLAG);
	}
}

void RWSpinLock::ReadLock()
{
	// ������ thread�� �����ϰ� ������ ������ ����
	uint32_t lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (lockThreadId == LThreadId)
	{
		_lockFlag.fetch_add(1);
		return;
	}

	// �ƹ��� �����ϰ� ���� ������ �����Ͽ� ���� ī��Ʈ ����
	while (true)
	{
		uint64_t beginTick = ::GetTickCount64();
		for (uint32_t i = 0; i < MAX_SPIN_COUNT; i++)
		{
			uint32_t expected = _lockFlag.load() & READ_COUNT_MASK;
			if (_lockFlag.compare_exchange_strong(expected, expected + 1))
			{
				return;
			}
		}

		if (::GetTickCount64() - beginTick)
		{
			assert(false && "ACQUIRE TIMEOUT");
		}

		this_thread::yield();
	}
}

void RWSpinLock::ReadUnlock()
{
	if ((_lockFlag.load() & READ_COUNT_MASK) <= 0)
	{
		assert(false && "INVALID CASE");
	}
	_lockFlag.fetch_sub(1);
}

ReadLockGuard::ReadLockGuard(RWSpinLock& lock) : _lock(lock)
{
	_lock.ReadLock();
}

ReadLockGuard::~ReadLockGuard()
{
	_lock.ReadUnlock();
}

WriteLockGuard::WriteLockGuard(RWSpinLock& lock) : _lock(lock)
{
	_lock.WriteLock();
}

WriteLockGuard::~WriteLockGuard()
{
	_lock.WriteUnlock();
}
