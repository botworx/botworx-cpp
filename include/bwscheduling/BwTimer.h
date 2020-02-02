/*BwSchedule - A Scheduling and Threading Library.
Copyright (C) 2004  Kurtis Fields. See BwSchedule_License.txt for details.
*/
#ifndef _BwTimer_H
#define _BwTimer_H

#include <chrono>
typedef double bwRealTime;
typedef std::chrono::milliseconds bwLoFrequency;
typedef std::chrono::nanoseconds bwHiFrequency;
typedef std::chrono::time_point<std::chrono::system_clock, bwLoFrequency> bwLoTime ;
typedef std::chrono::high_resolution_clock bwClock;
typedef std::chrono::time_point<std::chrono::high_resolution_clock, bwHiFrequency> bwHiTime ;

template<typename T_Clock>
class BwClockT {
public:
	typedef std::chrono::nanoseconds duration;
	typedef duration::rep rep;
	typedef duration::period period;
	typedef std::chrono::time_point<bwClock, duration> time_point;
	T_Clock m_clock;
	time_point now () { return m_clock.now(); }
};
typedef BwClockT<std::chrono::high_resolution_clock> BwHiClock;
typedef BwClockT<std::chrono::system_clock> BwLoClock;

template<typename T_Clock>
class BwTimerT : public BwClockT<T_Clock> {
public:
	typedef std::chrono::nanoseconds duration;
	typedef duration::rep rep;
	typedef duration::period period;
	typedef std::chrono::time_point<bwClock, duration> time_point;

	time_point m_startTime ;		//tick count at construction
	time_point m_lastElapsed ;	//
	duration m_alarmInterval ;	//
	time_point m_alarmTime ;		//
	duration m_frequency;

	BwTimerT() {
		reset() ;
	}
	BwTimerT(duration interval) {
		reset() ;
		setAlarm(interval) ;
	}
	void reset() {
		m_frequency = duration(1);
		m_startTime = this->now() ;
		m_lastElapsed = m_startTime ;
		setAlarm(m_frequency) ;
	}
	void setAlarm(duration interval) {
		auto time = this->now() ;
		m_alarmInterval = interval ;
		m_alarmTime = time + m_alarmInterval ;
	}
	/*
	void setAlarm(bwRealTime interval) {
		set
	}*/
	void resetAlarm() {
		auto time = this->now() ;
		m_alarmTime = time + m_alarmInterval ;
	}
	void resetAlarmMinus(duration interval) {
		auto time = this->now() ;
		m_alarmTime = time + ( m_alarmInterval - interval ) ;
	}
	bool checkAlarm() {
		auto time = this->now() ;
		if(time >= m_alarmTime)
			return true ;
		else
			return false ;
	}
	long getElapsed() {
		auto time = this->now() ;
		long elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(time - m_lastElapsed).count();
		m_lastElapsed = time ;
		return elapsed ;
	}
	//
	float getRealTime() {
		/*
		typedef std::chrono::duration<float> fsec;
		auto time = this->now() ;
		// float realTime = ((float)(time - m_startTime)) / ((float)m_frequency) ;
		return std::chrono::duration_cast<float>(time) ;
		 */
		return 0.0;
	}
	float getRealElapsed() {
		/*
		auto elapsed = getElapsed() ;
		float realTime = ((float)elapsed) / ((float)m_frequency) ;
		return realTime ;
		 */
		return 0.0;
	}
};
typedef BwTimerT<BwLoClock> BwLoTimer ;
typedef BwTimerT<BwHiClock> BwHiTimer ;

#endif //_BwTimer_H
