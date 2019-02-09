//-----------------------------------------------------------------------------
// File: CGameTimer.cpp
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameTimer.h"
#include <time.h>

CGameTimer::CGameTimer()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER *)&m_PerformanceFrequency))
	{
		m_bHardwareHasPerformanceCounter = TRUE;
		QueryPerformanceCounter((LARGE_INTEGER *)&m_nLastTime);
		m_fTimeScale = 1.0f / m_PerformanceFrequency;
	}
	else
	{
		m_bHardwareHasPerformanceCounter = FALSE;
		m_nLastTime = ::clock();
		m_fTimeScale = 0.001f;
	}

	m_nSampleCount = 0;
	m_nCurrentFrameRate = 0;
	m_FramePerSecond = 0;
	m_fFPSTimeElapsed = 0.0f;
}

CGameTimer::~CGameTimer()
{
}

void CGameTimer::Tick(float fLockFPS)
{
	float fTimeElapsed;

	if (m_bHardwareHasPerformanceCounter)
	{
		QueryPerformanceCounter((LARGE_INTEGER *)&m_nCurrentTime);
	}
	else
	{
		m_nCurrentTime = ::clock();
	}

	fTimeElapsed = (m_nCurrentTime - m_nLastTime) * m_fTimeScale;
	
	if (fTimeElapsed > max)max = fTimeElapsed;

	if (fLockFPS > 0.0f)									//0보단 크니깐 지나감
	{
		int a = 0;
		while (fTimeElapsed < (1.0f / fLockFPS))			
			/*
				이 부분이 핵심!
				fTimeElapsed는 이전 프레임과 현재 시간과의 차이를 나타내는건데
				fTimeElapsed가  1/fLockFPS(파라메터)보다 작으면
				계속 while로 대기타는거임
				그러면 fTimeElapsed의 값은 커지면서 자연스럽게 원하는 시간에 근접하게 나올 수 있음
			*/

			{												
			if (m_bHardwareHasPerformanceCounter)			
			{
				QueryPerformanceCounter((LARGE_INTEGER *)&m_nCurrentTime);
			}
			else
			{
				m_nCurrentTime = ::clock();
			}
			// Calculate elapsed time in seconds
			fTimeElapsed = (m_nCurrentTime - m_nLastTime) * m_fTimeScale;
		}
	}
	m_nLastTime = m_nCurrentTime;

	if (fabsf(fTimeElapsed - m_fTimeElapsed) < 1.0f)
	{
		// Wrap FIFO frame time buffer.
		memmove(&m_fFrameTime[1], m_fFrameTime, (MAX_SAMPLE_COUNT - 1) * sizeof(float));
		m_fFrameTime[0] = fTimeElapsed;
		if (m_nSampleCount < MAX_SAMPLE_COUNT) m_nSampleCount++;
	}

	// Calculate Frame Rate
	m_FramePerSecond++;
	m_fFPSTimeElapsed += fTimeElapsed;
	if (m_fFPSTimeElapsed > 1.0f)
	{
		m_nCurrentFrameRate = m_FramePerSecond;
		m_FramePerSecond = 0;
		m_fFPSTimeElapsed = 0.0f;
	}

	// Count up the new average elapsed time
	m_fTimeElapsed = 0.0f;
	for (ULONG i = 0; i < m_nSampleCount; i++) m_fTimeElapsed += m_fFrameTime[i];
	if (m_nSampleCount > 0) m_fTimeElapsed /= m_nSampleCount;

	m_fGlobalTime += fLockFPS;
}

unsigned long CGameTimer::GetFrameRate(LPTSTR lpszString, int nCharacters) const
{
	if (lpszString)
	{
		//_itow(m_nCurrentFrameRate, lpszString, nCharacters);
		//wcscat(lpszString, nCharacters, _T(" FPS)"));
	}

	return(m_nCurrentFrameRate);
}

float CGameTimer::GetTimeElapsed() const
{
	return(m_fTimeElapsed);
}



float CGameTimer::GetNowCurrentTime() const
{
	return(m_nCurrentTime);
}
