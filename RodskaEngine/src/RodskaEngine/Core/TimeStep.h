#pragma once


namespace RodskaEngine {
	class  TimeStep {
	public:
		RODSKA_EAPI TimeStep(float time = 0.0f)
		: m_Time(time) {

		}

		RODSKA_EAPI operator float() const { return m_Time; }

		RODSKA_EAPI float GetSeconds() const { return m_Time; }
		RODSKA_EAPI float GetMilliseconds() const { return m_Time * 1000.0f; }
	private:
		float m_Time;
	};
}